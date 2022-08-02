
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

Test(conversion_test, test_strjoin) {
	char* joined = km_strjoin("join these ", "strings :0");

	cr_expect_str_eq(joined, "join these strings :0");
	free(joined);

	joined = km_strjoin("", "this will be it");
	cr_expect_str_eq(joined, "this will be it");
	free(joined);

	joined = km_strjoin("Who knows what will happen", "");
	cr_expect_str_eq(joined, "Who knows what will happen");
	free(joined);

	joined = km_strjoin("", "");
	cr_expect_str_eq(joined, "");
	free(joined);

	joined = km_strjoin("ban", "ana");
	cr_expect_str_eq(joined, "banana");
	free(joined);
}

Test(conversion_test, test_strtrim) {
	char* trimmed;

	trimmed = km_strtrim("__get rid of these--", "__--");
	cr_expect_str_eq(trimmed, "get rid of these");
	free(trimmed);
	
	trimmed = km_strtrim("___--_a_--__", "_-");
	cr_expect_str_eq(trimmed, "a");
	free(trimmed);

	trimmed = km_strtrim("b___--_a_--__", "_-");
	cr_expect_str_eq(trimmed, "b___--_a");
	free(trimmed);

	trimmed = km_strtrim("b___--_-_--__", "_-");
	cr_expect_str_eq(trimmed, "b");
	free(trimmed);
	
	trimmed = km_strtrim("___--_-_--__y", "_-");
	cr_expect_str_eq(trimmed, "y");
	free(trimmed);

	trimmed = km_strtrim("___--_-_--__", "_-");
	cr_expect_str_eq(trimmed, "");
	free(trimmed);

	trimmed = km_strtrim("___--_-_--__", "abcdefghijk");
	cr_expect_str_eq(trimmed, "___--_-_--__");
	free(trimmed);
}