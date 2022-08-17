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

#ifndef PRINTF_BUFFER_SIZE
# define PRINTF_BUFFER_SIZE 256
#endif

#define km_printf(format, va_args...) km_dprintf(STDOUT_FILENO, format, va_args);

///////////
// Enums //
///////////

typedef enum e_format_size {
	LONG,
	LONG_LONG,
	SHORT,
	SHORT_SHORT,
	DEFAULT
} e_format_size;

///////////////////
// BUFFER STRUCT //
///////////////////

typedef struct s_printf_buffer {
	char	str[PRINTF_BUFFER_SIZE];
	int		length;
	int		fd;
} t_printf_buffer;

typedef struct s_printf_flags {
	int field_width;		 // number
	int precision;			 // '.' followed by a number
	int alternate_form	: 1; // '#'
	int left_adjust		: 1; // '-'
	int always_signed	: 1; // '+'
	int blank			: 1; // ' '
	int zero_padded		: 1; // '0'
	int	is_unsigned		: 1;
	e_format_size size	: 3; // ie: ll
	int uppercase		: 1; // print in uppercase
} t_printf_flags;

//////////////////////
// Helper functions //
//////////////////////

static int km_flush_buffer(t_printf_buffer* buffer)
{
	if (write(buffer->fd, buffer->str, buffer->length) < 0)
		return (-1); // maybe still set length to 0?
	buffer->length = 0;
	return (0);
}

static int km_add_to_buffer(t_printf_buffer* buffer, char c)
{
	if (buffer->length + 1 == PRINTF_BUFFER_SIZE)
		if (km_flush_buffer(buffer) < 0)
			return (-1);
	buffer->str[buffer->length] = c;
	buffer->length++;
}

/////////////////
// Conversions //
/////////////////

static int conversion_signed_decimal(t_printf_buffer* buffer, t_printf_flags* flags, long long int nbr)
{
}

///////////////////////////
// Conversion dispatcher //
///////////////////////////

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

static int conversion_dispatcher(va_list args, const char** format, t_printf_buffer* buffer)
{
	t_printf_flags flags = init_flags(format, args);
	set_format_specifier(&flags, format);

	switch(**format) {
		case 'd':
		case 'i': {
			// return conversion_signed_decimal(buffer, &flags, args);
		}
	}
	return (0);
}

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
			if (buffer.length < PRINTF_BUFFER_SIZE)
				ret = km_flush_buffer(&buffer);
			if (ret < 0)
				break ;
			buffer.str[buffer.length] = *format;
			// newline is found, flush buffer
			if (*format == '\n')
				ret = km_flush_buffer(&buffer);
		}
		++format;
	}
	va_end(args);
	return (ret);
}
