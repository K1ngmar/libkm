/* ************************************************************************** */
/*                                                                            */
/*                 _       _______  _____   _    _   __   __                  */
/*                (_)     (_______)(_____) (_)  (_) (__)_(__)                 */
/*                (_)        (_)   (_)__(_)(_)_(_) (_) (_) (_)                */
/*                (_)        (_)   (_____) (____)  (_) (_) (_)                */
/*                (_)____  __(_)__ (_)__(_)(_) (_) (_)     (_)                */
/*                (______)(_______)(_____) (_)  (_)(_)     (_)                */
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <libkm.h>
#include <stdbool.h>
#include "printf.h"

#define km_printf(format, ...) km_dprintf(STDOUT_FILENO, format, __VA_ARGS__);

///////////////////
// Main function //
///////////////////

int	km_dprintf(int fd, const char* restrict format, ...)
{
	static printf_buffer_t buffer = {
		.str = buffer.buffer_str,
		.len = 0,
		.max_len = PRINTF_BUFFER_SIZE,
		.fd = -1, // should be set later
		.flush = km_flush_buffer_fd
	};
	va_list args;
	int	ret = 0;

	// check if previous call was done on same fd
	if (fd != buffer.fd) {
		// if buffer is not empty clear it.
		if (buffer.len > 0)
			ret = buffer.flush(&buffer);
		buffer.fd = fd;
	}

	va_start(args, format);
	while (ret == 0 && *format != '\0') {
		// conversion is found
		if (*format == '%') {
			++format;
			ret = conversion_dispatcher(args, &format, &buffer);
		}
		// no conversion
		else {
			ret = km_add_to_buffer(&buffer, *format);
			if (ret < 0)
				break ;
		}
		++format;
	}
	va_end(args);
	return (ret);
}

/*
 * When passed a pointer to NULL it will allocate the right size
 * otherwise it will reallocate after the length has reached PRINTF_BUFFER_SIZE.
 * IMPORTANT: make sure if you do not pass it NULL, and you want it to reallocate,
 * that it has atleast a size of PRINTF_BUFFER_SIZE + 1 
*/
int km_sprintf(char* restrict* str, const char* restrict format, ...)
{
	static printf_buffer_t buffer = {
		.len = 0,
		.max_len = PRINTF_BUFFER_SIZE,
		.fd = -1, // invalid value, should not be used
		.flush = km_flush_buffer_str
	};
	va_list args;
	int	ret = 0;

	buffer.sprintf_str = *str;
	if (*str == NULL) {
		buffer.str = buffer.buffer_str;
	} else {
		buffer.str = *str;
	}

	va_start(args, format);
	while (ret == 0 && *format != '\0') {
		// conversion is found
		if (*format == '%') {
			++format;
			ret = conversion_dispatcher(args, &format, &buffer);
		}
		// no conversion
		else {
			ret = km_add_to_buffer(&buffer, *format);
			if (ret < 0)
				break ;
		}
		++format;
	}
	va_end(args);

	// if buffer is not empty clear it.
	if (buffer.len > 0 && buffer.str != buffer.sprintf_str)
		ret = buffer.flush(&buffer);
	else
		ret = km_add_to_buffer(&buffer, '\0');

	*str = buffer.sprintf_str;

	return (ret);
}
