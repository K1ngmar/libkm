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

int km_flush_buffer_fd(printf_buffer_t* buffer)
{
	if (write(buffer->fd, buffer->str, buffer->length) < 0)
		return (-1); // maybe still set length to 0?
	buffer->length = 0;
	return (0);
}

int km_flush_buffer_str(printf_buffer_t* buffer)
{
	// normally the buffer is not Null terminated,
	// strjoin expects null terminated string
	buffer->str[buffer->length] = '\0';
	char* str =	km_safe_strjoin(buffer->sprintf_string, buffer->sprintf_string);

	// free old string
	free(buffer->sprintf_string);
	buffer->length = 0;
	
	if (str == NULL) {
		return (-1);
	}
	buffer->sprintf_string = str;
	return (0);
}

int km_add_to_buffer(printf_buffer_t* buffer, char c)
{
	// adding character will exceed capacity, flush buffer
	if (buffer->length + 1 == PRINTF_BUFFER_SIZE) {
		if (buffer->flush(buffer) < 0)
			return (-1);
	}
	buffer->str[buffer->length] = c;
	buffer->length++;
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
		len = MIN(length, PRINTF_BUFFER_SIZE - buffer->length);
		km_memset(buffer->str + buffer->length, c, length);
		buffer->length += len;

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
