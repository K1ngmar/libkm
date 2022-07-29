#include <criterion/criterion.h>
#include <libkm.h>
#include <string.h>

#define VERY_LONG_STRING "I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS. I AM PRETTY SURE A LONG STRING WONT MAKE A DIFFERENCE BUT JUST FOR THE SAKE OF IT WE WILL TEST IT ANYWAYS."

char* km_str = NULL;
char* og_str = NULL;
size_t km_ret = 0;
size_t og_ret = 0;

void suitesetup(void) {
	km_str = malloc(sizeof(char) * 1024);
	og_str = malloc(sizeof(char) * 1024);
	km_ret = 0;
	og_ret = 0;
	km_str[0] = '\0';
	og_str[0] = '\0';
	km_str[2] = 'a';
	og_str[2] = 'a';
}

void suiteteardown(void) {
	free(km_str);
	free(og_str);
	km_str = NULL;
	og_str = NULL;
}

TestSuite(string_test, .init=suitesetup, .fini=suiteteardown);

Test(string_test, test_km_strlen_behaviour) {
	cr_expect(km_strlen("hi") == 2);
	cr_expect(km_strlen("") == 0);
	cr_expect(km_strlen("PIZZA") == 5);
	cr_expect(km_strlen("\n \n \n") == 5);
	cr_expect(km_strlen(VERY_LONG_STRING) == sizeof(VERY_LONG_STRING) - 1);
}

Test(string_test, test_strlcpy_no_crash) {
	km_strlcpy(NULL, "hi", 0);
	km_strlcpy(km_str, "test", 25);
}

Test(string_test, test_strlcpy_behaviour)
{
	km_ret = km_strlcpy(km_str, "test", 3);
	og_ret = strlcpy(og_str, "test", 3);
	cr_expect(strcmp(km_str, og_str) == 0, "comparison");
	cr_expect(km_ret == og_ret, "return value");
	
	km_ret = km_strlcpy(km_str, "pop", 1);
	og_ret = strlcpy(og_str, "pop", 1);
	cr_expect(strcmp(km_str, og_str) == 0, "comparison");
	cr_expect(km_ret == og_ret, "return value");

	km_ret = km_strlcpy(km_str, "help", 5);
	og_ret = strlcpy(og_str, "help", 5);
	cr_expect(strcmp(km_str, og_str) == 0, "comparison");
	cr_expect(km_ret == og_ret, "return value");

	km_ret = km_strlcpy(km_str, "kaaskop", 5);
	og_ret = strlcpy(og_str, "kaaskop", 5);
	cr_expect(strcmp(km_str, og_str) == 0, "comparison");
	cr_expect(km_ret == og_ret, "return value");

	km_ret = km_strlcpy(km_str, VERY_LONG_STRING, sizeof(VERY_LONG_STRING));
	og_ret = strlcpy(og_str, VERY_LONG_STRING, sizeof(VERY_LONG_STRING));
	cr_expect(strcmp(km_str, og_str) == 0, "comparison");
	cr_expect(km_ret == og_ret, "return value");
}

Test(string_test, test_strlcat_behaviour)
{	
	km_ret = km_strlcat(km_str, "this is ", 20);
	og_ret = strlcat(og_str, "this is ", 20);
	cr_expect(strcmp(km_str, og_str) == 0, "comparison");
	cr_expect(km_ret == og_ret, "return value");
	
	km_ret = km_strlcat(km_str, "an epic ", 10);
	og_ret = strlcat(og_str, "an epic ", 10);
	cr_expect(strcmp(km_str, og_str) == 0, "comparison");
	cr_expect(km_ret == og_ret, "return value");

	km_ret = km_strlcat(km_str, "test ", 0);
	og_ret = strlcat(og_str, "test ", 0);
	cr_expect(strcmp(km_str, og_str) == 0, "comparison");
	cr_expect(km_ret == og_ret, "return value");

	km_ret = km_strlcat(km_str, "strlcat implementation", 8);
	og_ret = strlcat(og_str, "strlcat implementation", 8);
	cr_expect(strcmp(km_str, og_str) == 0, "comparison");
	cr_expect(km_ret == og_ret, "return value");

	km_ret = km_strlcat(km_str, "implementation", 14);
	og_ret = strlcat(og_str, "implementation", 14);
	cr_expect(strcmp(km_str, og_str) == 0, "comparison");
	cr_expect(km_ret == og_ret, "return value");
}

Test(string_test, test_toupper) {
	for (char c = 1; c < 127; c++)
		cr_expect(km_toupper(c) == toupper(c));
}

Test(string_test, test_tolower) {
	for (char c = 1; c < 127; c++)
		cr_expect(km_tolower(c) == tolower(c));
}
