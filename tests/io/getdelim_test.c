
#include <libkm.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
	char	*line;
	int	fd = open("tests/io/test", 'r');
	ssize_t ret;

	while ((ret = km_getdelim(&line, '\n', fd)) > 0) {
		free(line);
	}
	return (ret);
}