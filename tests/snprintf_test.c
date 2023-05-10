
#include "libkm/io/printf.h"

#include <criterion/criterion.h>
#include <stdio.h>
#include <stdint.h>

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

TestSuite(sn_printf_test, .init=suitesetup, .fini=suiteteardown);

Test(sn_printf_test, test_no_conversion) {

	#ifndef __linux__

		cr_assert(
			km_snprintf(km, TEST_SIZE, "")
			==
			snprintf(og, TEST_SIZE, "")
		);
		cr_assert_str_eq(km, og);


	#endif

	km_snprintf(km, TEST_SIZE, "hello world");
	snprintf(og, TEST_SIZE, "hello world");
	cr_assert_str_eq(km, og);

	// passed as allocated
	cr_assert(
		km_snprintf(km, TEST_SIZE, "THIS IS A VERY LONG STRING ThAT WILL SURPASS THE LENGTH OF PRINTF_BUFFER_SIZE and should trigger a reallco that definitely will work the first time i test it right? Well this is not enough characters yet since it is by default set to 256 and we have not reached that yet :( but we will very soon and that will test if this will work or not :D")
		==
		snprintf(og, TEST_SIZE, "THIS IS A VERY LONG STRING ThAT WILL SURPASS THE LENGTH OF PRINTF_BUFFER_SIZE and should trigger a reallco that definitely will work the first time i test it right? Well this is not enough characters yet since it is by default set to 256 and we have not reached that yet :( but we will very soon and that will test if this will work or not :D")
	);
	cr_assert_str_eq(km, og);
	
}

Test(sn_printf_test, decimal)
{
	km_snprintf(km, TEST_SIZE, "d = %d", 100);
	snprintf(og, TEST_SIZE, "d = %d", 100);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "0 = %d", 0);
	snprintf(og, TEST_SIZE, "0 = %d", 0);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "9 = %d", 9);
	snprintf(og, TEST_SIZE, "9 = %d", 9);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "-9 = %d", -9);
	snprintf(og, TEST_SIZE, "-9 = %d", -9);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "INT_MAX = %d", INT32_MAX);
	snprintf(og, TEST_SIZE, "INT_MAX = %d", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "INT_MIN = %d", INT32_MIN);
	snprintf(og, TEST_SIZE, "INT_MIN = %d", INT32_MIN);
	cr_assert_str_eq(km, og);
}

Test(sn_printf_test, decimal_long)
{
	km_snprintf(km, TEST_SIZE, "%ld", (long)100);
	snprintf(og, TEST_SIZE, "%ld", (long)100);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%ld", (long)0);
	snprintf(og, TEST_SIZE, "%ld", (long)0);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%ld", (long)9);
	snprintf(og, TEST_SIZE, "%ld", (long)9);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%ld", (long)-9);
	snprintf(og, TEST_SIZE, "%ld", (long)-9);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%ld", (long)INT32_MAX);
	snprintf(og, TEST_SIZE, "%ld", (long)INT32_MAX);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%ld", (long)INT32_MIN);
	snprintf(og, TEST_SIZE, "%ld", (long)INT32_MIN);
	cr_assert_str_eq(km, og);

	#ifdef __linux__

		km_snprintf(km, TEST_SIZE, "%ld", INT64_MAX);
		snprintf(og, TEST_SIZE, "%ld", INT64_MAX);
		cr_assert_str_eq(km, og);


		km_snprintf(km, TEST_SIZE, "%ld", INT64_MIN);
		snprintf(og, TEST_SIZE, "%ld", INT64_MIN);
		cr_assert_str_eq(km, og);


	#else

		km_snprintf(km, TEST_SIZE, "%lld", INT64_MAX);
		snprintf(og, TEST_SIZE, "%lld", INT64_MAX);
		cr_assert_str_eq(km, og);


		km_snprintf(km, TEST_SIZE, "%lld", INT64_MIN);
		snprintf(og, TEST_SIZE, "%lld", INT64_MIN);
		cr_assert_str_eq(km, og);


	#endif
}

