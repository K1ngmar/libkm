
#include <criterion/criterion.h>
#include <libkm.h>
#include <stdio.h>

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

Test(printf_test, test_no_conversion) {

	km_sprintf(&km, "");
	sprintf(og, "");
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "hello world");
	sprintf(og, "hello world");
	cr_assert_str_eq(km, og);
}
