
#include <libkm.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#define VERY_LONG_STRING "I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS."

#define TEST_SIZE 500000

unsigned long	get_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

static void time_decimal()
{
	printf("----Test decimal----\n");
	size_t start = 0;
	size_t end = 0;

	start = get_time();
	for (int i = -TEST_SIZE; i < TEST_SIZE; i++)
		km_dprintf(STDERR_FILENO, "d = %d\n", i);
	end = get_time();
	km_printf("km_printf took: %lu ms\n", end - start);
	
	start = get_time();
	for (int i = -TEST_SIZE; i < TEST_SIZE; i++)
		dprintf(STDERR_FILENO, "d = %d\n", i);
	end = get_time();
	km_printf("og_printf took: %lu ms\n", end - start);
}

int main()
{
	time_decimal();
}
