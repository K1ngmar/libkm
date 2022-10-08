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

static inline bool has_nbr_prefix(bool is_negative, const t_printf_flags* flags) {
 return (is_negative == true || flags->always_signed == true || flags->blank == true);
}

static int nbr_length(unsigned long long nbr)
{
	int len = 0;

	if (nbr == 0)
		++len;
	for (; nbr != 0; nbr /= 10)
		++len;
	return (len);
}

static int conversion_recusion(printf_buffer_t* buffer, unsigned long long nbr)
{
	if (nbr > 0) {
		RETURN_IF_FAILED(conversion_recusion(buffer, nbr / 10));
		RETURN_IF_FAILED(km_add_to_buffer(buffer, '0' + (nbr % 10)));
	}
	return (0);
}

static int do_decimal_conversion(printf_buffer_t* buffer, const t_printf_flags* flags, unsigned long long nbr, bool is_negative)
{
	const int nbr_len = nbr_length(nbr) + has_nbr_prefix(is_negative, flags);
	const int true_len = MAX(flags->precision + has_nbr_prefix(is_negative, flags), nbr_len);

	// fill width on left side
	if (flags->left_adjust == false)
		RETURN_IF_FAILED(km_fill_width(buffer, flags, true_len));

	// add sign or blank
	if (is_negative == true)
		RETURN_IF_FAILED(km_add_to_buffer(buffer, '-'));
	else if (flags->always_signed == true)
		RETURN_IF_FAILED(km_add_to_buffer(buffer, '+'));
	else if (flags->blank == true)
		RETURN_IF_FAILED(km_add_to_buffer(buffer, ' '));
	
	// add precision
	if (true_len != nbr_len)
		RETURN_IF_FAILED(km_fill_char(buffer, '0', true_len - nbr_len));

	// itoa
	if (nbr == 0)
		RETURN_IF_FAILED(km_add_to_buffer(buffer, '0'));
	else
		RETURN_IF_FAILED(conversion_recusion(buffer, nbr));

	// fill width on right side
	if (flags->left_adjust == true)
		RETURN_IF_FAILED(km_fill_width(buffer, flags, true_len));
	return (0);
}

int conversion_decimal(va_list arg, printf_buffer_t* buffer, const t_printf_flags* flags)
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

	// number is negative
	if (flags->is_unsigned == false && nbr < 0)
		return do_decimal_conversion(buffer, flags, -nbr, true);
	// number is not negative
	return do_decimal_conversion(buffer, flags, nbr, false);
}
