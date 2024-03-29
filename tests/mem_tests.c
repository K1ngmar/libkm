
#include "libkm/memory.h"
#include <criterion/criterion.h>
#include <string.h>

#define TEST_SIZE 1024

char*	km_src = NULL;
char*	km_dst = NULL;
char*	og_src = NULL;
char*	og_dst = NULL;

void suitesetup(void) {
	km_src = malloc(sizeof(char) * TEST_SIZE);
	km_dst = malloc(sizeof(char) * TEST_SIZE);
	og_src = malloc(sizeof(char) * TEST_SIZE);
	og_dst = malloc(sizeof(char) * TEST_SIZE);
}

void suiteteardown(void) {
	free(km_src);
	free(km_dst);
	free(og_src);
	free(og_dst);
	km_src = NULL;
	km_dst = NULL;
	og_src = NULL;
	og_dst = NULL;
}

TestSuite(mem_test, .init=suitesetup, .fini=suiteteardown);

Test(mem_test, test_memset) {

	km_memset(km_src, 'a', TEST_SIZE);
	memset(og_src, 'a', TEST_SIZE);
	cr_expect(memcmp(km_src, og_src, TEST_SIZE) == 0);
	
	km_memset(km_src, 'z', TEST_SIZE / 2);
	memset(og_src, 'z', TEST_SIZE / 2);
	cr_expect(memcmp(km_src, og_src, TEST_SIZE) == 0);
}

Test(mem_test, test_memmove) {
	memset(km_src, 'a', TEST_SIZE);
	memset(km_src, 'z', TEST_SIZE / 2);
	memset(og_src, 'a', TEST_SIZE);
	memset(og_src, 'z', TEST_SIZE / 2);
	
	cr_expect(memcmp(km_memmove(km_dst, km_src, TEST_SIZE), memmove(og_dst, og_src, TEST_SIZE), TEST_SIZE) == 0);
	cr_expect(memcmp(km_memmove(km_src, km_src + (TEST_SIZE / 3), TEST_SIZE / 2), memmove(og_src, og_src + (TEST_SIZE / 3), TEST_SIZE / 2), TEST_SIZE) == 0);
	cr_expect(memcmp(km_memmove(km_dst + 42, km_dst, TEST_SIZE - 42), memmove(og_dst + 42, og_dst, TEST_SIZE - 42), TEST_SIZE - 42) == 0);
	cr_expect(memcmp(km_memmove(km_dst, km_dst, TEST_SIZE), memmove(og_dst, og_dst, TEST_SIZE), TEST_SIZE) == 0);
	cr_expect(memcmp(km_memmove(km_dst, km_src, 0), memmove(og_dst, og_src, 0), TEST_SIZE) == 0);
}

Test(mem_test, test_bzero) {
	km_bzero(km_src, TEST_SIZE);
	bzero(og_src, TEST_SIZE);
	cr_expect(memcmp(km_src, og_src, TEST_SIZE) == 0);
	
	memset(km_dst, 'a', TEST_SIZE);
	memset(og_dst, 'a', TEST_SIZE);
	km_bzero(km_dst, 1);
	bzero(og_dst, 1);
	cr_expect(memcmp(km_dst, og_dst, TEST_SIZE) == 0);
	
	km_bzero(km_dst, TEST_SIZE / 2);
	bzero(og_dst, TEST_SIZE / 2);
	cr_expect(memcmp(km_dst, og_dst, TEST_SIZE) == 0);
}

Test(mem_test, test_memchr) {
	const char str[] = "WE ARE ABOUT TO FIND SOME AWESOME CHARACTERS IN THIS VERY COOL STRING; WITH A DOPE FUNCTION :) (JUST MAKING THIS STRING A BIT LONGER IN ORDER TO _CHECK IF THE OPTIMISATION IS WORKING CORRECTLY, WHICH IS IMPORTANT TO KNOW U KNOW) :p/!@#$^";

	cr_expect(km_memchr(str, ';', sizeof(str)) == memchr(str, ';', sizeof(str)));
	cr_expect(km_memchr(str, ':', sizeof(str)) == memchr(str, ':', sizeof(str)));
	cr_expect(km_memchr(str, 'C', sizeof(str)) == memchr(str, 'C', sizeof(str)));
	cr_expect(km_memchr(str, 'W', sizeof(str)) == memchr(str, 'W', sizeof(str)));
	cr_expect(km_memchr(str, ',', sizeof(str)) == memchr(str, ',', sizeof(str)));
	cr_expect(km_memchr(str, '_', sizeof(str)) == memchr(str, '_', sizeof(str)));
	cr_expect(km_memchr(str, 'p', sizeof(str)) == memchr(str, 'p', sizeof(str)));
	cr_expect(km_memchr(str, '!', sizeof(str)) == memchr(str, '!', sizeof(str)));
	cr_expect(km_memchr(str, '@', sizeof(str)) == memchr(str, '@', sizeof(str)));
	cr_expect(km_memchr(str, '#', sizeof(str)) == memchr(str, '#', sizeof(str)));
	cr_expect(km_memchr(str, '$', sizeof(str)) == memchr(str, '$', sizeof(str)));
	cr_expect(km_memchr(str, '^', sizeof(str)) == memchr(str, '^', sizeof(str)));
	cr_expect(km_memchr(str, -1, sizeof(str)) == memchr(str, -1, sizeof(str)));
}

Test(mem_test, test_memcmp) {
	char s1[] = "You already know these strings are going to be compared matey; also this string has to be longer than CACHE_LINE_SIZE because that will trigger the optimisation built in :0";
	char s2[] = "You already know these strings are going to be compared matey; also this string has to be longer than CACHE_LINE_SIZE because that will trigger the optimisation built in :0";

	cr_expect(km_memcmp(s1, s2, sizeof(s1)) == memcmp(s1, s2, sizeof(s1)));
	cr_expect(km_memcmp(s2, s1, sizeof(s1)) == memcmp(s2, s1, sizeof(s1)));

	s2[sizeof(s2) - 1] = 'x';
	cr_expect(km_memcmp(s1, s2, sizeof(s1)) == memcmp(s1, s2, sizeof(s1)));
	cr_expect(km_memcmp(s2, s1, sizeof(s1)) == memcmp(s2, s1, sizeof(s1)));
	
	s2[170] = -42;
	cr_expect(km_memcmp(s1, s2, sizeof(s1)) == memcmp(s1, s2, sizeof(s1)));
	cr_expect(km_memcmp(s2, s1, sizeof(s1)) == memcmp(s2, s1, sizeof(s1)));
	
	s2[64] = '_';
	cr_expect(km_memcmp(s1, s2, sizeof(s1)) == memcmp(s1, s2, sizeof(s1)));
	cr_expect(km_memcmp(s2, s1, sizeof(s1)) == memcmp(s2, s1, sizeof(s1)));

	s2[5] = '?';
	cr_expect(km_memcmp(s1, s2, sizeof(s1)) == memcmp(s1, s2, sizeof(s1)));
	cr_expect(km_memcmp(s2, s1, sizeof(s1)) == memcmp(s2, s1, sizeof(s1)));
}