Test(sn_printf_test, decimal_u)
{
	km_snprintf(km, TEST_SIZE, "%u", (unsigned int)100);
	snprintf(og, TEST_SIZE, "%u", (unsigned int)100);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%u", (unsigned int)0);
	snprintf(og, TEST_SIZE, "%u", (unsigned int)0);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%u", (unsigned int)9);
	snprintf(og, TEST_SIZE, "%u", (unsigned int)9);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%u", (unsigned int)-9);
	snprintf(og, TEST_SIZE, "%u", (unsigned int)-9);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%u", (unsigned int)UINT32_MAX);
	snprintf(og, TEST_SIZE, "%u", (unsigned int)UINT32_MAX);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%u", (unsigned int)UINT32_MAX + 1);
	snprintf(og, TEST_SIZE, "%u", (unsigned int)UINT32_MAX + 1);
	cr_assert_str_eq(km, og);
}

Test(sn_printf_test, decimal_ulong)
{
	km_snprintf(km, TEST_SIZE, "%lu", (unsigned long)100);
	snprintf(og, TEST_SIZE, "%lu", (unsigned long)100);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%lu", (unsigned long)0);
	snprintf(og, TEST_SIZE, "%lu", (unsigned long)0);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%lu", (unsigned long)9);
	snprintf(og, TEST_SIZE, "%lu", (unsigned long)9);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%lu", (unsigned long)-9);
	snprintf(og, TEST_SIZE, "%lu", (unsigned long)-9);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%lu", (unsigned long)UINT32_MAX);
	snprintf(og, TEST_SIZE, "%lu", (unsigned long)UINT32_MAX);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%lu", (unsigned long)UINT32_MAX + 1);
	snprintf(og, TEST_SIZE, "%lu", (unsigned long)UINT32_MAX + 1);
	cr_assert_str_eq(km, og);

	#ifdef __linux__

	km_snprintf(km, TEST_SIZE, "%lu", UINT64_MAX);
	snprintf(og, TEST_SIZE, "%lu", UINT64_MAX);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%lu", UINT64_MAX + 1);
	snprintf(og, TEST_SIZE, "%lu", UINT64_MAX + 1);
	cr_assert_str_eq(km, og);

	#else

	km_snprintf(km, TEST_SIZE, "%llu", UINT64_MAX);
	snprintf(og, TEST_SIZE, "%llu", UINT64_MAX);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%llu", UINT64_MAX + 1);
	snprintf(og, TEST_SIZE, "%llu", UINT64_MAX + 1);
	cr_assert_str_eq(km, og);

	#endif
}

