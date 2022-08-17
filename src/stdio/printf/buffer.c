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

int km_flush_buffer(t_printf_buffer* buffer)
{
	if (write(buffer->fd, buffer->str, buffer->length) < 0)
		return (-1); // maybe still set length to 0?
	buffer->length = 0;
	return (0);
}

int km_add_to_buffer(t_printf_buffer* buffer, char c)
{
	// adding character will exceed capacity, flush buffer
	if (buffer->length + 1 == PRINTF_BUFFER_SIZE)
		if (km_flush_buffer(buffer) < 0)
			return (-1);
	buffer->str[buffer->length] = c;
	buffer->length++;
	// newline is found, flush buffer
	if (c == '\n')
		if (km_flush_buffer(buffer) < 0)
			return (-1);
}

void km_fill_width(char* str, const t_printf_flags* flags, int conversion_length)
{
	char c = (flags->zero_padded) ? '0' : ' ';
	int len = 0;

	if (flags->field_width > conversion_length)
		len = flags->field_width - conversion_length;
	
	if (len == 0)
		return ;

	if (flags->left_adjust == false)
		km_memset(str + conversion_length, c, len);
	else
		km_memset(str, c, len);
}
