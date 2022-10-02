
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

Test(printf_test, test_decimal) {

	km_sprintf(&km, "d = %d", 100);
	sprintf(og, "d = %d", 100);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "0 = %d", 0);
	sprintf(og, "0 = %d", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "9 = %d", 9);
	sprintf(og, "9 = %d", 9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "-9 = %d", -9);
	sprintf(og, "-9 = %d", -9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "INT_MAX = %d", INT32_MAX);
	sprintf(og, "INT_MAX = %d", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "INT_MIN = %d", INT32_MIN);
	sprintf(og, "INT_MIN = %d", INT32_MIN);
	cr_assert_str_eq(km, og);
}
