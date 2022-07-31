
#include <stdlib.h>
#include <libkm.h>
#include <criterion/criterion.h>

Test(conversion_test, test_atoi) {
	cr_expect(km_atoi("12345") == 12345);
	cr_expect(km_atoi("2147483647") == 2147483647);
	cr_expect(km_atoi("-2147483648") == -2147483648);
	cr_expect(km_atoi(" 12") == 12);
	cr_expect(km_atoi(" +-12") == atoi(" +-12"));
	cr_expect(km_atoi(" -+12") == atoi(" -+12"));
	cr_expect(km_atoi("	-42") == -42);
	cr_expect(km_atoi("a") == 0);
	cr_expect(km_atoi("-69lol42") == -69);
}

Test(conversion_test, test_atol) {
	cr_expect(km_atol("12345") == 12345);
	cr_expect(km_atol("9223372036854775807") == 9223372036854775807L);
	cr_expect(km_atol("-9223372036854775808") == __LONG_MAX__ + 1);
	cr_expect(km_atol(" 12") == 12);
	cr_expect(km_atol(" +-12") == atoi(" +-12"));
	cr_expect(km_atol(" -+12") == atoi(" -+12"));
	cr_expect(km_atol("	-42") == -42);
	cr_expect(km_atol("a") == 0);
	cr_expect(km_atol("-69lol42") == -69);
}
