
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

	cr_assert(
		km_sprintf(&km, "")
		==
		sprintf(og, "")
	);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "hello world");
	sprintf(og, "hello world");
	cr_assert_str_eq(km, og);

	// passed as allocated
	cr_assert(
		km_sprintf(&km, "THIS IS A VERY LONG STRING ThAT WILL SURPASS THE LENGTH OF PRINTF_BUFFER_SIZE and should trigger a reallco that definitely will work the first time i test it right? Well this is not enough characters yet since it is by default set to 256 and we have not reached that yet :( but we will very soon and that will test if this will work or not :D")
		==
		sprintf(og, "THIS IS A VERY LONG STRING ThAT WILL SURPASS THE LENGTH OF PRINTF_BUFFER_SIZE and should trigger a reallco that definitely will work the first time i test it right? Well this is not enough characters yet since it is by default set to 256 and we have not reached that yet :( but we will very soon and that will test if this will work or not :D")
	);
	cr_assert_str_eq(km, og);
	
	// passed as NULL
	char* km_str = NULL;
	cr_assert(
		km_sprintf(&km_str, "THIS IS A VERY LONG STRING ThAT WILL SURPASS THE LENGTH OF PRINTF_BUFFER_SIZE and should trigger a reallco that definitely will work the first time i test it right? Well this is not enough characters yet since it is by default set to 256 and we have not reached that yet :( but we will very soon and that will test if this will work or not :D")
		==
		sprintf(og, "THIS IS A VERY LONG STRING ThAT WILL SURPASS THE LENGTH OF PRINTF_BUFFER_SIZE and should trigger a reallco that definitely will work the first time i test it right? Well this is not enough characters yet since it is by default set to 256 and we have not reached that yet :( but we will very soon and that will test if this will work or not :D")
	);
	cr_assert_str_eq(km_str, og);
}

