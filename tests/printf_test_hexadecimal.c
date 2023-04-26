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

Test(printf_test, test_no_conversion) {

	cr_assert(
		km_sprintf(&km, "")
		==
		sprintf(og, "")
	);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "hello worlx");
	sprintf(og, "hello worlx");
	cr_assert_str_eq(km, og);

	// passed as allocated
	cr_assert(
		km_sprintf(&km, "THIS IS A VERY LONG STRING ThAT WILL SURPASS THE LENGTH OF PRINTF_BUFFER_SIZE and should trigger a reallco that definitely will work the first time i test it right? Well this is not enough characters yet since it is by default set to 256 and we have not reached that yet :( but we will very soon and that will test if this will work or not :x")
		==
		sprintf(og, "THIS IS A VERY LONG STRING ThAT WILL SURPASS THE LENGTH OF PRINTF_BUFFER_SIZE and should trigger a reallco that definitely will work the first time i test it right? Well this is not enough characters yet since it is by default set to 256 and we have not reached that yet :( but we will very soon and that will test if this will work or not :x")
	);
	cr_assert_str_eq(km, og);
	
	// passed as NULL
	char* km_str = NULL;
	cr_assert(
		km_sprintf(&km_str, "THIS IS A VERY LONG STRING ThAT WILL SURPASS THE LENGTH OF PRINTF_BUFFER_SIZE and should trigger a reallco that definitely will work the first time i test it right? Well this is not enough characters yet since it is by default set to 256 and we have not reached that yet :( but we will very soon and that will test if this will work or not :x")
		==
		sprintf(og, "THIS IS A VERY LONG STRING ThAT WILL SURPASS THE LENGTH OF PRINTF_BUFFER_SIZE and should trigger a reallco that definitely will work the first time i test it right? Well this is not enough characters yet since it is by default set to 256 and we have not reached that yet :( but we will very soon and that will test if this will work or not :x")
	);
	cr_assert_str_eq(km_str, og);
}

Test(printf_test, hex)
{
	km_sprintf(&km, "d = %x", 100);
	sprintf(og, "d = %x", 100);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "0 = %x", 0);
	sprintf(og, "0 = %x", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "9 = %x", 9);
	sprintf(og, "9 = %x", 9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "-9 = %x", -9);
	sprintf(og, "-9 = %x", -9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "INT_MAX = %x", INT32_MAX);
	sprintf(og, "INT_MAX = %x", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "INT_MIN = %x", INT32_MIN);
	sprintf(og, "INT_MIN = %x", INT32_MIN);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "d = %X", 100);
	sprintf(og, "d = %X", 100);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "0 = %X", 0);
	sprintf(og, "0 = %X", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "9 = %X", 9);
	sprintf(og, "9 = %X", 9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "-9 = %X", -9);
	sprintf(og, "-9 = %X", -9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "INT_MAX = %X", INT32_MAX);
	sprintf(og, "INT_MAX = %X", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "INT_MIN = %X", INT32_MIN);
	sprintf(og, "INT_MIN = %X", INT32_MIN);
	cr_assert_str_eq(km, og);
}

