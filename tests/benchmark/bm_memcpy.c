
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <libkm.h>
#include <stdlib.h>

#define VERY_LONG_STRING "I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS."


#define TEST_SIZE 1024 * 1024 * 1024

void	*fm_memcpy(void *dst, const void *src, size_t n);

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == src)
		return (dest);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

unsigned long	get_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

static void time_func(void*(*f)(void* restrict, const void* restrict, size_t), const char* name) {
	int*	src = malloc(sizeof(int) * TEST_SIZE);
	int*	dst = malloc(sizeof(int) * TEST_SIZE);
	size_t	start;
	size_t	end;

	for (size_t i = 0; i < TEST_SIZE; i++)
		src[i] = i;

	start = get_time();
	f(dst, src, TEST_SIZE * sizeof(int));
	end = get_time();

	printf("%s took: %lu ms\n", name, end - start);
	for (size_t i = 0; i < TEST_SIZE; ++i) {
		if (dst[i] != src[i]) {
			printf("dst[i] = %d, src[i] = %d\n", dst[i], src[i]);
			printf("Copy went wrong on index: %zu\n", i);
			break ;
		}
	}
	free(src);
	free(dst);
}

int main()
{
	time_func(km_memcpy, "km_memcpy");
	time_func(memcpy,	 "og_memcpy");
	time_func(ft_memcpy, "ft_memcpy");
}