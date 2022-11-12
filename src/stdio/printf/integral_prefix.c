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

////////////////
// set prefix //
////////////////

int set_prefix_decimal(printf_buffer_t* buffer, const t_printf_flags* flags, uint64_t nbr, bool is_negative, int(*f)(int))
{
	(void)f;
	(void)nbr;
	if (is_negative == true)
		RETURN_IF_FAILED(km_add_to_buffer(buffer, '-'));
	else if (flags->always_signed == true)
		RETURN_IF_FAILED(km_add_to_buffer(buffer, '+'));
	else if (flags->blank == true)
		RETURN_IF_FAILED(km_add_to_buffer(buffer, ' '));
	return (0);
}

int set_prefix_hex(printf_buffer_t* buffer, const t_printf_flags* flags, uint64_t nbr, bool is_negative, int(*case_modifier)(int))
{
	(void)is_negative;
	if (flags->alternate_form == true && nbr != 0) {
		RETURN_IF_FAILED(km_add_to_buffer(buffer, '0'));
		RETURN_IF_FAILED(km_add_to_buffer(buffer, case_modifier('X')));
	}
	return (0);
}

int set_prefix_address(printf_buffer_t* buffer, const t_printf_flags* flags, uint64_t nbr, bool is_negative, int(*f)(int))
{
	(void)flags;
	(void)nbr;
	(void)is_negative;
	(void)f;
	RETURN_IF_FAILED(km_add_to_buffer(buffer, '0'));
	RETURN_IF_FAILED(km_add_to_buffer(buffer, 'x'));
	return (0);
}

int set_prefix_octal(printf_buffer_t* buffer, const t_printf_flags* flags, uint64_t nbr, bool is_negative, int(*f)(int))
{
	(void)buffer;
	(void)flags;
	(void)nbr;
	(void)is_negative;
	(void)f;
	return (0);
}

///////////////////
// Prefix length //
///////////////////

int prefix_length_decimal(bool is_negative, uint64_t nbr, const t_printf_flags* flags)
{
	(void)nbr;
	if (is_negative == true || flags->always_signed == true || flags->blank == true)
		return (1);
	return (0);
}

int prefix_length_hex(bool is_negative, uint64_t nbr, const t_printf_flags* flags)
{
	(void)is_negative;
	if (flags->alternate_form == true && nbr != 0)
		return (2); // 0x
	return (0);
}

int prefix_length_address(bool is_negative, uint64_t nbr, const t_printf_flags* flags)
{
	(void)flags;
	(void)nbr;
	(void)is_negative;
	return (2); // 0x
}

int prefix_length_octal(bool is_negative, uint64_t nbr, const t_printf_flags* flags)
{
	(void)flags;
	(void)nbr;
	(void)is_negative;
	return (0);
}
