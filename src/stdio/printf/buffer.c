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
#include <unistd.h>
#include <stdlib.h>

int km_flush_buffer_fd(printf_buffer_t* buffer)
{
	if (write(buffer->fd, buffer->str, buffer->len) < 0)
		return (-1); // maybe still set length to 0?
	buffer->len = 0;
	return (0);
}

int km_flush_buffer_str(printf_buffer_t* buffer)
{
	// normally the buffer is not Null terminated,
	// strjoin expects null terminated string
	buffer->str[buffer->len] = '\0';

	char* str =	km_safe_strjoin(buffer->sprintf_str, buffer->str);

	// free old string
	free(buffer->sprintf_str);
	buffer->sprintf_str = str;
	buffer->len = 0;

	if (str == NULL) {
		return (-1);
	}
	return (0);
}

int km_add_to_buffer(printf_buffer_t* buffer, char c)
{
	// adding character will exceed capacity, flush buffer
	if (buffer->len + 1 == buffer->max_len) {
		if (buffer->flush(buffer) < 0)
			return (-1);
	}
	buffer->str[buffer->len] = c;
	buffer->len++;
	// newline is found, flush buffer (only when writing to fd)
	if (buffer->flush == km_flush_buffer_fd && c == '\n') {
		if (buffer->flush(buffer) < 0)
			return (-1);
	}
	return (0);
}

int km_fill_char(printf_buffer_t* buffer, char c, int length)
{
	int len;

	while (length > 0) {
		len = MIN(length, buffer->max_len - buffer->len);
		km_memset(buffer->str + buffer->len, c, length);
		buffer->len += len;

		length -= len;
		if (length > 0) {
			if (buffer->flush(buffer) < 0)
				return (-1);
		}
	}
	return (0);
}

int km_fill_width(printf_buffer_t* buffer, const t_printf_flags* flags, int conversion_width)
{
	char c = (flags->zero_padded) ? '0' : ' ';
	int width = flags->field_width - conversion_width;
	
	return km_fill_char(buffer, c, width);
}
