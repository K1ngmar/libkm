
#include <stdlib.h>
#include <libkm.h>
#include <criterion/criterion.h>

Test(conversion_test, test_substr) {
	char str[] = "I am going to get some substrings out of this string and it is going to be epic :0";
	char* substr;

	substr = km_substr(str, 0, (sizeof(str)));
	cr_expect_str_eq(substr, str);
	free(substr);
	
	substr = km_substr(str, 2, 2);
	cr_expect_str_eq(substr, "am");
	free(substr);
	
	substr = km_substr(str, 18, 4);
	cr_expect_str_eq(substr, "some");
	free(substr);

	substr = km_substr(str, 18, 1);
	cr_expect_str_eq(substr, "s");
	free(substr);

	substr = km_substr(str, 5, 100);
	cr_expect_str_eq(substr, str + 5);
	free(substr);

	substr = km_substr(str, 3, 0);
	cr_expect_str_eq(substr, "");
	free(substr);
}
