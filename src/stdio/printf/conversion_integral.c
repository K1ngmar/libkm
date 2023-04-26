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
#include "libkm/string.h"
#include "libkm/libkm.h"

#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>

#define KM_BASE_STRING "0123456789abcdef"

static int nbr_length(uint64_t nbr, size_t base)
{
	int len = 0;

	if (nbr == 0)
		++len;
	for (; nbr != 0; nbr /= base)
		++len;
	return (len);
}

static int conversion_recusion(printf_buffer_t* buffer, uint64_t nbr, size_t base, int(*conversion)(int))
{
	if (nbr > 0) {
		RETURN_IF_FAILED(conversion_recusion(buffer, nbr / base, base, conversion));
		RETURN_IF_FAILED(km_add_to_buffer(buffer, conversion(KM_BASE_STRING[nbr % base])));
	}
	return (0);
}

static void set_precision(t_printf_flags* flags, uint64_t nbr, const int nbr_len, size_t base)
{
	// octal in alternate form needs to start with a 0
	if (base == 8 && flags->alternate_form == true && nbr != 0) {
		if (flags->precision <= nbr_len)
			flags->precision = nbr_len + 1;
	}
}

static int do_integral_conversion(
	printf_buffer_t* buffer,
	t_printf_flags* flags,
	uint64_t nbr,
	bool is_negative,
	size_t base,
	prefix_length_fp prefix_length,
	set_prefix_fp set_prefix)
{
	const int nbr_len = nbr_length(nbr, base) + prefix_length(is_negative, nbr, flags);

	// increase precision if necessary
	set_precision(flags, nbr, nbr_len, base);
	
	const int true_len = MAX(flags->precision + prefix_length(is_negative, nbr, flags), nbr_len);
	int(*case_modifier)(int) = (flags->uppercase == true) ? km_toupper : km_tolower;

	// fill width on left side
	if (flags->left_adjust == false)
		RETURN_IF_FAILED(km_fill_width(buffer, flags, true_len));

	// set prefix
	RETURN_IF_FAILED(set_prefix(buffer, flags, nbr, is_negative, case_modifier));
	
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

int conversion_signed(va_list arg, printf_buffer_t* buffer, t_printf_flags* flags, size_t base, prefix_length_fp prefix_length, set_prefix_fp set_prefix)
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
		return do_integral_conversion(buffer, flags, -nbr, true, base, prefix_length, set_prefix);
	return do_integral_conversion(buffer, flags, nbr, false, base, prefix_length, set_prefix);
}

int conversion_unsigned(va_list arg, printf_buffer_t* buffer, t_printf_flags* flags, size_t base, prefix_length_fp prefix_length, set_prefix_fp set_prefix)
{
	uint64_t nbr;

	switch(flags->size) {
		case LONG: {
			nbr = (unsigned long int)va_arg(arg, long int); break;
		}
		case LONG_LONG: {
			nbr = (unsigned long long)va_arg(arg, long long int); break;
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
	return do_integral_conversion(buffer, flags, nbr, false, base, prefix_length, set_prefix);
}

int conversion_pointer(va_list arg, printf_buffer_t* buffer, t_printf_flags* flags)
{
	uintptr_t address = (uintptr_t)va_arg(arg, uintptr_t);
	return do_integral_conversion(buffer, flags, address, false, KM_BASE_HEXADECIMAL, prefix_length_address, set_prefix_address);
}

#undef KM_BASE_STRING
