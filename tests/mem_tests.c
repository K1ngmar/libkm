
#include <criterion/criterion.h>
#include <libkm.h>
#include <string.h>

#define TEST_SIZE 1024

Test(mem_test, test_memset) {
	char* km_tbf = malloc(sizeof(char) * TEST_SIZE);
	char* og_tbf = malloc(sizeof(char) * TEST_SIZE);

	km_memset(km_tbf, 'a', TEST_SIZE);
	memset(og_tbf, 'a', TEST_SIZE);
	cr_expect(memcmp(km_tbf, og_tbf, TEST_SIZE) == 0);
	
	km_memset(km_tbf, 'z', TEST_SIZE / 2);
	memset(og_tbf, 'z', TEST_SIZE / 2);
	cr_expect(memcmp(km_tbf, og_tbf, TEST_SIZE) == 0);

}
