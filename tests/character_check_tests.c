
#include "libkm/string.h"

#include <criterion/criterion.h>
#include <ctype.h>
#include <stdio.h>

#define TestFunc(funcname) \
	Test(character_checks, test_##funcname) { \
		for (int c = -255; c < 255; c++){ \
			printf("c=%d\n", c); \
			cr_expect(funcname(c) == km_##funcname(c));} \
	}

TestFunc(isupper)
TestFunc(islower)
TestFunc(isalpha)
TestFunc(isdigit)
TestFunc(isascii)
TestFunc(isprint)
