
#include "libkm/string.h"

#include <stdlib.h>
#include <criterion/criterion.h>
#include <stdint.h>

#define __LONG_MIN__ (__LONG_MAX__ + 1)

char int_max[] = "2147483647";
char int_min[] = "-2147483648";
char long_max[] = "9223372036854775807";
char long_min[] = "-9223372036854775808";


char faulty[] = "234532a34";

char space[] = " \t\r\v\n";
char zero[] = " 0";

char *km_endptr;
char *og_endptr;

void suiteteardown(void) {
	km_endptr = NULL;
	og_endptr = NULL;
}

TestSuite(string_test, .fini=suiteteardown);

Test(conversion_test, test_atoi) {
	cr_expect(km_atoi("12345") == 12345);
	cr_expect(km_atoi(int_max) == INT32_MAX);
	cr_expect(km_atoi(int_min) == INT32_MIN);
	cr_expect(km_atoi(" 12") == 12);
	cr_expect(km_atoi(" +-12") == atoi(" +-12"));
	cr_expect(km_atoi(" -+12") == atoi(" -+12"));
	cr_expect(km_atoi("	-42") == -42);
	cr_expect(km_atoi("a") == 0);
	cr_expect(km_atoi("-69lol42") == -69);
}

Test(conversion_test, test_atol) {
	cr_expect(km_atol("12345") == 12345);
	cr_expect(km_atol(long_max) == __LONG_MAX__);
	cr_expect(km_atol(long_min) == __LONG_MIN__);
	cr_expect(km_atol(" 12") == 12);
	cr_expect(km_atol(" +-12") == atoi(" +-12"));
	cr_expect(km_atol(" -+12") == atoi(" -+12"));
	cr_expect(km_atol("	-42") == -42);
	cr_expect(km_atol("a") == 0);
	cr_expect(km_atol("-69lol42") == -69);
}

Test(conversion_test, test_strtoll_base_10) {
	cr_expect(km_strtoll("1023", NULL, 10) == strtoll("1023", NULL, 10));
	cr_expect(km_strtoll("-1023", NULL, 10) == strtoll("-1023", NULL, 10));
	cr_expect(km_strtoll(long_max, NULL, 10) == strtoll(long_max, NULL, 10));
	cr_expect(km_strtoll(long_min, NULL, 0) == strtoll(long_min, NULL, 0));
	cr_expect(km_strtoll("  1213b20", NULL, 10) == strtoll("  1213b20", NULL, 10));
	cr_expect(km_strtoll("  -1213b20", NULL, 10) == strtoll("  -1213b20", NULL, 10));
	
	cr_expect(km_strtoll(faulty, &km_endptr, 10) == strtoll(faulty, &og_endptr, 10));
	cr_expect(km_endptr == og_endptr);
	
	cr_expect(km_strtoll(long_max, &km_endptr, 10) == strtoll(long_max, &og_endptr, 10));
	cr_expect(km_endptr == og_endptr);

	cr_expect(km_strtoll(space, &km_endptr, 10) == strtoll(space, &og_endptr, 10));
	cr_expect(km_endptr == og_endptr);
	
	cr_expect(km_strtoll(zero, &km_endptr, 10) == strtoll(zero, &og_endptr, 10));
	cr_expect(km_endptr == og_endptr);	
}

Test(conversion_test, test_strtoll_base_2) {
	char wrong_dc[] = "01010201046";

	cr_expect(km_strtoll("1001010", NULL, 2) == strtoll("1001010", NULL, 2));
	cr_expect(km_strtoll("-100101", NULL, 2) == strtoll("-100101", NULL, 2));
	cr_expect(km_strtoll("1111111111111111111111111111111", NULL, 2) == strtoll("1111111111111111111111111111111", NULL, 2));
	cr_expect(km_strtoll("-1111111111111111111111111111111", NULL, 2) == strtoll("-1111111111111111111111111111111", NULL, 2));

	cr_expect(km_strtoll("0b101010", NULL, 0) == 42);

	cr_expect(km_strtoll(wrong_dc, &km_endptr, 2) == strtoll(wrong_dc, &og_endptr, 2));
	cr_expect(km_endptr == og_endptr);
}

Test(conversion_test, test_strtoll_base_8) {
	char wrong_dc[] = "1254890";

	cr_expect(km_strtoll("11234", NULL, 8) == strtoll("11234", NULL, 8));
	
	cr_expect(km_strtoll("-76235", NULL, 8) == strtoll("-76235", NULL, 8));
	cr_expect(km_strtoll("272433", NULL, 8) == strtoll("272433", NULL, 8));
	cr_expect(km_strtoll("-232736263", NULL, 8) == strtoll("-232736263", NULL, 8));
	cr_expect(km_strtoll("-232736263", NULL, 8) == strtoll("-232736263", NULL, 8));

	cr_expect(km_strtoll(wrong_dc, &km_endptr, 8) == strtoll(wrong_dc, &og_endptr, 8));
	cr_expect(km_endptr == og_endptr);
}

Test(conversion_test, test_strtoll_base_16) {
	char wrong_dc[] = "42abz2";

	cr_expect(km_strtoll("21aabcaf", NULL, 16) == strtoll("21aabcaf", NULL, 16));
	cr_expect(km_strtoll("-234adf", NULL, 16) == strtoll("-234adf", NULL, 16));
	cr_expect(km_strtoll("0X12344f", NULL, 16) == strtoll("0X12344f", NULL, 16));
	cr_expect(km_strtoll("-0xabcd", NULL, 16) == strtoll("-0xabcd", NULL, 16));
	cr_expect(km_strtoll("-232736263", NULL, 16) == strtoll("-232736263", NULL, 16));

	cr_expect(km_strtoll(wrong_dc, &km_endptr, 16) == strtoll(wrong_dc, &og_endptr, 16));
	cr_expect(km_endptr == og_endptr);
}
