
#include "libkm/io/printf.h"

#include <criterion/criterion.h>
#include <string.h>

#define VERY_LONG_STRING "I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS."

#define TEST_SIZE 1024

char*	km = NULL;
char*	og = NULL;

void suitesetup(void) {
	km = malloc(sizeof(char) * TEST_SIZE);
	og = malloc(sizeof(char) * TEST_SIZE);
}


void suiteteardown(void) {
	free(km);
	free(og);
	km = NULL;
	og = NULL;
}

TestSuite(printf_test, .init=suitesetup, .fini=suiteteardown);

Test(printf_test, char_test)
{
	cr_assert(
		km_sprintf(&km, "%c", 'a')
		==
		sprintf(og, "%c", 'a')
	);
	cr_assert_str_eq(km, og);

	cr_assert(
		km_sprintf(&km, "%c\n", 'b')
		==
		sprintf(og, "%c\n", 'b')
	);
	cr_assert_str_eq(km, og);

	cr_assert(
		km_sprintf(&km, "scooperdie%c\n", 'd')
		==
		sprintf(og, "scooperdie%c\n", 'd')
	);
	cr_assert_str_eq(km, og);
	
	cr_assert(
		km_sprintf(&km, "scooperdie%cswoop\n", 'e')
		==
		sprintf(og, "scooperdie%cswoop\n", 'e')
	);
	cr_assert_str_eq(km, og);
	
	cr_assert(
		km_sprintf(&km, "%cswoop\n", 'g')
		==
		sprintf(og, "%cswoop\n", 'g')
	);
	cr_assert_str_eq(km, og);
	
	cr_assert(
		km_sprintf(&km, "%c%c&%c%c", 'g', 'l', 'h', 'f')
		==
		sprintf(og, "%c%c&%c%c", 'g', 'l', 'h', 'f')
	);
	cr_assert_str_eq(km, og);
}

Test(printf_test, test_width)
{
	cr_assert(
		km_sprintf(&km, "%5c", 'a')
		==
		sprintf(og, "%5c", 'a')
	);
	cr_assert_str_eq(km, og);

	cr_assert(
		km_sprintf(&km, "%3c\n", 'b')
		==
		sprintf(og, "%3c\n", 'b')
	);
	cr_assert_str_eq(km, og);

	cr_assert(
		km_sprintf(&km, "scooperdie%4c\n", 'd')
		==
		sprintf(og, "scooperdie%4c\n", 'd')
	);
	cr_assert_str_eq(km, og);
	
	cr_assert(
		km_sprintf(&km, "scooperdie%4cswoop\n", 'e')
		==
		sprintf(og, "scooperdie%4cswoop\n", 'e')
	);
	cr_assert_str_eq(km, og);
	
	cr_assert(
		km_sprintf(&km, "%20cswoop\n", 'g')
		==
		sprintf(og, "%20cswoop\n", 'g')
	);
	cr_assert_str_eq(km, og);
	
	cr_assert(
		km_sprintf(&km, "%2c%3c&%4c%5c", 'g', 'l', 'h', 'f')
		==
		sprintf(og, "%2c%3c&%4c%5c", 'g', 'l', 'h', 'f')
	);
	cr_assert_str_eq(km, og);
}
