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

#include "printf.h"
#include <stdbool.h>
#include <stdarg.h>

///////////
// Flags //
///////////

static t_printf_flags init_flags(const char** format, va_list args)
{
	t_printf_flags flags = {
		.field_width = false,
		.precision = false,
		.alternate_form = false,
		.left_adjust = false,
		.always_signed = false,
		.blank = false,
		.zero_padded = false,
		.is_unsigned = false,
		.size = DEFAULT,
		.uppercase = false
	};
	
	if (**format == '#') {
		flags.alternate_form = true;
		++(*format);
	}
	if (**format == '-') {
		flags.left_adjust = true;
		++(*format);
	}
	if (**format == '+') {
		flags.always_signed = true;
		++(*format);
	}
	if (**format == ' ') {
		flags.blank = true;
		++(*format);
	}
	if (**format == '0') {
		flags.zero_padded = true;
		++(*format);
	}
	// field witdh
	if (km_isdigit(**format)) {
		flags.field_width = km_strtoll(*format, format, 10);
	}
	else if (**format == '*') {
		flags.field_width = va_arg(args, int);
		++(*format);
	}
	// precision
	if (**format == '.') {
		++(*format);
		if (*format == '*') {
			flags.precision = va_arg(args, int);
			++(*format);
		} else {
			flags.precision = km_strtoll(*format, format, 10);
		}
	}
	return (flags);
}

static void	set_format_specifier(t_printf_flags* flags, const char** format)
{
	if (**format == 'u') {
		++(*format);
		flags->is_unsigned = true;
	}
	if (km_tolower(**format) == 'l') {
		if (km_isupper(**format))
			flags->uppercase = true;
		++(*format);
		if (km_tolower(**format) == 'l') {
			++(*format);
			flags->size = LONG_LONG;
		}
		else
			flags->size = LONG;
	}
	else if (km_tolower(**format) == 'h') {
		if (km_isupper(**format))
			flags->uppercase = true;
		++(*format);
		if (km_tolower(**format) == 'h') {
			++(*format);
			flags->size = SHORT_SHORT;
		}
		else
			flags->size = SHORT;
	}
}

////////////////
// Dispatcher //
////////////////

int conversion_dispatcher(va_list args, const char** format, t_printf_buffer* buffer)
{
	t_printf_flags flags = init_flags(format, args);
	set_format_specifier(&flags, format);

	switch(**format) {
		case 'd':
		case 'i': {
			if (flags.is_unsigned == true)
				return conversion_unsigned_decimal(buffer, &flags, );
			return conversion_signed_decimal(buffer, &flags, );
		}
	}
	return (0);
}
