
#include <sys/time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libkm.h>

unsigned long	get_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

#define SIZE 1024 * 1024 * 1024

char* str;
char* str2;

int pos[] = {
	1024 * 1024 + 1337,
	1024 * 1024 + 420,
	1024 * 1024 + 69,
	1024 * 1023 + 420,
	1024 * 1022 + 420,
	1024 * 1021 + 420,
	1024 * 1020 + 420,
	};

void	bm(size_t(*f)(const char*), const char* name)
{
	size_t len = 0;
	size_t len2 = 0;

	str = malloc(sizeof(char) * SIZE + 1);
	str2 = malloc(sizeof(char) * SIZE + 1);

	for (size_t i = 0; i < SIZE; i++)
		str[i] = 'a' + (i % 26);
	str[SIZE] = '\0';

	memcpy(str2, str, SIZE);

	size_t start = get_time();
	for (size_t j = 8; j > 0; j--) {
		for (size_t i = 0; i < 7; i++) {
			len += f(str);
			len2 += f(str2);
			str[pos[i] + i] = '\0';
			str2[pos[i] + i + j] = '\0';
		}
	}
	size_t end = get_time();
	printf("%s took: %zu\n", name, end - start);
	dprintf(4, "%lu", len * len2);

	free(str);
	free(str2);
}

size_t glibc_strlen (const char *str);

size_t og_strlen(const char* str)
{
	size_t i = 0;

	while (str[i])
		i++;
	return (i);
}

int main()
{

	bm(km_strlen,		"km_strlen   ");
	bm(strlen,			"libc_strlen ");
	bm(glibc_strlen,	"glibc_strlen");
	bm(og_strlen,		"og_strlen   ");
}
