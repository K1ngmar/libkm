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

int km_flush_buffer(t_printf_buffer* buffer)
{
	if (write(buffer->fd, buffer->str, buffer->length) < 0)
		return (-1); // maybe still set length to 0?
	buffer->length = 0;
	return (0);
}

int km_add_to_buffer(t_printf_buffer* buffer, char c)
{
	if (buffer->length + 1 == PRINTF_BUFFER_SIZE)
		if (km_flush_buffer(buffer) < 0)
			return (-1);
	buffer->str[buffer->length] = c;
	buffer->length++;
}
