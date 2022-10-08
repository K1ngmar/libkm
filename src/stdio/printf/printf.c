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

///////////////////
// Main function //
///////////////////

static int format_loop(printf_buffer_t* buffer, va_list args, const char* restrict format)
{
	int ret = 0;

	while (ret == 0 && *format != '\0') {
		// conversion is found
		if (*format == '%') {
			++format;
			ret = conversion_dispatcher(args, &format, buffer);
		}
		// no conversion
		else {
			ret = km_add_to_buffer(buffer, *format);
			if (ret < 0)
				break ;
		}
		++format;
	}
	va_end(args);
	return (ret);
}

#define km_printf(format, ...) km_dprintf(STDOUT_FILENO, format, __VA_ARGS__);

int	km_dprintf(int fd, const char* restrict format, ...)
{
	static printf_buffer_t buffer = {
		.sprintf_str = NULL, // should not be used
		.len = 0,
		.max_len = PRINTF_BUFFER_SIZE,
		.fd = -1, // should be set later
		.flush = km_flush_buffer_fd
	};
	int	ret = 0;

	// check if previous call was done on same fd
	if (fd != buffer.fd) {
		// if buffer is not empty clear it.
		if (buffer.len > 0)
			ret = buffer.flush(&buffer);
		buffer.fd = fd;
	}

	va_list args;
	va_start(args, format);
	ret = format_loop(&buffer, args, format);
	return (ret);
}

/*
 * When passed a pointer to NULL it will allocate the right size
 * 
 * IMPORTANT: do not pass this an allocated pointer because that will cause a leak 
*/
int km_sprintf(char* restrict* str, const char* restrict format, ...)
{
	printf_buffer_t buffer = {
		.sprintf_str = NULL,
		.len = 0,
		.max_len = PRINTF_BUFFER_SIZE,
		.fd = -1, // invalid value, should not be used
		.flush = km_flush_buffer_str
	};

	int	ret = 0;

	va_list args;
	va_start(args, format);
	ret = format_loop(&buffer, args, format);

	// if buffer is not empty clear it.
	if (buffer.len > 0 && ret == 0)
		ret = buffer.flush(&buffer);
	else if (buffer.sprintf_str == NULL && ret == 0)
		buffer.sprintf_str = km_strdup("");

	*str = buffer.sprintf_str;

	return (ret);
}
