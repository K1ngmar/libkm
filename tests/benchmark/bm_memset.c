
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <libkm.h>
#include <stdlib.h>

#define VERY_LONG_STRING "I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS."


#define TEST_SIZE 1024 * 1024 * 1024

unsigned long	get_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	*ft_memset(void *ptr, int x, size_t n)
{
	size_t	i;
	char	*c;

	i = 0;
	c = ptr;
	while (i != n)
	{
		c[i] = (char)x;
		i++;
	}
	return (ptr);
}

static void time_func(void*(*f)(void*, int, size_t), const char* name) {
	int*	dst = malloc(sizeof(int) * TEST_SIZE);
	size_t	start;
	size_t	end;

	for (size_t i = 0; i < TEST_SIZE; i++)
		dst[i] = i;

	start = get_time();
	dst = f(dst, 'a', TEST_SIZE * sizeof(int));
	end = get_time();

	for (size_t i = 0; i < TEST_SIZE; i++)
		dst[i] ^= 2 * i;
	printf("%s took: %lu ms\n", name, end - start);
	free(dst);
}

int main()
{
	time_func(km_memset, "km_memset");
	time_func(memset,	 "og_memset");
	time_func(ft_memset, "ft_memset");
}