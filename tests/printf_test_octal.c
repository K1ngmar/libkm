
#include "libkm/io/printf.h"

#include <criterion/criterion.h>
#include <stdio.h>
#include <stdint.h>
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

	#ifndef __linux__
		
		cr_assert(
			km_sprintf(&km, "")
			==
			sprintf(og, "")
		);
		cr_assert_str_eq(km, og);

	#endif

	km_sprintf(&km, "hello worlo");
	sprintf(og, "hello worlo");
	cr_assert_str_eq(km, og);

	// passed as allocated
	cr_assert(
		km_sprintf(&km, "THIS IS A VERY LONG STRING ThAT WILL SURPASS THE LENGTH OF PRINTF_BUFFER_SIZE and should trigger a reallco that definitely will work the first time i test it right? Well this is not enough characters yet since it is by default set to 256 and we have not reached that yet :( but we will very soon and that will test if this will work or not :o")
		==
		sprintf(og, "THIS IS A VERY LONG STRING ThAT WILL SURPASS THE LENGTH OF PRINTF_BUFFER_SIZE and should trigger a reallco that definitely will work the first time i test it right? Well this is not enough characters yet since it is by default set to 256 and we have not reached that yet :( but we will very soon and that will test if this will work or not :o")
	);
	cr_assert_str_eq(km, og);
	
	// passed as NULL
	char* km_str = NULL;
	cr_assert(
		km_sprintf(&km_str, "THIS IS A VERY LONG STRING ThAT WILL SURPASS THE LENGTH OF PRINTF_BUFFER_SIZE and should trigger a reallco that definitely will work the first time i test it right? Well this is not enough characters yet since it is by default set to 256 and we have not reached that yet :( but we will very soon and that will test if this will work or not :o")
		==
		sprintf(og, "THIS IS A VERY LONG STRING ThAT WILL SURPASS THE LENGTH OF PRINTF_BUFFER_SIZE and should trigger a reallco that definitely will work the first time i test it right? Well this is not enough characters yet since it is by default set to 256 and we have not reached that yet :( but we will very soon and that will test if this will work or not :o")
	);
	cr_assert_str_eq(km_str, og);
}

Test(printf_test, octal)
{
	km_sprintf(&km, "d = %o", 100);
	sprintf(og, "d = %o", 100);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "0 = %o", 0);
	sprintf(og, "0 = %o", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "9 = %o", 9);
	sprintf(og, "9 = %o", 9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "-9 = %o", -9);
	sprintf(og, "-9 = %o", -9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "INT_MAX = %o", INT32_MAX);
	sprintf(og, "INT_MAX = %o", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "INT_MIN = %o", INT32_MIN);
	sprintf(og, "INT_MIN = %o", INT32_MIN);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "d = %o", 100);
	sprintf(og, "d = %o", 100);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "0 = %o", 0);
	sprintf(og, "0 = %o", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "9 = %o", 9);
	sprintf(og, "9 = %o", 9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "-9 = %o", -9);
	sprintf(og, "-9 = %o", -9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "INT_MAX = %o", INT32_MAX);
	sprintf(og, "INT_MAX = %o", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "INT_MIN = %o", INT32_MIN);
	sprintf(og, "INT_MIN = %o", INT32_MIN);
	cr_assert_str_eq(km, og);
}

