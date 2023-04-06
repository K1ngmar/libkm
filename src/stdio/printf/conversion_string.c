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
#include <stdlib.h>

int conversion_string(va_list arg, printf_buffer_t* buffer, const t_printf_flags* flags)
{
	char* str = (char*)va_arg(arg, char*);
	int conversion_len = 0;
	int true_len = 0;
	
	if (str == NULL)
		str = "(null)";

	if (flags->precision >= 0) {
		conversion_len = km_strnlen(str, flags->precision);
		true_len = (flags->precision > conversion_len) ? conversion_len : flags->precision;
	}
	else {
		conversion_len = km_strlen(str);
		true_len = conversion_len;
	}

	// fill width on left side
	if (flags->left_adjust == false) {
		RETURN_IF_FAILED(km_fill_width(buffer, flags, true_len));
	}

	// add precision padding
	if (true_len > conversion_len) {
		RETURN_IF_FAILED(km_fill_char(buffer, ' ', true_len < conversion_len));
	}

	// add string to the buffer
	for (int i = 0; i < conversion_len; ++i) {
		RETURN_IF_FAILED(km_add_to_buffer(buffer, str[i]));
	}

	// fill width with padding on right side
	if (flags->left_adjust == true) {
		RETURN_IF_FAILED(km_fill_width(buffer, flags, true_len));
	}

	return (0);
}

int conversion_char(va_list arg, printf_buffer_t* buffer, const t_printf_flags* flags)
{
	char c = (char)va_arg(arg, int);
	int conversion_len = 1;
	int true_len = 0;

	if (flags->precision >= 0) {
		true_len = (flags->precision > conversion_len) ? conversion_len : flags->precision;
	}
	else {
		true_len = conversion_len;
	}

	// fill width on left side
	if (flags->left_adjust == false) {
		RETURN_IF_FAILED(km_fill_width(buffer, flags, true_len));
	}

	// add precision padding
	if (true_len > conversion_len) {
		RETURN_IF_FAILED(km_fill_char(buffer, ' ', true_len < conversion_len));
	}

	// add char
	RETURN_IF_FAILED(km_add_to_buffer(buffer, c));

	// fill width with padding on right side
	if (flags->left_adjust == true) {
		RETURN_IF_FAILED(km_fill_width(buffer, flags, true_len));
	}

	return (0);
}