Test(printf_test, decimal)
{
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

Test(printf_test, decimal_long)
{
	km_sprintf(&km, "%ld", (long)100);
	sprintf(og, "%ld", (long)100);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%ld", (long)0);
	sprintf(og, "%ld", (long)0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%ld", (long)9);
	sprintf(og, "%ld", (long)9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%ld", (long)-9);
	sprintf(og, "%ld", (long)-9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%ld", (long)INT32_MAX);
	sprintf(og, "%ld", (long)INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%ld", (long)INT32_MIN);
	sprintf(og, "%ld", (long)INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lld", INT64_MAX);
	sprintf(og, "%lld", INT64_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lld", INT64_MIN);
	sprintf(og, "%lld", INT64_MIN);
	cr_assert_str_eq(km, og);
}

Test(printf_test, decimal_u)
{
	km_sprintf(&km, "%u", (unsigned int)100);
	sprintf(og, "%u", (unsigned int)100);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%u", (unsigned int)0);
	sprintf(og, "%u", (unsigned int)0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%u", (unsigned int)9);
	sprintf(og, "%u", (unsigned int)9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%u", (unsigned int)-9);
	sprintf(og, "%u", (unsigned int)-9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%u", (unsigned int)UINT32_MAX);
	sprintf(og, "%u", (unsigned int)UINT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%u", (unsigned int)UINT32_MAX + 1);
	sprintf(og, "%u", (unsigned int)UINT32_MAX + 1);
	cr_assert_str_eq(km, og);
}

Test(printf_test, decimal_ulong)
{
	km_sprintf(&km, "%lu", (unsigned long)100);
	sprintf(og, "%lu", (unsigned long)100);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lu", (unsigned long)0);
	sprintf(og, "%lu", (unsigned long)0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lu", (unsigned long)9);
	sprintf(og, "%lu", (unsigned long)9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lu", (unsigned long)-9);
	sprintf(og, "%lu", (unsigned long)-9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lu", (unsigned long)UINT32_MAX);
	sprintf(og, "%lu", (unsigned long)UINT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lu", (unsigned long)UINT32_MAX + 1);
	sprintf(og, "%lu", (unsigned long)UINT32_MAX + 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%llu", UINT64_MAX);
	sprintf(og, "%llu", UINT64_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%llu", UINT64_MAX + 1);
	sprintf(og, "%llu", UINT64_MAX + 1);
	cr_assert_str_eq(km, og);
}

Test(printf_test, decimal_sign) {

	km_sprintf(&km, "%+d", 0);
	sprintf(og, "%+d", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%+d", 1);
	sprintf(og, "%+d", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%+d", INT32_MAX);
	sprintf(og, "%+d", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%+d", INT32_MIN);
	sprintf(og, "%+d", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%+d", -1);
	sprintf(og, "%+d", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%+d", -17);
	sprintf(og, "%+d", -17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, decimal_field_width)
{
	km_sprintf(&km, "%20d", 0);
	sprintf(og, "%20d", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%0d", 0);
	sprintf(og, "%0d", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%1d", 1);
	sprintf(og, "%1d", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%1d", 56);
	sprintf(og, "%1d", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5d", 56);
	sprintf(og, "%5d", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%1d", -6);
	sprintf(og, "%1d", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5d", -65);
	sprintf(og, "%5d", -65);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%10d", INT32_MAX);
	sprintf(og, "%10d", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%11d", INT32_MIN);
	sprintf(og, "%11d", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%2d", -1);
	sprintf(og, "%2d", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%3d", -17);
	sprintf(og, "%3d", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%2d", 17);
	sprintf(og, "%2d", 17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, decimal_precision)
{
	km_sprintf(&km, "%.20d", 0);
	sprintf(og, "%.20d", 0);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%.d", 12);
	sprintf(og, "%.d", 12);
	cr_assert_str_eq(km, og);

	// km_sprintf(&km, "%.0d", 0);
	// sprintf(og, "%.0d", 0);
	// cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.1d", 1);
	sprintf(og, "%.1d", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.1d", 56);
	sprintf(og, "%.1d", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.d", 439);
	sprintf(og, "%.d", 439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.d", -439);
	sprintf(og, "%.d", -439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.5d", 56);
	sprintf(og, "%.5d", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.1d", -6);
	sprintf(og, "%.1d", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.10d", INT32_MAX);
	sprintf(og, "%.10d", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.11d", INT32_MIN);
	sprintf(og, "%.11d", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.2d", -1);
	sprintf(og, "%.2d", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.3d", -17);
	sprintf(og, "%.3d", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%.2d", 17);
	sprintf(og, "%.2d", 17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, decimal_precision_and_width)
{
	km_sprintf(&km, "%10.20d", 0);
	sprintf(og, "%10.20d", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%20.10d", 0);
	sprintf(og, "%20.10d", 0);
	cr_assert_str_eq(km, og);

	// km_sprintf(&km, "%.0d", 0);
	// sprintf(og, "%.0d", 0);
	// cr_assert_str_eq(km, og);

	km_sprintf(&km, "%2.1d", 1);
	sprintf(og, "%2.1d", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%2.3d", 56);
	sprintf(og, "%1.3d", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%3.3d", 439);
	sprintf(og, "%3.3d", 439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%4.4d", -439);
	sprintf(og, "%4.4d", -439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5.5d", 56);
	sprintf(og, "%5.5d", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%2.2d", -6);
	sprintf(og, "%2.2d", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5.6d", 56);
	sprintf(og, "%5.6d", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%2.3d", -6);
	sprintf(og, "%2.3d", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%11.10d", INT32_MAX);
	sprintf(og, "%11.10d", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%12.11d", INT32_MIN);
	sprintf(og, "%12.11d", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5.2d", -1);
	sprintf(og, "%5.2d", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5.9d", -17);
	sprintf(og, "%5.9d", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%2.6d", 17);
	sprintf(og, "%2.6d", 17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, decimal_precision_and_width_blank)
{
	km_sprintf(&km, "% 10.20d", 0);
	sprintf(og, "% 10.20d", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "% 20.10d", 0);
	sprintf(og, "% 20.10d", 0);
	cr_assert_str_eq(km, og);

	// km_sprintf(&km, "% .0d", 0);
	// sprintf(og, "% .0d", 0);
	// cr_assert_str_eq(km, og);

	km_sprintf(&km, "% 2.1d", 1);
	sprintf(og, "% 2.1d", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "% 2.3d", 56);
	sprintf(og, "% 1.3d", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "% 3.3d", 439);
	sprintf(og, "% 3.3d", 439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "% 4.4d", -439);
	sprintf(og, "% 4.4d", -439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "% 5.5d", 56);
	sprintf(og, "% 5.5d", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "% 2.2d", -6);
	sprintf(og, "% 2.2d", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "% 5.6d", 56);
	sprintf(og, "% 5.6d", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "% 2.3d", -6);
	sprintf(og, "% 2.3d", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "% 11.10d", INT32_MAX);
	sprintf(og, "% 11.10d", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "% 12.11d", INT32_MIN);
	sprintf(og, "% 12.11d", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "% 5.2d", -1);
	sprintf(og, "% 5.2d", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "% 5.9d", -17);
	sprintf(og, "% 5.9d", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "% 2.6d", 17);
	sprintf(og, "% 2.6d", 17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, decimal_precision_and_width_left_adjust)
{
	cr_assert(
		km_sprintf(&km, "%-10.20d", 0)
		==
		sprintf(og, "%-10.20d", 0)
	);
	cr_assert_str_eq(km, og);

	cr_assert(
		km_sprintf(&km, "%-20.10d", 0)
		==
		sprintf(og, "%-20.10d", 0)
	);
	cr_assert_str_eq(km, og);

	// km_sprintf(&km, "%-.0d", 0);
	// sprintf(og, "%-.0d", 0);
	// cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-2.1d", 1);
	sprintf(og, "%-2.1d", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-2.3d", 56);
	sprintf(og, "%-1.3d", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-3.3d", 439);
	sprintf(og, "%-3.3d", 439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-4.4d", -439);
	sprintf(og, "%-4.4d", -439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-5.5d", 56);
	sprintf(og, "%-5.5d", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-2.2d", -6);
	sprintf(og, "%-2.2d", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-5.6d", 56);
	sprintf(og, "%-5.6d", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-2.3d", -6);
	sprintf(og, "%-2.3d", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-11.10d", INT32_MAX);
	sprintf(og, "%-11.10d", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-12.11d", INT32_MIN);
	sprintf(og, "%-12.11d", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-5.2d", -1);
	sprintf(og, "%-5.2d", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-5.9d", -17);
	sprintf(og, "%-5.9d", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%-2.6d", 17);
	sprintf(og, "%-2.6d", 17);
	cr_assert_str_eq(km, og);
}