Test(printf_test, octal_long)
{
	km_sprintf(&km, "%lo", (long)100);
	sprintf(og, "%lo", (long)100);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lo", (long)0);
	sprintf(og, "%lo", (long)0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lo", (long)9);
	sprintf(og, "%lo", (long)9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lo", (long)-9);
	sprintf(og, "%lo", (long)-9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lo", (long)INT32_MAX);
	sprintf(og, "%lo", (long)INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lo", (long)INT32_MIN);
	sprintf(og, "%lo", (long)INT32_MIN);
	cr_assert_str_eq(km, og);

	#ifdef __linux__

		km_sprintf(&km, "%lo", INT64_MAX);
		sprintf(og, "%lo", INT64_MAX);
		cr_assert_str_eq(km, og);

		km_sprintf(&km, "%lo", INT64_MIN);
		sprintf(og, "%lo", INT64_MIN);
		cr_assert_str_eq(km, og);

	#else

		km_sprintf(&km, "%llo", INT64_MAX);
		sprintf(og, "%llo", INT64_MAX);
		cr_assert_str_eq(km, og);

		km_sprintf(&km, "%llo", INT64_MIN);
		sprintf(og, "%llo", INT64_MIN);
		cr_assert_str_eq(km, og);

	#endif
}

Test(printf_test, octal_u)
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

Test(printf_test, octal_ulong)
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

	#ifdef __linux__

		km_sprintf(&km, "%lu", UINT64_MAX);
		sprintf(og, "%lu", UINT64_MAX);
		cr_assert_str_eq(km, og);

		km_sprintf(&km, "%lu", UINT64_MAX + 1);
		sprintf(og, "%lu", UINT64_MAX + 1);
		cr_assert_str_eq(km, og);

	#else	

		km_sprintf(&km, "%llu", UINT64_MAX);
		sprintf(og, "%llu", UINT64_MAX);
		cr_assert_str_eq(km, og);

		km_sprintf(&km, "%llu", UINT64_MAX + 1);
		sprintf(og, "%llu", UINT64_MAX + 1);
		cr_assert_str_eq(km, og);
	
	#endif
}

Test(printf_test, octal_field_width)
{
	km_sprintf(&km, "%20o", 0);
	sprintf(og, "%20o", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%0o", 0);
	sprintf(og, "%0o", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%1o", 1);
	sprintf(og, "%1o", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%1o", 56);
	sprintf(og, "%1o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5o", 56);
	sprintf(og, "%5o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%1o", -6);
	sprintf(og, "%1o", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5o", -65);
	sprintf(og, "%5o", -65);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%10o", INT32_MAX);
	sprintf(og, "%10o", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%11o", INT32_MIN);
	sprintf(og, "%11o", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%2o", -1);
	sprintf(og, "%2o", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%3o", -17);
	sprintf(og, "%3o", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%2o", 17);
	sprintf(og, "%2o", 17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, octal_precision)
{
	km_sprintf(&km, "%.20o", 0);
	sprintf(og, "%.20o", 0);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%.o", 12);
	sprintf(og, "%.o", 12);
	cr_assert_str_eq(km, og);

	// km_sprintf(&km, "%.0o", 0);
	// sprintf(og, "%.0o", 0);
	// cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.1o", 1);
	sprintf(og, "%.1o", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.1o", 56);
	sprintf(og, "%.1o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.o", 439);
	sprintf(og, "%.o", 439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.o", -439);
	sprintf(og, "%.o", -439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.5o", 56);
	sprintf(og, "%.5o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.1o", -6);
	sprintf(og, "%.1o", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.10o", INT32_MAX);
	sprintf(og, "%.10o", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.11o", INT32_MIN);
	sprintf(og, "%.11o", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.2o", -1);
	sprintf(og, "%.2o", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.3o", -17);
	sprintf(og, "%.3o", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%.2o", 17);
	sprintf(og, "%.2o", 17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, octal_precision_and_width)
{
	km_sprintf(&km, "%10.20o", 0);
	sprintf(og, "%10.20o", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%20.10o", 0);
	sprintf(og, "%20.10o", 0);
	cr_assert_str_eq(km, og);

	// km_sprintf(&km, "%.0o", 0);
	// sprintf(og, "%.0o", 0);
	// cr_assert_str_eq(km, og);

	km_sprintf(&km, "%2.1o", 1);
	sprintf(og, "%2.1o", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%2.3o", 56);
	sprintf(og, "%1.3o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%3.3o", 439);
	sprintf(og, "%3.3o", 439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%4.4o", -439);
	sprintf(og, "%4.4o", -439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5.5o", 56);
	sprintf(og, "%5.5o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%2.2o", -6);
	sprintf(og, "%2.2o", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5.6o", 56);
	sprintf(og, "%5.6o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%2.3o", -6);
	sprintf(og, "%2.3o", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%11.10o", INT32_MAX);
	sprintf(og, "%11.10o", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%12.11o", INT32_MIN);
	sprintf(og, "%12.11o", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5.2o", -1);
	sprintf(og, "%5.2o", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5.9o", -17);
	sprintf(og, "%5.9o", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%2.6o", 17);
	sprintf(og, "%2.6o", 17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, octal_precision_and_width_hashtag)
{
	km_sprintf(&km, "%#10.20o", 0);
	sprintf(og, "%#10.20o", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#20.10o", 0);
	sprintf(og, "%#20.10o", 0);
	cr_assert_str_eq(km, og);

	// km_sprintf(&km, "%#.0o", 0);
	// sprintf(og, "%#.0o", 0);
	// cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.1o", 1);
	sprintf(og, "%#2.1o", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.3o", 56);
	sprintf(og, "%#1.3o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#3.3o", 439);
	sprintf(og, "%#3.3o", 439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#4.4o", -439);
	sprintf(og, "%#4.4o", -439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.5o", 56);
	sprintf(og, "%#5.5o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.2o", -6);
	sprintf(og, "%#2.2o", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.6o", 56);
	sprintf(og, "%#5.6o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.3o", -6);
	sprintf(og, "%#2.3o", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#11.10o", INT32_MAX);
	sprintf(og, "%#11.10o", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#12.11o", INT32_MIN);
	sprintf(og, "%#12.11o", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.2o", -1);
	sprintf(og, "%#5.2o", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.9o", -17);
	sprintf(og, "%#5.9o", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%#2.6o", 17);
	sprintf(og, "%#2.6o", 17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, octal_precision_and_width_hashtag_uppercase)
{
	km_sprintf(&km, "%#10.20o", 0);
	sprintf(og, "%#10.20o", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#20.10o", 0);
	sprintf(og, "%#20.10o", 0);
	cr_assert_str_eq(km, og);

	// km_sprintf(&km, "%#.0o", 0);
	// sprintf(og, "%#.0o", 0);
	// cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.1o", 1);
	sprintf(og, "%#2.1o", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.3o", 56);
	sprintf(og, "%#1.3o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#3.3o", 439);
	sprintf(og, "%#3.3o", 439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#4.4o", -439);
	sprintf(og, "%#4.4o", -439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.5o", 56);
	sprintf(og, "%#5.5o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.2o", -6);
	sprintf(og, "%#2.2o", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.6o", 56);
	sprintf(og, "%#5.6o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.3o", -6);
	sprintf(og, "%#2.3o", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#11.10o", INT32_MAX);
	sprintf(og, "%#11.10o", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#12.11o", INT32_MIN);
	sprintf(og, "%#12.11o", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.2o", -1);
	sprintf(og, "%#5.2o", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.9o", -17);
	sprintf(og, "%#5.9o", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%#2.6o", 17);
	sprintf(og, "%#2.6o", 17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, octal_precision_and_width_left_adjust)
{
	cr_assert(
		km_sprintf(&km, "%-10.20o", 0)
		==
		sprintf(og, "%-10.20o", 0)
	);
	cr_assert_str_eq(km, og);

	cr_assert(
		km_sprintf(&km, "%-20.10o", 0)
		==
		sprintf(og, "%-20.10o", 0)
	);
	cr_assert_str_eq(km, og);

	// km_sprintf(&km, "%-.0o", 0);
	// sprintf(og, "%-.0o", 0);
	// cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-2.1o", 1);
	sprintf(og, "%-2.1o", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-2.3o", 56);
	sprintf(og, "%-1.3o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-3.3o", 439);
	sprintf(og, "%-3.3o", 439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-4.4o", -439);
	sprintf(og, "%-4.4o", -439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-5.5o", 56);
	sprintf(og, "%-5.5o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-2.2o", -6);
	sprintf(og, "%-2.2o", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-5.6o", 56);
	sprintf(og, "%-5.6o", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-2.3o", -6);
	sprintf(og, "%-2.3o", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-11.10o", INT32_MAX);
	sprintf(og, "%-11.10o", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-12.11o", INT32_MIN);
	sprintf(og, "%-12.11o", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-5.2o", -1);
	sprintf(og, "%-5.2o", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-5.9o", -17);
	sprintf(og, "%-5.9o", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%-2.6o", 17);
	sprintf(og, "%-2.6o", 17);
	cr_assert_str_eq(km, og);
}
