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

#include "libkm/memory.h"
#include "libkm/string.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

/*
** thanks to @tishj for the inspiration to use stringview
*/
typedef struct	split_string_view_s {
	const char*	start;
	size_t		length;
} split_string_view_t;

typedef struct	split_simple_vector_s {
	split_string_view_t*	arr;
	size_t					capacity;
	size_t					size;
} split_simple_vector_t;

static bool grow_vector(split_simple_vector_t* vec)
{
	vec->capacity *= 2;
	void* new_arr = km_stupid_realloc(vec->arr, vec->size * sizeof(split_string_view_t), vec->capacity * sizeof(split_string_view_t));
	if (new_arr == NULL) {
		free(vec->arr);
		vec->arr = NULL;
		return (false);
	}
	vec->arr = new_arr;
	return (true);
}

static bool set_view(const char* str, split_simple_vector_t* vec, size_t start, size_t i)
{
	if (str[start] == '\0')
		return (true);
	if (vec->size + 1 >= vec->capacity && grow_vector(vec) == false) {
		return (false);
	}
	vec->arr[vec->size].start = str + start;
	vec->arr[vec->size].length = i - start;
	vec->size++;
	return (true);
}

static bool	generate_view(const char* str, char c, split_simple_vector_t* vec)
{
	size_t i = 0;
	while (str[i] == c)
		++i;

	size_t start = i;
	for (; str[i] != '\0'; ++i)
	{
		if (str[i] == c && i != start) {
			if (set_view(str, vec, start, i) == false)
				return (false);
			while (str[i] == c)
				++i;
			start = i;
		}
		while (str[i] == c)
			++i;
	}
	return (set_view(str, vec, start, i));
}

static void*	free_split(char** split, size_t len)
{
	for (size_t i = 0; i < len; ++i)
		free(split[i]);
	free(split);
	return (NULL);
}

static char**	generate_split(split_simple_vector_t* vec)
{
	char** split = malloc(sizeof(char*) * (vec->size + 1));
	if (split == NULL)
		return (NULL);
	split[vec->size] = NULL;

	split_string_view_t* sub;
	for (size_t i = 0; i < vec->size; ++i)
	{
		sub = &(vec->arr[i]);
		split[i] = malloc(sizeof(char) * (sub->length + 1));
		if (split[i] == NULL)
			return (free_split(split, i));
		km_memcpy(split[i], sub->start, sub->length);
		split[i][sub->length] = '\0';
	}
	return (split);
}

/*
** Not optimal memory size wise, but also not terrible
*/
char**	km_split(const char* str, char c)
{
	split_simple_vector_t	vec = {
		.arr = malloc(sizeof(split_string_view_t) * 2),
		.capacity = 2,
		.size = 0
	};
	if (vec.arr == NULL)
		return (NULL);
	if (generate_view(str, c, &vec) == false)
		return (NULL);
	char** split = generate_split(&vec);
	free(vec.arr);
	return (split);
}
