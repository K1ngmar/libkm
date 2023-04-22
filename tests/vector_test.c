#include <criterion/criterion.h>
#include <libkm/containers/vector.h>

REGISTER_KM_VECTOR_PROTOTYPES(int, int)
REGISTER_KM_VECTOR_SOURCE(int, int)

km_vector_int vec;

void suitesetup(void) {

	km_vector_int_initialise(&vec, NULL, NULL);
}

void suiteteardown(void) {
	km_vector_int_destroy(&vec);
}

TestSuite(km_vector_test, .init=suitesetup, .fini=suiteteardown);

Test(km_vector_test, km_vector_push_back)
{
	km_vector_int_push_back(&vec, 10);
	cr_assert_eq(km_vector_int_size(&vec), 1);

	km_vector_int_push_back(&vec, 20);
	cr_assert_eq(*km_vector_int_front(&vec), 10);
	cr_assert_eq(*km_vector_int_back(&vec), 20);
	cr_assert_eq(km_vector_int_size(&vec), 2);

	km_vector_int_push_back(&vec, 40);
	cr_assert_eq(*km_vector_int_front(&vec), 10);
	cr_assert_eq(*km_vector_int_at(&vec, 1), 20);
	cr_assert_eq(*km_vector_int_back(&vec), 40);
	cr_assert_eq(km_vector_int_size(&vec), 3);
}

Test(km_vector_test, km_vector_element_insert)
{
	km_vector_int_element_insert(&vec, 0, 1);
	cr_assert_eq(*km_vector_int_at(&vec, 0), 1);

	km_vector_int_element_insert(&vec, 1, 3);
	cr_assert_eq(*km_vector_int_at(&vec, 0), 1);
	cr_assert_eq(*km_vector_int_at(&vec, 1), 3);

	km_vector_int_element_insert(&vec, 1, 2);
	cr_assert_eq(*km_vector_int_at(&vec, 0), 1);
	cr_assert_eq(*km_vector_int_at(&vec, 1), 2);
	cr_assert_eq(*km_vector_int_at(&vec, 2), 3);
	
	km_vector_int_element_insert(&vec, 0, 0);
	cr_assert_eq(*km_vector_int_at(&vec, 0), 0);
	cr_assert_eq(*km_vector_int_at(&vec, 1), 1);
	cr_assert_eq(*km_vector_int_at(&vec, 2), 2);
	cr_assert_eq(*km_vector_int_at(&vec, 3), 3);

	km_vector_int_fill_insert(&vec, 1, 3, 42);
	cr_assert_eq(*km_vector_int_at(&vec, 0), 0);
	cr_assert_eq(*km_vector_int_at(&vec, 1), 42);
	cr_assert_eq(*km_vector_int_at(&vec, 2), 42);
	cr_assert_eq(*km_vector_int_at(&vec, 3), 42);
	cr_assert_eq(*km_vector_int_at(&vec, 4), 1);
	cr_assert_eq(km_vector_int_size(&vec), 7);

	int arr[] = {10, 20, 30};
	km_vector_int_range_insert(&vec, 2, arr, arr + 3);
	cr_assert_eq(*km_vector_int_at(&vec, 0), 0);
	cr_assert_eq(*km_vector_int_at(&vec, 1), 42);
	cr_assert_eq(*km_vector_int_at(&vec, 2), 10);
	cr_assert_eq(*km_vector_int_at(&vec, 3), 20);
	cr_assert_eq(*km_vector_int_at(&vec, 4), 30);
	cr_assert_eq(*km_vector_int_at(&vec, 5), 42);
	cr_assert_eq(*km_vector_int_at(&vec, 9), 3);
	cr_assert_eq(km_vector_int_size(&vec), 10);
}

Test(km_vector_test, km_vector_element_erase)
{
	int arr[] = {10, 20, 30, 40, 50, 60, 70};
	km_vector_int_range_insert(&vec, 0, arr, arr + 7);

	km_vector_int_erase_position(&vec, 1);
	cr_assert_eq(*km_vector_int_at(&vec, 0), 10);
	cr_assert_eq(*km_vector_int_at(&vec, 1), 30);
	cr_assert_eq(km_vector_int_size(&vec), 6);
	
	km_vector_int_erase_position(&vec, 0);
	cr_assert_eq(*km_vector_int_at(&vec, 0), 30);
	cr_assert_eq(*km_vector_int_at(&vec, 1), 40);
	cr_assert_eq(km_vector_int_size(&vec), 5);

	km_vector_int_erase_range(&vec, 2, 4);
	cr_assert_eq(*km_vector_int_at(&vec, 0), 30);
	cr_assert_eq(*km_vector_int_at(&vec, 1), 40);
	cr_assert_eq(*km_vector_int_at(&vec, 2), 70);
	cr_assert_eq(km_vector_int_size(&vec), 3);
	
	km_vector_int_erase_range(&vec, 0, 3);
	cr_assert_eq(km_vector_int_size(&vec), 0);
}

Test(km_vector_test, km_vector_element_clear)
{
	int arr[] = {10, 20, 30, 40, 50, 60, 70};
	km_vector_int_range_insert(&vec, 0, arr, arr + 7);

	km_vector_int_clear(&vec);
	cr_assert_eq(km_vector_int_size(&vec), 0);
}