Test(printf_test, hex_long)
{
	km_sprintf(&km, "%lx", (long)100);
	sprintf(og, "%lx", (long)100);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lx", (long)0);
	sprintf(og, "%lx", (long)0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lx", (long)9);
	sprintf(og, "%lx", (long)9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lx", (long)-9);
	sprintf(og, "%lx", (long)-9);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lx", (long)INT32_MAX);
	sprintf(og, "%lx", (long)INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%lx", (long)INT32_MIN);
	sprintf(og, "%lx", (long)INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%llx", INT64_MAX);
	sprintf(og, "%llx", INT64_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%llx", INT64_MIN);
	sprintf(og, "%llx", INT64_MIN);
	cr_assert_str_eq(km, og);
}

Test(printf_test, hex_u)
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

Test(printf_test, hex_ulong)
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

Test(printf_test, hex_field_width)
{
	km_sprintf(&km, "%20x", 0);
	sprintf(og, "%20x", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%0x", 0);
	sprintf(og, "%0x", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%1x", 1);
	sprintf(og, "%1x", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%1x", 56);
	sprintf(og, "%1x", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5x", 56);
	sprintf(og, "%5x", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%1x", -6);
	sprintf(og, "%1x", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5x", -65);
	sprintf(og, "%5x", -65);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%10x", INT32_MAX);
	sprintf(og, "%10x", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%11x", INT32_MIN);
	sprintf(og, "%11x", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%2x", -1);
	sprintf(og, "%2x", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%3x", -17);
	sprintf(og, "%3x", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%2x", 17);
	sprintf(og, "%2x", 17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, hex_precision)
{
	km_sprintf(&km, "%.20x", 0);
	sprintf(og, "%.20x", 0);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%.x", 12);
	sprintf(og, "%.x", 12);
	cr_assert_str_eq(km, og);

	// km_sprintf(&km, "%.0x", 0);
	// sprintf(og, "%.0x", 0);
	// cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.1x", 1);
	sprintf(og, "%.1x", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.1x", 56);
	sprintf(og, "%.1x", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.x", 439);
	sprintf(og, "%.x", 439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.x", -439);
	sprintf(og, "%.x", -439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.5x", 56);
	sprintf(og, "%.5x", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.1x", -6);
	sprintf(og, "%.1x", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.10x", INT32_MAX);
	sprintf(og, "%.10x", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.11x", INT32_MIN);
	sprintf(og, "%.11x", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.2x", -1);
	sprintf(og, "%.2x", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%.3x", -17);
	sprintf(og, "%.3x", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%.2x", 17);
	sprintf(og, "%.2x", 17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, hex_precision_and_width)
{
	km_sprintf(&km, "%10.20x", 0);
	sprintf(og, "%10.20x", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%20.10x", 0);
	sprintf(og, "%20.10x", 0);
	cr_assert_str_eq(km, og);

	// km_sprintf(&km, "%.0x", 0);
	// sprintf(og, "%.0x", 0);
	// cr_assert_str_eq(km, og);

	km_sprintf(&km, "%2.1x", 1);
	sprintf(og, "%2.1x", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%2.3x", 56);
	sprintf(og, "%1.3x", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%3.3x", 439);
	sprintf(og, "%3.3x", 439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%4.4x", -439);
	sprintf(og, "%4.4x", -439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5.5x", 56);
	sprintf(og, "%5.5x", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%2.2x", -6);
	sprintf(og, "%2.2x", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5.6x", 56);
	sprintf(og, "%5.6x", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%2.3x", -6);
	sprintf(og, "%2.3x", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%11.10x", INT32_MAX);
	sprintf(og, "%11.10x", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%12.11x", INT32_MIN);
	sprintf(og, "%12.11x", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5.2x", -1);
	sprintf(og, "%5.2x", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%5.9x", -17);
	sprintf(og, "%5.9x", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%2.6x", 17);
	sprintf(og, "%2.6x", 17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, hex_precision_and_width_hashtag)
{
	km_sprintf(&km, "%#10.20x", 0);
	sprintf(og, "%#10.20x", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#20.10x", 0);
	sprintf(og, "%#20.10x", 0);
	cr_assert_str_eq(km, og);

	// km_sprintf(&km, "%#.0x", 0);
	// sprintf(og, "%#.0x", 0);
	// cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.1x", 1);
	sprintf(og, "%#2.1x", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.3x", 56);
	sprintf(og, "%#1.3x", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#3.3x", 439);
	sprintf(og, "%#3.3x", 439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#4.4x", -439);
	sprintf(og, "%#4.4x", -439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.5x", 56);
	sprintf(og, "%#5.5x", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.2x", -6);
	sprintf(og, "%#2.2x", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.6x", 56);
	sprintf(og, "%#5.6x", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.3x", -6);
	sprintf(og, "%#2.3x", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#11.10x", INT32_MAX);
	sprintf(og, "%#11.10x", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#12.11x", INT32_MIN);
	sprintf(og, "%#12.11x", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.2x", -1);
	sprintf(og, "%#5.2x", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.9x", -17);
	sprintf(og, "%#5.9x", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%#2.6x", 17);
	sprintf(og, "%#2.6x", 17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, hex_precision_and_width_hashtag_uppercase)
{
	km_sprintf(&km, "%#10.20X", 0);
	sprintf(og, "%#10.20X", 0);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#20.10X", 0);
	sprintf(og, "%#20.10X", 0);
	cr_assert_str_eq(km, og);

	// km_sprintf(&km, "%#.0X", 0);
	// sprintf(og, "%#.0X", 0);
	// cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.1X", 1);
	sprintf(og, "%#2.1X", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.3X", 56);
	sprintf(og, "%#1.3X", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#3.3X", 439);
	sprintf(og, "%#3.3X", 439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#4.4X", -439);
	sprintf(og, "%#4.4X", -439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.5X", 56);
	sprintf(og, "%#5.5X", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.2X", -6);
	sprintf(og, "%#2.2X", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.6X", 56);
	sprintf(og, "%#5.6X", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#2.3X", -6);
	sprintf(og, "%#2.3X", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#11.10X", INT32_MAX);
	sprintf(og, "%#11.10X", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#12.11X", INT32_MIN);
	sprintf(og, "%#12.11X", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.2X", -1);
	sprintf(og, "%#5.2X", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%#5.9X", -17);
	sprintf(og, "%#5.9X", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%#2.6X", 17);
	sprintf(og, "%#2.6X", 17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, hex_precision_and_width_left_adjust)
{
	cr_assert(
		km_sprintf(&km, "%-10.20x", 0)
		==
		sprintf(og, "%-10.20x", 0)
	);
	cr_assert_str_eq(km, og);

	cr_assert(
		km_sprintf(&km, "%-20.10x", 0)
		==
		sprintf(og, "%-20.10x", 0)
	);
	cr_assert_str_eq(km, og);

	// km_sprintf(&km, "%-.0x", 0);
	// sprintf(og, "%-.0x", 0);
	// cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-2.1x", 1);
	sprintf(og, "%-2.1x", 1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-2.3x", 56);
	sprintf(og, "%-1.3x", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-3.3x", 439);
	sprintf(og, "%-3.3x", 439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-4.4x", -439);
	sprintf(og, "%-4.4x", -439);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-5.5x", 56);
	sprintf(og, "%-5.5x", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-2.2x", -6);
	sprintf(og, "%-2.2x", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-5.6x", 56);
	sprintf(og, "%-5.6x", 56);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-2.3x", -6);
	sprintf(og, "%-2.3x", -6);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-11.10x", INT32_MAX);
	sprintf(og, "%-11.10x", INT32_MAX);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-12.11x", INT32_MIN);
	sprintf(og, "%-12.11x", INT32_MIN);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-5.2x", -1);
	sprintf(og, "%-5.2x", -1);
	cr_assert_str_eq(km, og);

	km_sprintf(&km, "%-5.9x", -17);
	sprintf(og, "%-5.9x", -17);
	cr_assert_str_eq(km, og);
	
	km_sprintf(&km, "%-2.6x", 17);
	sprintf(og, "%-2.6x", 17);
	cr_assert_str_eq(km, og);
}

Test(printf_test, address)
{
	cr_assert_eq(
		km_sprintf(&km, "%p", (void*)100),
		sprintf(og, "%p", (void*)100)
	);
	cr_assert_str_eq(km, og);

	cr_assert_eq(
		km_sprintf(&km, "%p", (void*)0),
		sprintf(og, "%p", (void*)0)
	);
	cr_assert_str_eq(km, og);

	cr_assert_eq(
		km_sprintf(&km, "%p", (void*)9),
		sprintf(og, "%p", (void*)9)
	);
	cr_assert_str_eq(km, og);

	cr_assert_eq(
		km_sprintf(&km, "%p", (void*)-9),
		sprintf(og, "%p", (void*)-9)
	);
	cr_assert_str_eq(km, og);

	cr_assert_eq(
		km_sprintf(&km, "%p", (void*)INT32_MAX),
		sprintf(og, "%p", (void*)INT32_MAX)
	);
	cr_assert_str_eq(km, og);

	cr_assert_eq(
		km_sprintf(&km, "%p", (void*)INT32_MIN),
		sprintf(og, "%p", (void*)INT32_MIN)
	);
	cr_assert_str_eq(km, og);

	cr_assert_eq(
		km_sprintf(&km, "%p", (void*)INT64_MAX),
		sprintf(og, "%p", (void*)INT64_MAX)
	);
	cr_assert_str_eq(km, og);

	void* addr = km;
	cr_assert_eq(
		km_sprintf(&km, "%p", addr),
		sprintf(og, "%p", addr)
	);
	cr_assert_str_eq(km, og);
	
	cr_assert_eq(
		km_sprintf(&km, "%p", (void*)&og),
		sprintf(og, "%p", (void*)&og)
	);
	cr_assert_str_eq(km, og);
}

Test(printf_test, address_precision_width)
{
	cr_assert_eq(
		km_sprintf(&km, "%3p", (void*)100),
		sprintf(og, "%3p", (void*)100)
	);
	cr_assert_str_eq(km, og);

	cr_assert_eq(
		km_sprintf(&km, "%2p", (void*)0),
		sprintf(og, "%2p", (void*)0)
	);
	cr_assert_str_eq(km, og);
	
	cr_assert_eq(
		km_sprintf(&km, "%5p", (void*)0),
		sprintf(og, "%5p", (void*)0)
	);
	cr_assert_str_eq(km, og);
	
	cr_assert_eq(
		km_sprintf(&km, "%8p", (void*)0),
		sprintf(og, "%8p", (void*)0)
	);
	cr_assert_str_eq(km, og);
	
	cr_assert_eq(
		km_sprintf(&km, "%29p", (void*)9),
		sprintf(og, "%29p", (void*)9)
	);
	cr_assert_str_eq(km, og);

	cr_assert_eq(
		km_sprintf(&km, "%2p", (void*)-9),
		sprintf(og, "%2p", (void*)-9)
	);
	cr_assert_str_eq(km, og);

	cr_assert_eq(
		km_sprintf(&km, "%30p", (void*)INT32_MAX),
		sprintf(og, "%30p", (void*)INT32_MAX)
	);
	cr_assert_str_eq(km, og);

	cr_assert_eq(
		km_sprintf(&km, "%30p", (void*)INT32_MIN),
		sprintf(og, "%30p", (void*)INT32_MIN)
	);
	cr_assert_str_eq(km, og);

	cr_assert_eq(
		km_sprintf(&km, "%20p", (void*)INT64_MAX),
		sprintf(og, "%20p", (void*)INT64_MAX)
	);
	cr_assert_str_eq(km, og);

	void* addr = km;
	cr_assert_eq(
		km_sprintf(&km, "%5p", addr),
		sprintf(og, "%5p", addr)
	);
	cr_assert_str_eq(km, og);
	
	cr_assert_eq(
		km_sprintf(&km, "%10p", (void*)&og),
		sprintf(og, "%10p", (void*)&og)
	);
	cr_assert_str_eq(km, og);
}
