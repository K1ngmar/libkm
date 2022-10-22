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
#include <libkm.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>

#define BASE_STRING "0123456789abcdef"

static inline int nbr_prefix_length(bool is_negative, unsigned long long nbr, const t_printf_flags* flags, size_t base)
{
	if (is_negative == true || flags->always_signed == true || flags->blank == true)
		return (1);
	if (base == 16 && flags->alternate_form == true && nbr != 0)
		return (2); // 0X
	return (0);
}

static int nbr_length(unsigned long long nbr, size_t base)
{
	int len = 0;

	if (nbr == 0)
		++len;
	for (; nbr != 0; nbr /= base)
		++len;
	return (len);
}

static int conversion_recusion(printf_buffer_t* buffer, unsigned long long nbr, size_t base, int(*conversion)(int))
{
	if (nbr > 0) {
		RETURN_IF_FAILED(conversion_recusion(buffer, nbr / base, base, conversion));
		RETURN_IF_FAILED(km_add_to_buffer(buffer, conversion(BASE_STRING[nbr % base])));
	}
	return (0);
}

static int set_prefix(printf_buffer_t* buffer, const t_printf_flags* flags, unsigned long long nbr, bool is_negative, size_t base, int(*case_modifier)(int))
{
	if (base == 10) {
		if (is_negative == true)
			RETURN_IF_FAILED(km_add_to_buffer(buffer, '-'));
		else if (flags->always_signed == true)
			RETURN_IF_FAILED(km_add_to_buffer(buffer, '+'));
		else if (flags->blank == true)
			RETURN_IF_FAILED(km_add_to_buffer(buffer, ' '));
	}
	else if (base == 16) {
		if (flags->alternate_form == true && nbr != 0) {
			RETURN_IF_FAILED(km_add_to_buffer(buffer, '0'));
			RETURN_IF_FAILED(km_add_to_buffer(buffer, case_modifier('X')));
		}
	}
	return (0);
}

static int do_integral_conversion(printf_buffer_t* buffer, const t_printf_flags* flags, unsigned long long nbr, bool is_negative, size_t base)
{
	const int nbr_len = nbr_length(nbr, base) + nbr_prefix_length(is_negative, nbr, flags, base);
	const int true_len = MAX(flags->precision + nbr_prefix_length(is_negative, nbr, flags, base), nbr_len);
	int(*case_modifier)(int) = (flags->uppercase == true) ? km_toupper : km_tolower;

	// fill width on left side
	if (flags->left_adjust == false)
		RETURN_IF_FAILED(km_fill_width(buffer, flags, true_len));

	// set prefix
	RETURN_IF_FAILED(set_prefix(buffer, flags, nbr, is_negative, base, case_modifier));
	
	// add precision
	if (true_len != nbr_len)
		RETURN_IF_FAILED(km_fill_char(buffer, '0', true_len - nbr_len));

	// itoa
	if (nbr == 0)
		RETURN_IF_FAILED(km_add_to_buffer(buffer, '0'));
	else
		RETURN_IF_FAILED(conversion_recusion(buffer, nbr, base, case_modifier));

	// fill width on right side
	if (flags->left_adjust == true)
		RETURN_IF_FAILED(km_fill_width(buffer, flags, true_len));
	return (0);
}

int conversion_signed(va_list arg, printf_buffer_t* buffer, const t_printf_flags* flags, size_t base)
{
	long long nbr;

	switch(flags->size) {
		case LONG: {
			nbr = (long int)va_arg(arg, long int); break;
		}
		case LONG_LONG: {
			nbr = (long long int)va_arg(arg, long long int); break;
		}
		case SHORT: {
			nbr = (short)va_arg(arg, int); break;
		}
		case SHORT_SHORT: {
			nbr = (int8_t)va_arg(arg, int); break;
		}
		default: {
			nbr = (int)va_arg(arg, int);
		}
	}

	if (nbr < 0)
		return do_integral_conversion(buffer, flags, -nbr, true, base);
	return do_integral_conversion(buffer, flags, nbr, false, base);
}

int conversion_unsigned(va_list arg, printf_buffer_t* buffer, const t_printf_flags* flags, size_t base)
{
	unsigned long long nbr;

	switch(flags->size) {
		case LONG: {
			nbr = (unsigned long int)va_arg(arg, long int); break;
		}
		case LONG_LONG: {
			nbr = (unsigned long long int)va_arg(arg, long long int); break;
		}
		case SHORT: {
			nbr = (unsigned short)va_arg(arg, int); break;
		}
		case SHORT_SHORT: {
			nbr = (uint8_t)va_arg(arg, int); break;
		}
		default: {
			nbr = (unsigned int)va_arg(arg, int);
		}
	}

	return do_integral_conversion(buffer, flags, nbr, false, base);
}

#undef BASE_STRING
