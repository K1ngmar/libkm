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

#ifndef KM_PRINTF_H
# define KM_PRINTF_H

# ifndef PRINTF_BUFFER_SIZE
#  define PRINTF_BUFFER_SIZE 256
# endif

#include <stdarg.h>

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

////////////
// STRUCT //
////////////

	struct printf_buffer_t;

	typedef int (*flush_t)(printf_buffer_t*);

	typedef struct s_printf_buffer {
		char	str[PRINTF_BUFFER_SIZE + 1];
		char*	sprintf_string;
		int		length;
		int		fd;
		flush_t flush;
	} printf_buffer_t;

	typedef struct s_printf_flags {
		int field_width;		 // number
		int precision;			 // '.' followed by a number
		int alternate_form	: 1; // '#'
		int left_adjust		: 1; // '-'
		int always_signed	: 1; // '+'
		int blank			: 1; // ' '
		int zero_padded		: 1; // '0'
		int	is_unsigned		: 1; // no negativity
		e_format_size size	: 3; // ie: ll
		int uppercase		: 1; // print in uppercase
	} t_printf_flags;

////////////
// Buffer //
////////////

	int	km_flush_buffer_fd(printf_buffer_t* buffer);
	int	km_flush_buffer_str(printf_buffer_t* buffer);
	int	km_add_to_buffer(printf_buffer_t* buffer, char c);
	int km_fill_char(printf_buffer_t* buffer, char c, int length);
	int	km_fill_width(printf_buffer_t* buffer, const t_printf_flags* flags, int conversion_width);

////////////////
// Dispatcher //
////////////////

	int conversion_dispatcher(va_list args, const char** format, printf_buffer_t* buffer);

/////////////////
// Conversions //
/////////////////

	int conversion_decimal(va_list arg, printf_buffer_t* buffer, const t_printf_flags* flags);

#endif
