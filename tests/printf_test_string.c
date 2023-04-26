
#include "libkm/io/printf.h"

#include <criterion/criterion.h>
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

Test(printf_test, test_string)
{
	cr_assert(
		km_sprintf(&km, "%s", "swooperdiewoop")
		==
		sprintf(og, "%s", "swooperdiewoop")
	);
	cr_assert_str_eq(km, og);

	cr_assert(
		km_sprintf(&km, "%s\n", "swooperdiewoop")
		==
		sprintf(og, "%s\n", "swooperdiewoop")
	);
	cr_assert_str_eq(km, og);

	cr_assert(
		km_sprintf(&km, "scooperdie%s\n", "swooperdiewoop")
		==
		sprintf(og, "scooperdie%s\n", "swooperdiewoop")
	);
	cr_assert_str_eq(km, og);
	
	cr_assert(
		km_sprintf(&km, "%s", (char*)NULL)
		==
		sprintf(og, "%s", (char*)NULL)
	);
	cr_assert_str_eq(km, og);

	cr_assert(
		km_sprintf(&km, "%s\n", (char*)NULL)
		==
		sprintf(og, "%s\n", (char*)NULL)
	);
	cr_assert_str_eq(km, og);
	
	cr_assert(
		km_sprintf(&km, "scooperdie%s\n", (char*)NULL)
		==
		sprintf(og, "scooperdie%s\n", (char*)NULL)
	);
	cr_assert_str_eq(km, og);
}

Test(printf_test, test_precision_string)
{
	for (int size = 0; size < 42; size++) {
		cr_assert(
			km_sprintf(&km, "%.*s", size, "swooperdiewoop")
			==
			sprintf(og, "%.*s", size, "swooperdiewoop")
		);
		cr_assert_str_eq(km, og);

		cr_assert(
			km_sprintf(&km, "%.*s", size, (char*)NULL)
			==
			sprintf(og, "%.*s", size, (char*)NULL)
		);
		cr_assert_str_eq(km, og);
	}
}

Test(printf_test, test_width_string)
{
	for (int size = 0; size < 42; size++) {
		cr_assert(
			km_sprintf(&km, "%*s", size, "swooperdiewoop")
			==
			sprintf(og, "%*s", size, "swooperdiewoop")
		);
		cr_assert_str_eq(km, og);

		cr_assert(
			km_sprintf(&km, "%*s", size, (char*)NULL)
			==
			sprintf(og, "%*s", size, (char*)NULL)
		);
		cr_assert_str_eq(km, og);
	}
}

Test(printf_test, test_precision_width_string)
{
	for (int width = 0; width < 42; width++)
	{
		for (int precision = 0; precision < 50; precision++)
		{
			cr_expect_eq(
				km_sprintf(&km, "%*.*s", width, precision, "swooperdiewoop"),
				sprintf(og, "%*.*s", width, precision, "swooperdiewoop")
			);
			cr_assert_str_eq(km, og);

			cr_expect_eq(
				km_sprintf(&km, "%*.*s", width, precision, (char*)NULL),
				sprintf(og, "%*.*s", width, precision, (char*)NULL)
			);
			cr_assert_str_eq(km, og);
		}
	}
}

Test(printf_test, test_precision_width_left_adjust_string)
{
	for (int width = 0; width < 42; width++)
	{
		for (int precision = 0; precision < 50; precision++)
		{
			cr_expect_eq(
				km_sprintf(&km, "%-*.*s", width, precision, "swooperdiewoop"),
				sprintf(og, "%-*.*s", width, precision, "swooperdiewoop")
			);
			cr_assert_str_eq(km, og);

			cr_expect_eq(
				km_sprintf(&km, "%-*.*s", width, precision, (char*)NULL),
				sprintf(og, "%-*.*s", width, precision, (char*)NULL)
			);
			cr_assert_str_eq(km, og);
		}
	}
}
