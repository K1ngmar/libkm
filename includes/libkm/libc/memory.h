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

#ifndef AWESOME_LIBKM_MEMORY_FUNCTIONS_H
# define AWESOME_LIBKM_MEMORY_FUNCTIONS_H

# include <ctype.h>

///////////
// mem.c //
///////////

	/*!
	 * @brief copies n bytes from src to dst
	 * @param dstp destination pointer
	 * @param srcp source pointer
	 * @return destp
	 * 
	 * @NOTE: dstp and srcp are allowed to overlap!
	*/
	void*	km_memmove(void* dstp, const void* srcp, size_t n);

	/*!
	 * @brief sets n bytes in s to zero
	 * @param s -
	 * @param n -
	*/
	void	km_bzero(void* s, size_t n);

	/*!
	 * @brief allocates count * size bytes and sets the allocated memmory to zero
	 * @param count amount of 
	 * @param size size of the datatype
	 * @return the allocted array, NULL on failure
	*/
	void*	km_calloc(size_t count, size_t size);

	/*!
	 * @brief creates an array of new_size and copys old_size bytes to the array
	 * @param prt -
	 * @param old_size needed for copy
	 * @param new_size the new size of the array (in bytes)
	 * @return the newly allocted array, NULL on failure
	*/
	void*	km_stupid_realloc(void* ptr, size_t old_size, size_t new_size);

//////////////
// memchr.c //
//////////////

	/*!
	 * @brief locates the first occurrence of c (converted to an unsigned char) in string s.
	 * @param s_in array to find in
	 * @param c_in char to find (converted to an unsigned char)
	 * @param n amount of bytes to search
	 * @return function returns a pointer to the byte located, or NULL if no such byte exists within n bytes.
	*/
	void*	km_memchr(void const* s_in, int c_in, size_t n);

//////////////
// memcmp.h //
//////////////

	/*!
	 * @brief compares byte string s1 against byte string s2.  Both strings are assumed to be n bytes long.
	 * @param s1p -
	 * @param s2p -
	 * @param n amount of bytes to search
	 * @return zero if the two strings are identical, otherwise returns the difference between the first two differing bytes
	*/
	int		km_memcmp(const void* s1p, const void* s2p, size_t n);

//////////////
// memcpy.h //
//////////////

	/*!
	 * @brief copies n bytes from memory area src to memory area dst.  If dst and src overlap, behavior is undefined.
	 * @param dst -
	 * @param src -
	 * @param n amount of bytes to copy
	 * @return returns the original value of dst.
	 * 
	 * @NOTE: Applications in which dst and src might overlap should use memmove
	*/
	void*	km_memcpy(void* restrict dst, const void* restrict src, size_t n);

//////////////
// memset.h //
//////////////

	/*!
	 * @brief writes len bytes of value c (converted to an unsigned char) to the string b.
	 * @param b -
	 * @param c -
	 * @param len- 
	 * @return returns its first argument.
	*/
	void*	km_memset(void* restrict b, int c, size_t len);

#endif