Test(sn_printf_test, decimal_sign) {

	km_snprintf(km, TEST_SIZE, "%+d", 0);
	snprintf(og, TEST_SIZE, "%+d", 0);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%+d", 1);
	snprintf(og, TEST_SIZE, "%+d", 1);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%+d", INT32_MAX);
	snprintf(og, TEST_SIZE, "%+d", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%+d", INT32_MIN);
	snprintf(og, TEST_SIZE, "%+d", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%+d", -1);
	snprintf(og, TEST_SIZE, "%+d", -1);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%+d", -17);
	snprintf(og, TEST_SIZE, "%+d", -17);
	cr_assert_str_eq(km, og);
}

Test(sn_printf_test, decimal_field_width)
{
	km_snprintf(km, TEST_SIZE, "%20d", 0);
	snprintf(og, TEST_SIZE, "%20d", 0);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%0d", 0);
	snprintf(og, TEST_SIZE, "%0d", 0);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%1d", 1);
	snprintf(og, TEST_SIZE, "%1d", 1);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%1d", 56);
	snprintf(og, TEST_SIZE, "%1d", 56);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%5d", 56);
	snprintf(og, TEST_SIZE, "%5d", 56);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%1d", -6);
	snprintf(og, TEST_SIZE, "%1d", -6);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%5d", -65);
	snprintf(og, TEST_SIZE, "%5d", -65);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%10d", INT32_MAX);
	snprintf(og, TEST_SIZE, "%10d", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%11d", INT32_MIN);
	snprintf(og, TEST_SIZE, "%11d", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%2d", -1);
	snprintf(og, TEST_SIZE, "%2d", -1);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%3d", -17);
	snprintf(og, TEST_SIZE, "%3d", -17);
	cr_assert_str_eq(km, og);
	
	km_snprintf(km, TEST_SIZE, "%2d", 17);
	snprintf(og, TEST_SIZE, "%2d", 17);
	cr_assert_str_eq(km, og);
}

Test(sn_printf_test, decimal_precision)
{
	km_snprintf(km, TEST_SIZE, "%.20d", 0);
	snprintf(og, TEST_SIZE, "%.20d", 0);
	cr_assert_str_eq(km, og);

	// km_snprintf(km, TEST_SIZE, "%.0d", 0);
	// snprintf(og, TEST_SIZE, "%.0d", 0);
	// cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%.1d", 1);
	snprintf(og, TEST_SIZE, "%.1d", 1);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%.1d", 56);
	snprintf(og, TEST_SIZE, "%.1d", 56);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%.d", 439);
	snprintf(og, TEST_SIZE, "%.d", 439);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%.d", -439);
	snprintf(og, TEST_SIZE, "%.d", -439);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%.5d", 56);
	snprintf(og, TEST_SIZE, "%.5d", 56);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%.1d", -6);
	snprintf(og, TEST_SIZE, "%.1d", -6);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%.10d", INT32_MAX);
	snprintf(og, TEST_SIZE, "%.10d", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%.11d", INT32_MIN);
	snprintf(og, TEST_SIZE, "%.11d", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%.2d", -1);
	snprintf(og, TEST_SIZE, "%.2d", -1);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%.3d", -17);
	snprintf(og, TEST_SIZE, "%.3d", -17);
	cr_assert_str_eq(km, og);
	
	km_snprintf(km, TEST_SIZE, "%.2d", 17);
	snprintf(og, TEST_SIZE, "%.2d", 17);
	cr_assert_str_eq(km, og);
}

Test(sn_printf_test, decimal_precision_and_width)
{
	km_snprintf(km, TEST_SIZE, "%10.20d", 0);
	snprintf(og, TEST_SIZE, "%10.20d", 0);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%20.10d", 0);
	snprintf(og, TEST_SIZE, "%20.10d", 0);
	cr_assert_str_eq(km, og);

	// km_snprintf(km, TEST_SIZE, "%.0d", 0);
	// snprintf(og, TEST_SIZE, "%.0d", 0);
	// cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%2.1d", 1);
	snprintf(og, TEST_SIZE, "%2.1d", 1);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%2.3d", 56);
	snprintf(og, TEST_SIZE, "%1.3d", 56);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%3.3d", 439);
	snprintf(og, TEST_SIZE, "%3.3d", 439);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%4.4d", -439);
	snprintf(og, TEST_SIZE, "%4.4d", -439);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%5.5d", 56);
	snprintf(og, TEST_SIZE, "%5.5d", 56);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%2.2d", -6);
	snprintf(og, TEST_SIZE, "%2.2d", -6);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%5.6d", 56);
	snprintf(og, TEST_SIZE, "%5.6d", 56);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%2.3d", -6);
	snprintf(og, TEST_SIZE, "%2.3d", -6);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%11.10d", INT32_MAX);
	snprintf(og, TEST_SIZE, "%11.10d", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%12.11d", INT32_MIN);
	snprintf(og, TEST_SIZE, "%12.11d", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%5.2d", -1);
	snprintf(og, TEST_SIZE, "%5.2d", -1);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%5.9d", -17);
	snprintf(og, TEST_SIZE, "%5.9d", -17);
	cr_assert_str_eq(km, og);
	
	km_snprintf(km, TEST_SIZE, "%2.6d", 17);
	snprintf(og, TEST_SIZE, "%2.6d", 17);
	cr_assert_str_eq(km, og);
}

Test(sn_printf_test, decimal_precision_and_width_blank)
{
	km_snprintf(km, TEST_SIZE, "% 10.20d", 0);
	snprintf(og, TEST_SIZE, "% 10.20d", 0);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "% 20.10d", 0);
	snprintf(og, TEST_SIZE, "% 20.10d", 0);
	cr_assert_str_eq(km, og);

	// km_snprintf(km, TEST_SIZE, "% .0d", 0);
	// snprintf(og, TEST_SIZE, "% .0d", 0);
	// cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "% 2.1d", 1);
	snprintf(og, TEST_SIZE, "% 2.1d", 1);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "% 2.3d", 56);
	snprintf(og, TEST_SIZE, "% 1.3d", 56);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "% 3.3d", 439);
	snprintf(og, TEST_SIZE, "% 3.3d", 439);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "% 4.4d", -439);
	snprintf(og, TEST_SIZE, "% 4.4d", -439);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "% 5.5d", 56);
	snprintf(og, TEST_SIZE, "% 5.5d", 56);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "% 2.2d", -6);
	snprintf(og, TEST_SIZE, "% 2.2d", -6);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "% 5.6d", 56);
	snprintf(og, TEST_SIZE, "% 5.6d", 56);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "% 2.3d", -6);
	snprintf(og, TEST_SIZE, "% 2.3d", -6);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "% 11.10d", INT32_MAX);
	snprintf(og, TEST_SIZE, "% 11.10d", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "% 12.11d", INT32_MIN);
	snprintf(og, TEST_SIZE, "% 12.11d", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "% 5.2d", -1);
	snprintf(og, TEST_SIZE, "% 5.2d", -1);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "% 5.9d", -17);
	snprintf(og, TEST_SIZE, "% 5.9d", -17);
	cr_assert_str_eq(km, og);
	
	km_snprintf(km, TEST_SIZE, "% 2.6d", 17);
	snprintf(og, TEST_SIZE, "% 2.6d", 17);
	cr_assert_str_eq(km, og);
}

