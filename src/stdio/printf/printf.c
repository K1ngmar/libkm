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

#define km_printf(format, va_args...) km_dprintf(STDOUT_FILENO, format, va_args);

///////////////////
// Main function //
///////////////////

int	km_dprintf(int fd, const char* format, ...)
{
	static t_printf_buffer buffer;
	va_list args;
	int	ret = 0;

	// check if previous call was done on same fd
	if (fd != buffer.fd) {
		// if buffer is not empty clear it.
		if (buffer.length > 0)
			ret = km_flush_buffer(&buffer);
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
			// newline is found, flush buffer
			if (*format == '\n')
				ret = km_flush_buffer(&buffer);
		}
		++format;
	}
	va_end(args);
	return (ret);
}
