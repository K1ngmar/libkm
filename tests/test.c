
#include <criterion/criterion.h>

Test(tryout, criterion) {
	int i = 5;
	cr_expect( i != 5, "expected five");
}
