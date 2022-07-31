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

Test(string_test, test_strchr) {
	for (size_t i = 0; i < 69; i++)
		km_str[i] = 'a' + i % 26;
	km_str[69] = '\0';

	for (size_t i = 0; i < 128; i++)
		cr_expect(km_strchr(km_str, i) == strchr(km_str, i));
}

Test(string_test, test_strrchr) {
	for (size_t i = 0; i < 69; i++)
		km_str[i] = 'a' + i % 26;
	km_str[69] = '\0';

	for (size_t i = 0; i < 128; i++)
		cr_expect(km_strrchr(km_str, i) == strrchr(km_str, i));
}

Test(string_test, test_strcmp) {
	char s1[] = "testniffau";
	char s2[] = "testniffau";
	
	cr_expect(km_strcmp(s1, s2) == strcmp(s1, s2));

	s2[5] = 'z';
	cr_expect(km_strcmp(s1, s2) == strcmp(s1, s2));

	s1[3] = 'a';
	cr_expect(km_strcmp(s1, s2) == strcmp(s1, s2));

	s1[0] = 'd';
	cr_expect(km_strcmp(s1, s2) == strcmp(s1, s2));
}

Test(string_test, test_strncmp) {
	char s1[] = "testniffau";
	char s2[] = "testniffau";
	
	cr_expect(km_strncmp(s1, s2, 5) == strncmp(s1, s2, 5));
	cr_expect(km_strncmp(s1, s2, 42) == strncmp(s1, s2, 42));
	cr_expect(km_strncmp(s1, s2, 1) == strncmp(s1, s2, 1));
	cr_expect(km_strncmp(s1, s2, 2) == strncmp(s1, s2, 2));

	s2[5] = 'z';
	cr_expect(km_strncmp(s1, s2, 0) == strncmp(s1, s2, 0));
	cr_expect(km_strncmp(s1, s2, 20) == strncmp(s1, s2, 20));
	

	s1[3] = 'a';
	cr_expect(km_strncmp(s1, s2, 3) == strncmp(s1, s2, 3));

	s1[0] = 'd';
	cr_expect(km_strncmp(s1, s2, 12) == strncmp(s1, s2, 12));
}
