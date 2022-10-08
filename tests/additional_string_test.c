
#include <stdlib.h>
#include <libkm.h>
#include <criterion/criterion.h>

Test(additional_test, test_substr) {
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

Test(additional_test, test_strjoin) {
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

Test(additional_test, test_strtrim) {
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

static void free_split(char** split)
{
	for (size_t i = 0; split && split[i] != NULL; i++)
		free(split[i]);
	free(split);
}

Test(additional_test, test_split) {
	char str[] = "I AM GOING TO SPLIT THIS STRING\0";
	char** split = km_split(str, ' ');

	cr_expect_str_eq(*(split), strtok(str,  " "));
	for (size_t i = 1; split[i] != NULL; i++)
		cr_expect_str_eq(*(split + i), strtok(NULL, " "));
	free_split(split);

	char st[] = "       this  has      multiple       splittable    characters   \0";
	split = km_split(st, ' ');
	cr_expect_str_eq(*(split), strtok(st,  " "));
	for (size_t i = 1; split[i] != NULL; i++)
		cr_expect_str_eq(*(split + i), strtok(NULL, " "));
	free_split(split);

	char stur[] = "          \0";
	split = km_split(stur, ' ');
	cr_expect(*(split) == strtok(stur,  " "));
	free_split(split);

	split = km_split("          ", 'b');
	cr_expect_str_eq(*(split), "          ");
	free_split(split);
}

Test(additional_test, test_ltoa) {
	char* nbr;

	nbr = km_ltoa(1);
	cr_expect_str_eq(nbr, "1");
	free(nbr);

	nbr = km_ltoa(0);
	cr_expect_str_eq(nbr, "0");
	free(nbr);

	nbr = km_ltoa(-__LONG_MAX__  - 1);
	cr_expect_str_eq(nbr, "-9223372036854775808");
	free(nbr);

	nbr = km_ltoa(__LONG_MAX__);
	cr_expect_str_eq(nbr, "9223372036854775807");
	free(nbr);

	nbr = km_ltoa(-69);
	cr_expect_str_eq(nbr, "-69");
	free(nbr);

	nbr = km_ltoa(420);
	cr_expect_str_eq(nbr, "420");
	free(nbr);
}

Test(additional_test, test_itoa) {
	char* nbr;

	nbr = km_ltoa(1);
	cr_expect_str_eq(nbr, "1");
	free(nbr);

	nbr = km_ltoa(0);
	cr_expect_str_eq(nbr, "0");
	free(nbr);

	nbr = km_ltoa(-__INT_MAX__  - 1);
	cr_expect_str_eq(nbr, "-2147483648");
	free(nbr);

	nbr = km_ltoa(__INT_MAX__);
	cr_expect_str_eq(nbr, "2147483647");
	free(nbr);

	nbr = km_ltoa(-69);
	cr_expect_str_eq(nbr, "-69");
	free(nbr);

	nbr = km_ltoa(420);
	cr_expect_str_eq(nbr, "420");
	free(nbr);
}

char mapi_test_func(unsigned int i, char c) {
	(void)i;
	return (km_toupper(c));
}

Test(additional_test, test_strmapi) {
	const char str[] = "this string is going to be mapi'd";

	char* mapi = km_strmapi(str, mapi_test_func);
	cr_expect_str_eq(mapi, "THIS STRING IS GOING TO BE MAPI'D");
	free(mapi);
}

void striteri_test_func(unsigned int i, char* s) {
	s[i] = km_toupper(s[i]);
}

Test(additional_test, test_striteri) {
	char str[] = "this string is going to be striteri'd";

	km_striteri(str, striteri_test_func);
	cr_expect_str_eq(str, "THIS STRING IS GOING TO BE STRITERI'D");
}
