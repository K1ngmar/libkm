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

#define km_printf(format, va_args...) km_dprintf(STDOUT_FILENO, format, va_args);

int	km_dprintf(int fd, const char* restrict format, ...)
{
	va_list args;
	va_start(args, format);

	while (*format != '\0') {
		if (*format == '%') {
			++format;
			if (*format == 'd') {
				int i = va_arg(args, int);
				km_putnbr_fd(i, fd);
			} else if (*format == 'c') {
				char c = va_arg(args, int);
				km_putchar_fd(c, fd);
			} else if (*format == 's') {
				char* str = va_arg(args, char*);
				km_putstr_fd(str, fd);
			}
		} else {
			km_putchar_fd(*format, fd);
		}
		++format;
	}
	va_end(args);
	return (0);
}