Test(sn_printf_test, decimal_precision_and_width_left_adjust)
{
	cr_assert(
		km_snprintf(km, TEST_SIZE, "%-10.20d", 0)
		==
		snprintf(og, TEST_SIZE, "%-10.20d", 0)
	);
	cr_assert_str_eq(km, og);

	cr_assert(
		km_snprintf(km, TEST_SIZE, "%-20.10d", 0)
		==
		snprintf(og, TEST_SIZE, "%-20.10d", 0)
	);
	cr_assert_str_eq(km, og);

	// km_snprintf(km, TEST_SIZE, "%-.0d", 0);
	// snprintf(og, TEST_SIZE, "%-.0d", 0);
	// cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%-2.1d", 1);
	snprintf(og, TEST_SIZE, "%-2.1d", 1);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%-2.3d", 56);
	snprintf(og, TEST_SIZE, "%-1.3d", 56);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%-3.3d", 439);
	snprintf(og, TEST_SIZE, "%-3.3d", 439);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%-4.4d", -439);
	snprintf(og, TEST_SIZE, "%-4.4d", -439);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%-5.5d", 56);
	snprintf(og, TEST_SIZE, "%-5.5d", 56);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%-2.2d", -6);
	snprintf(og, TEST_SIZE, "%-2.2d", -6);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%-5.6d", 56);
	snprintf(og, TEST_SIZE, "%-5.6d", 56);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%-2.3d", -6);
	snprintf(og, TEST_SIZE, "%-2.3d", -6);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%-11.10d", INT32_MAX);
	snprintf(og, TEST_SIZE, "%-11.10d", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%-12.11d", INT32_MIN);
	snprintf(og, TEST_SIZE, "%-12.11d", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%-5.2d", -1);
	snprintf(og, TEST_SIZE, "%-5.2d", -1);
	cr_assert_str_eq(km, og);

	km_snprintf(km, TEST_SIZE, "%-5.9d", -17);
	snprintf(og, TEST_SIZE, "%-5.9d", -17);
	cr_assert_str_eq(km, og);
	
	km_snprintf(km, TEST_SIZE, "%-2.6d", 17);
	snprintf(og, TEST_SIZE, "%-2.6d", 17);
	cr_assert_str_eq(km, og);
}
