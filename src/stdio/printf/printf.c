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

int	km_dprintf(int fd, const char* restrict format, ...)
{
	static printf_buffer_t buffer = {
		.sprintf_str = NULL, // should not be used
		.str = buffer.buffer_str,
		.bytes_printed = 0,
		.len = 0,
		.max_len = PRINTF_BUFFER_SIZE,
		.fd = -1, // should be set later
		.flush = km_flush_buffer_fd
	};
	int	ret = 0;
	buffer.fd = fd;
	buffer.bytes_printed = 0;

	va_list args;
	va_start(args, format);
	ret = format_loop(&buffer, args, format);

	if (buffer.len > 0)
		ret = buffer.flush(&buffer);
	return (ret == 0 ? buffer.bytes_printed : ret);
}

int km_sprintf_common(const char* restrict format, va_list args, printf_buffer_t* buffer)
{
	int	ret = 0;
	
	ret = format_loop(buffer, args, format);

	// if buffer is not empty clear it.
	if (buffer->len > 0 && ret == 0)
		ret = buffer->flush(buffer);

	return (ret == 0 ? buffer->bytes_printed : ret);
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
		.str = buffer.buffer_str,
		.bytes_printed = 0,
		.len = 0,
		.max_len = PRINTF_BUFFER_SIZE,
		.fd = -1, // invalid value, should not be used
		.flush = km_flush_buffer_str
	};

	va_list args;
	va_start(args, format);
	int ret = km_sprintf_common(format, args, &buffer);
	if (buffer.sprintf_str == NULL && ret >= 0)
	{
		buffer.sprintf_str = km_strdup("");
		if (buffer.sprintf_str == NULL)
			ret = -1;
	}
	*str = buffer.sprintf_str;
	return (ret);
}

int km_snprintf(char* restrict* str, const size_t size, const char* restrict format, ...)
{
	printf_buffer_t buffer = {
		.sprintf_str = *str,
		.str = buffer.sprintf_str,
		.len = 0,
		.max_len = size,
		.fd = -1, // invalid value, should not be used
		.flush = km_flush_buffer_nstr
	};

	va_list args;
	va_start(args, format);
	int ret = km_sprintf_common(format, args, &buffer);
	if (buffer.bytes_printed == 0 && ret >= 0)
		buffer.sprintf_str[0] = '\0';
	return (ret);
}
