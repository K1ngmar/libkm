/* ************************************************************************** */
/*                                                                            */
/*                 _       _______  _____   _    _   __   __                  */
/*                (_)     (_______)(_____) (_)  (_) (__)_(__)                 */
/*                (_)        (_)   (_)__(_)(_)_(_) (_) (_) (_)                */
/*                (_)        (_)   (_____) (____)  (_) (_) (_)                */
/*                (_)____  __(_)__ (_)__(_)(_) (_) (_)     (_)                */
/*                (______)(_______)(_____) (_)  (_)(_)     (_)                */
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBKM_AWESOME_TEMPLATED_VECTOR
# define LIBKM_AWESOME_TEMPLATED_VECTOR

# include <ctype.h>
# include <stdlib.h>
# include <assert.h>

/*!
 * @brief this macro registers vector prototypes
 * @NOTE: Put this in a headerfile
*/
# define REGISTER_KM_VECTOR_PROTOTYPES(vector_type, typename) \
\
typedef bool(*typename##_deep_copy_function)(vector_type* destination, const vector_type source); \
typedef void(*typename##_destroy_function)(vector_type* val); \
\
/*! \
 * @brief this is the vector struct containing all the vector data \
*/ \
typedef struct km_vector_##typename##_s \
{ \
	size_t							size; \
	size_t							capacity; \
	vector_type*					arr; \
	typename##_deep_copy_function	deep_copy; \
	typename##_destroy_function 	destroy_element; \
} km_vector_##typename; \
\
/*! \
* @brief intialises vector \
* @param vector - \
* @param deep_copy_function pass NULL if no deepcopy is nessecary \
* @param destroy_element_function pass NULL if no destruction is needed \
* @param deep_copy_function pass NULL if no deep_copy on insert is needed \
*/ \
void km_vector_##typename##_initialise( \
		km_vector_##typename* vector, \
		typename##_destroy_function destroy_element_function, \
		typename##_deep_copy_function deep_copy_function); \
\
/*! \
* @brief destroys vector \
* @param vector - \
*/ \
void km_vector_##typename##_destroy(km_vector_##typename* vector); \
\
/*! \
* @brief gets element at position with validation \
* @param vector - \
* @param position - \
*/ \
vector_type* km_vector_##typename##_at(km_vector_##typename* vector, size_t position); \
\
/*! \
* @brief gets first element \
* @param vector - \
*/ \
vector_type* km_vector_##typename##_front(km_vector_##typename* vector); \
\
/*! \
* @brief gets last element \
* @param vector - \
*/ \
vector_type* km_vector_##typename##_back(km_vector_##typename* vector); \
\
/*! \
* @brief gets the internal array \
* @param vector - \
*/ \
vector_type* km_vector_##typename##_data(km_vector_##typename* vector); \
\
/*! \
* @brief - \
* @param vector - \
*/ \
vector_type* km_vector_##typename##_begin(km_vector_##typename* vector); \
\
/*! \
* @brief - \
* @param vector - \
*/ \
vector_type* km_vector_##typename##_end(km_vector_##typename* vector); \
\
/*! \
* @brief - \
* @param vector - \
*/ \
vector_type* km_vector_##typename##_rbegin(km_vector_##typename* vector); \
\
/*! \
* @brief - \
* @param vector - \
*/ \
vector_type* km_vector_##typename##_rend(km_vector_##typename* vector); \
\
/*! \
* @brief - \
* @param vector - \
* @return - \
*/ \
bool km_vector_##typename##_empty(km_vector_##typename* vector); \
\
/*! \
* @brief - \
* @param vector - \
* @return - \
*/ \
size_t km_vector_##typename##_size(km_vector_##typename* vector); \
\
/*! \
* @brief makes sure there is enough space for size elements, reallocates if necessary \
* @param vector - \
* @param size - \
* @return - \
*/ \
bool km_vector_##typename##_reserve(km_vector_##typename* vector, size_t size); \
\
/*! \
* @brief - \
* @param vector - \
* @return - \
*/ \
size_t km_vector_##typename##_capacity(km_vector_##typename* vector); \
\
/*! \
* @brief clears vector contents, does not free or resize the array \
* @param vector - \
*/ \
void km_vector_##typename##_clear(km_vector_##typename* vector); \
\
/*! \
* @brief inserts val after pos \
* @param vector - \
* @param position - \
* @param amount - \
* @param val - \
* @return pointer to position of the first inserted value, NULL on failure \
*/ \
vector_type* km_vector_##typename##_fill_insert(km_vector_##typename* vector, size_t position, size_t amount, const vector_type val); \
\
/*! \
* @brief inserts val after pos \
* @param vector - \
* @param position - \
* @param val - \
* @return pointer to inserted value, NULL on failure \
*/ \
vector_type* km_vector_##typename##_element_insert(km_vector_##typename* vector, size_t position, const vector_type val); \
\
/*! \
* @brief inserts everything between first and last into vector at pos \
* @param vector - \
* @param position - \
* @param first - \
* @param last - \
* @param deep_copy pass NULL if deepcopy is not required, otherwise provide a function that does the deepcopy \
* @return pointer to inserted value, NULL on failure \
*  \
* @note Make sure first and last are from the same array \
*/ \
vector_type* km_vector_##typename##_range_insert(km_vector_##typename* vector, size_t position, const vector_type* first, const vector_type* last); \
\
/*! \
* @brief erases everything between [first and last) \
* @param vector - \
* @param fist - \
* @param last \
*/ \
void km_vector_##typename##_erase_range(km_vector_##typename* vector, size_t first, size_t last); \
\
/*! \
* @brief erases value at position \
* @param vector - \
* @param position - \
*/ \
void km_vector_##typename##_erase_position(km_vector_##typename* vector, size_t position); \
\
/*! \
* @brief appends value to the end of the vector \
* @param vector - \
* @param val - \
* @return pointer to inserted value, Null on failure \
*  \
* @NOTE: resizes if nessecary \
*/ \
vector_type* km_vector_##typename##_push_back(km_vector_##typename* vector, const vector_type val); \
\
/*! \
* @brief erases last element \
* @param vector - \
*/ \
void km_vector_##typename##_pop_back(km_vector_##typename* vector); \
\
/*! \
* @brief Resizes the container to contain count elements, does nothing if count == size() \
* @param vector - \
* @param count - \
* @return true on success, false on failure and the vector is no longer usable \
*/ \
bool km_vector_##typename##_resize(km_vector_##typename* vector, size_t count);



/*!
 * @brief this macro registers a vector for type
 * @NOTE: Put this in a source file
 * 		  make sure to include the header with the registered prototypes in this sourcefile
*/
# define REGISTER_KM_VECTOR_SOURCE(vector_type, typename) \
\
/*//////////////// \
// Construction // \
////////////////*/ \
\
	/*! \
	* @brief intialises vector \
	* @param vector - \
	* @param deep_copy_function pass NULL if no deepcopy is nessecary \
	* @param destroy_element_function pass NULL if no destruction is needed \
	* @param deep_copy_function pass NULL if no deep_copy on insert is needed \
	*/ \
	void km_vector_##typename##_initialise( \
		km_vector_##typename* vector, \
		typename##_destroy_function destroy_element_function, \
		typename##_deep_copy_function deep_copy_function) \
	{ \
		vector->size = 0; \
		vector->capacity = 0; \
		vector->arr = NULL; \
		vector->destroy_element = destroy_element_function; \
		vector->deep_copy = deep_copy_function; \
	} \
\
	/*! \
	* @brief destroys vector \
	* @param vector - \
	*/ \
	void km_vector_##typename##_destroy(km_vector_##typename* vector) \
	{ \
		km_vector_##typename##_clear(vector); \
		free(vector->arr); \
	} \
\
/*/////////// \
// helpers // \
///////////*/ \
\
	/*! \
	 * @brief reallocates the vector \
	 * @param vector - \
	 * @param newCapacity - \
	 * @return true on success, false on failure \
	*/ \
	static bool __km_vector_##typename##_realloc(km_vector_##typename* vector, size_t newCapacity) \
	{ \
		vector_type* tmp; \
 \
		tmp = (vector_type*)malloc(sizeof(vector_type) * newCapacity); \
		if (tmp == NULL) { \
			km_vector_##typename##_destroy(vector); \
			return false; \
		} \
 \
		size_t i = 0; \
		for (; i < vector->size && i < newCapacity; i++) { \
			tmp[i] = vector->arr[i]; \
		} \
		free(vector->arr); \
		vector->arr = tmp; \
		vector->size = i; \
		vector->capacity = newCapacity; \
		return true; \
	} \
 \
	/*! \
	 * @brief moves amount everything after position n spots \
	 * @param vector - \
	 * @param position - \
	 * @param n - \
	 * @return true on success, false on error \
	*/ \
	static bool __km_vector_##typename##_move_range(km_vector_##typename* vector, size_t position, size_t n) \
	{ \
		if (vector->size + n > vector->capacity) { \
			if (km_vector_##typename##_resize(vector, vector->size + n) == false) { \
				return false; \
			} \
		} \
		size_t oldEnd = vector->size; \
		vector->size += n; \
		while (oldEnd != position) \
		{ \
			oldEnd--; \
			vector->arr[oldEnd + n] = vector->arr[oldEnd]; \
		} \
		return true; \
	} \
 \
	/*! \
	 * @brief copys value to pos, does deepcopy if necessary \
	 * @param vector - \
	 * @param position - \
	 * @param val - \
	 * @return true on success, false on error \
	*/ \
	static bool __km_vector_##typename##_copy_value(km_vector_##typename* vector, size_t position, const vector_type val) \
	{ \
		if (vector->deep_copy) \
		{ \
			if (vector->deep_copy(&(vector->arr[position]), val) == false) \
			{ \
				km_vector_##typename##_destroy(vector); \
				return false; \
			} \
		} \
		else { \
			vector->arr[position] = val; \
		} \
		return true; \
	} \
 \
	/*! \
	 * @brief moves everything from end to start position \
	 * @param vector - \
	 * @param start - \
	 * @param end - \
	*/ \
	static void __km_vector_##typename##_move_back_range(km_vector_##typename* vector, size_t start, size_t end) \
	{ \
		assert(start <= end); \
		size_t dist = end - start; \
		for (size_t i = 0; end + i < vector->size; i++) \
		{ \
			vector->arr[start + i] = vector->arr[end + i]; \
		} \
		vector->size -= dist; \
	} \
 \
/*////////////////// \
// Element access // \
//////////////////*/ \
 \
	/*! \
	 * @brief gets element at position with validation \
	 * @param vector - \
	 * @param position - \
	*/ \
	vector_type* km_vector_##typename##_at(km_vector_##typename* vector, size_t position) \
	{ \
		assert(position < vector->size); \
		return &(vector->arr[position]); \
	} \
 \
	/*! \
	 * @brief gets first element \
	 * @param vector - \
	*/ \
	vector_type* km_vector_##typename##_front(km_vector_##typename* vector) \
	{ \
		assert(vector->size > 0); \
		return vector->arr; \
	} \
 \
	/*! \
	 * @brief gets last element \
	 * @param vector - \
	*/ \
	vector_type* km_vector_##typename##_back(km_vector_##typename* vector) \
	{ \
		assert(vector->size > 0); \
		return &(vector->arr[vector->size - 1]); \
	} \
 \
	/*! \
	 * @brief gets the internal array \
	 * @param vector - \
	*/ \
	vector_type* km_vector_##typename##_data(km_vector_##typename* vector) \
	{ \
		return vector->arr; \
	} \
 \
/*///////////// \
// iterators // \
/////////////*/ \
 \
	/*! \
	 * @brief - \
	 * @param vector - \
	*/ \
	vector_type* km_vector_##typename##_begin(km_vector_##typename* vector) \
	{ \
		return vector->arr; \
	} \
 \
	/*! \
	 * @brief - \
	 * @param vector - \
	*/ \
	vector_type* km_vector_##typename##_end(km_vector_##typename* vector) \
	{ \
		return vector->arr + vector->size; \
	} \
 \
	/*! \
	 * @brief - \
	 * @param vector - \
	*/ \
	vector_type* km_vector_##typename##_rbegin(km_vector_##typename* vector) \
	{ \
		return vector->arr + vector->size - 1; \
	} \
 \
	/*! \
	 * @brief - \
	 * @param vector - \
	*/ \
	vector_type* km_vector_##typename##_rend(km_vector_##typename* vector) \
	{ \
		return vector->arr - 1; \
	} \
 \
/*//////////// \
// Capacity // \
////////////*/ \
 \
	/*! \
	 * @brief - \
	 * @param vector - \
	 * @return - \
	*/ \
	bool km_vector_##typename##_empty(km_vector_##typename* vector) \
	{ \
		return vector->size == 0;	 \
	} \
 \
	/*! \
	 * @brief - \
	 * @param vector - \
	 * @return - \
	*/ \
	size_t km_vector_##typename##_size(km_vector_##typename* vector) \
	{ \
		return vector->size; \
	} \
 \
	/*! \
	 * @brief makes sure there is enough space for size elements, reallocates if necessary \
	 * @param vector - \
	 * @param size - \
	 * @return - \
	*/ \
	bool km_vector_##typename##_reserve(km_vector_##typename* vector, size_t size) \
	{ \
		if (vector->capacity > size) { \
			return true; \
		} \
		return km_vector_##typename##_resize(vector, size); \
	} \
 \
	/*! \
	 * @brief - \
	 * @param vector - \
	 * @return - \
	*/ \
	size_t km_vector_##typename##_capacity(km_vector_##typename* vector) \
	{ \
		return vector->capacity; \
	} \
 \
/*///////////// \
// Modifiers // \
/////////////*/ \
 \
	/*! \
	* @brief clears vector contents, does not free or resize the array \
	* @param vector - \
	*/ \
	void km_vector_##typename##_clear(km_vector_##typename* vector) \
	{ \
		while (vector->size > 0) { \
			km_vector_##typename##_pop_back(vector); \
		} \
	} \
 \
 	/*! \
	 * @brief inserts val after pos \
	 * @param vector - \
	 * @param position - \
	 * @param amount - \
	 * @param val - \
	 * @return pointer to position of the first inserted value, NULL on failure \
	*/ \
	vector_type* km_vector_##typename##_fill_insert(km_vector_##typename* vector, size_t position, size_t amount, const vector_type val) \
	{ \
		assert(position <= vector->size); \
		if (__km_vector_##typename##_move_range(vector, position, amount) == false) { \
			return NULL; \
		} \
		while (amount > 0) \
		{ \
			amount--; \
			if (__km_vector_##typename##_copy_value(vector, position + amount, val) == false) { \
				return NULL; \
			} \
		} \
		return vector->arr + position; \
	} \
 \
	/*! \
	 * @brief inserts val after pos \
	 * @param vector - \
	 * @param position - \
	 * @param val - \
	 * @return pointer to inserted value, NULL on failure \
	*/ \
	vector_type* km_vector_##typename##_element_insert(km_vector_##typename* vector, size_t position, const vector_type val) \
	{ \
		return km_vector_##typename##_fill_insert(vector, position, 1, val); \
	} \
 \
	/*! \
	 * @brief inserts everything between first and last into vector at pos \
	 * @param vector - \
	 * @param position - \
	 * @param first - \
	 * @param last - \
	 * @param deep_copy pass NULL if deepcopy is not required, otherwise provide a function that does the deepcopy \
	 * @return pointer to inserted value, NULL on failure \
	 *  \
	 * @note Make sure first and last are from the same array \
	*/ \
	vector_type* km_vector_##typename##_range_insert(km_vector_##typename* vector, size_t position, const vector_type* first, const vector_type* last) \
	{ \
		assert(position <= vector->size); \
		assert(first < last); \
\
		size_t amount = last - first; \
		if (__km_vector_##typename##_move_range(vector, position, amount) == false) { \
			return NULL; \
		} \
		for (size_t i = 0; i < amount; i++) \
		{ \
			if (__km_vector_##typename##_copy_value(vector, position + i, *(first + i)) == false) { \
				return NULL; \
			} \
		} \
		return vector->arr + position; \
	} \
 \
 	/*! \
	 * @brief erases everything between [first and last) \
	 * @param vector - \
	 * @param fist - \
	 * @param last \
	*/ \
	void km_vector_##typename##_erase_range(km_vector_##typename* vector, size_t first, size_t last) \
	{ \
		assert(first < vector->size && last <= vector->size); \
 \
		if (vector->destroy_element) \
		{ \
			for (size_t i = first; i != last; i++) \
			{ \
				vector->destroy_element(&(vector->arr[i]));	 \
			} \
		} \
		__km_vector_##typename##_move_back_range(vector, first, last); \
	} \
 \
	/*! \
	 * @brief erases value at position \
	 * @param vector - \
	 * @param position - \
	*/ \
	void km_vector_##typename##_erase_position(km_vector_##typename* vector, size_t position) \
	{ \
		km_vector_##typename##_erase_range(vector, position, position + 1); \
	} \
	 \
 \
	/*! \
	 * @brief appends value to the end of the vector \
	 * @param vector - \
	 * @param val - \
	 * @return pointer to inserted value, Null on failure \
	 *  \
	 * @NOTE: resizes if nessecary \
	*/ \
	vector_type* km_vector_##typename##_push_back(km_vector_##typename* vector, const vector_type val) \
	{ \
		if (vector->size + 1 > vector->capacity) { \
			if (km_vector_##typename##_resize(vector, vector->size + 1) == false) { \
				return NULL; \
			} \
		} \
		if (__km_vector_##typename##_copy_value(vector, vector->size, val) == false) { \
			return NULL; \
		} \
		vector->size++; \
		return km_vector_##typename##_back(vector); \
	} \
 \
	/*! \
	 * @brief erases last element \
	 * @param vector - \
	*/ \
	void km_vector_##typename##_pop_back(km_vector_##typename* vector) \
	{ \
		if (vector->size == 0) { \
			return ; \
		} \
		vector->size--; \
		if (vector->destroy_element) \
		{ \
			vector->destroy_element(&(vector->arr[vector->size])); \
		} \
	} \
 \
	/*! \
	 * @brief Resizes the container to contain count elements, does nothing if count == size() \
	 * @param vector - \
	 * @param count - \
	 * @return true on success, false on failure and the vector is no longer usable \
	*/ \
	bool km_vector_##typename##_resize(km_vector_##typename* vector, size_t count) \
	{ \
		if (count == vector->size) { \
			return true; \
		} \
		if (count == 0) { \
			vector->capacity = 16; \
		} \
		if (count < vector->capacity * 2) \
			count = vector->capacity * 2; \
		return __km_vector_##typename##_realloc(vector, count); \
	}

#endif
