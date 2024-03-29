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
#include <inttypes.h>
#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>

#define KM_BASE_OCTAL 8
#define KM_BASE_DECIMAL 10
#define KM_BASE_HEXADECIMAL 16

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

	struct printf_buffer_s;

	typedef int (*flush_t)(struct printf_buffer_s*);

	typedef struct printf_buffer_s {
		char	buffer_str[PRINTF_BUFFER_SIZE + 1];
		char*	sprintf_str;
		char*	str;
		int		bytes_printed;
		int		len;
		int		max_len;
		int		fd;
		flush_t flush;
	} printf_buffer_t;

	typedef struct s_printf_flags {
		int 	field_width;		 // number
		int 	precision;			 // '.' followed by a number
		bool 	alternate_form	: 1; // '#'
		bool	left_adjust		: 1; // '-'
		bool	always_signed	: 1; // '+'
		bool	blank			: 1; // ' '
		bool	zero_padded		: 1; // '0'
		bool	is_unsigned		: 1; // no negativity
		e_format_size size		: 3; // ie: ll
		bool	uppercase		: 1; // print in uppercase
	} t_printf_flags;

////////////
// Buffer //
////////////

	int	km_flush_buffer_fd(printf_buffer_t* buffer);
	int	km_flush_buffer_str(printf_buffer_t* buffer);
	int	km_flush_buffer_nstr(printf_buffer_t* buffer);
	int	km_add_to_buffer(printf_buffer_t* buffer, char c);
	int km_fill_char(printf_buffer_t* buffer, char c, int length);
	int	km_fill_width(printf_buffer_t* buffer, const t_printf_flags* flags, int conversion_width);

////////////////
// Dispatcher //
////////////////

	int conversion_dispatcher(va_list args, const char* restrict * format, printf_buffer_t* buffer);

/////////////////////
// integral prefix //
/////////////////////

	typedef int(*set_prefix_fp)(printf_buffer_t*, const t_printf_flags*, uint64_t, bool, int(*)(int));

	int set_prefix_decimal(printf_buffer_t* buffer, const t_printf_flags* flags, uint64_t nbr, bool is_negative, int(*)(int));
	int set_prefix_hex(printf_buffer_t* buffer, const t_printf_flags* flags, uint64_t nbr, bool, int(*case_modifier)(int));
	int set_prefix_address(printf_buffer_t* buffer, const t_printf_flags*, uint64_t, bool, int(*)(int));
	int set_prefix_octal(printf_buffer_t*, const t_printf_flags*, uint64_t, bool, int(*)(int));

	typedef int(*prefix_length_fp)(bool, uint64_t, const t_printf_flags*);

	int prefix_length_decimal(bool is_negative, uint64_t nbr, const t_printf_flags* flags);
	int prefix_length_hex(bool, uint64_t nbr, const t_printf_flags* flags);
	int prefix_length_address(bool, uint64_t, const t_printf_flags*);
	int prefix_length_octal(bool, uint64_t, const t_printf_flags*);

/////////////////
// Conversions //
/////////////////

	int conversion_signed(va_list arg, printf_buffer_t* buffer, t_printf_flags* flags, size_t base, prefix_length_fp prefix_length, set_prefix_fp set_prefix);
	int conversion_unsigned(va_list arg, printf_buffer_t* buffer, t_printf_flags* flags, size_t base, prefix_length_fp prefix_length, set_prefix_fp set_prefix);
	int conversion_pointer(va_list arg, printf_buffer_t* buffer, t_printf_flags* flags);
	int conversion_string(va_list arg, printf_buffer_t* buffer, const t_printf_flags* flags);
	int conversion_char(va_list arg, printf_buffer_t* buffer, const t_printf_flags* flags);

#endif
