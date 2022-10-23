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

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <libkm.h>

#ifndef GETDELIM_BUFFER_SIZE
# define GETDELIM_BUFFER_SIZE 256
#endif

/*
** length of string till delimiter or end of string
*/
static size_t	line_len(const char *str, int delim)
{
	size_t i = 0;

	while (str[i] != delim && str[i] != '\0')
		i++;
	return (i);
}

/*
** moves everything in buffer after pos to the beginning of the string
*/
static void	prep_buf(char* buf, size_t pos)
{
	km_memcpy(buf, buf + pos + 1, GETDELIM_BUFFER_SIZE - pos);
	buf[GETDELIM_BUFFER_SIZE - pos] = '\0';
}

/*
** concatonate buffer to line
*/
static char* line_join(char* line, char *buf, size_t pos, size_t len)
{
	line = km_stupid_realloc(line, len, len + pos + 1);
	if (line == NULL)
		return (NULL);
	km_strlcat(line, buf, len + pos + 1);
	return (line);
}

/*
** reads from fd, returns line once a delimiter or the end of the file is reached;
*/
ssize_t	km_getdelim(char** restrict line, int delim, int fd)
{
	static char buf[GETDELIM_BUFFER_SIZE + 1];
	size_t len = 0;
	size_t pos;
	ssize_t ret;

	if (fd < 0 || line == NULL || GETDELIM_BUFFER_SIZE <= 0)
		return (-1);

	*line = NULL;

	while (1) {
		// only read if buffer is empty
		if (buf[0] == '\0')
		{
			ret = read(fd, buf, GETDELIM_BUFFER_SIZE);
			if (ret < 0) {
				free(*line);
				return (-1);
			}
			if (ret == 0) {
				if (*line != NULL)
					return (len);
				return (0);
			}
			buf[ret] = '\0';
		}
		// add bytes read to line (till delim or hole buff if no delimiter was found)
		pos = line_len(buf, delim);
		*line = line_join(*line, buf, pos, len);
		len += pos;
		if (*line == NULL)
			return (-1);

		// prepare buffer for next call
		if (buf[pos] == delim) {
			prep_buf(buf, pos);
			break ;
		}
		else
			buf[0] = '\0';
	}
	return (len);
}

ssize_t	km_getline(char** restrict line, int fd) {
	return (km_getdelim(line, '\n', fd));
}
