
#include "libkm/math.h"
#include <criterion/criterion.h>
#include <math.h>

void suitesetup(void)
{
}

void suiteteardown(void)
{
}

TestSuite(math_test, .init=suitesetup, .fini=suiteteardown);

Test(math_test, test_floor)
{
    cr_expect_eq(km_floor(5.5), 5);
    cr_expect_eq(km_floor(5.1), 5);
    cr_expect_eq(km_floor(5.999), 5);
    cr_expect_eq(km_floor(5.011), 5);
    cr_expect_eq(km_floor(-5.999), -5);
    cr_expect_eq(km_floor(-5.011), -5);
    cr_expect_eq(km_floor(-5), -5);
}

Test(math_test, test_ceil)
{
    cr_expect_eq(km_ceil(5.5), 6);
    cr_expect_eq(km_ceil(5.1), 6);
    cr_expect_eq(km_ceil(5.999), 6);
    cr_expect_eq(km_ceil(5.011), 6);
    cr_expect_eq(km_ceil(-5.999), -6);
    cr_expect_eq(km_ceil(-5.011), -6);
    cr_expect_eq(km_ceil(-5), -5);
}
