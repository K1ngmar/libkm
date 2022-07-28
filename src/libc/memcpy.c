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

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

/*
** Generally it is 64 bytes
** Use get_cache_line_size() in LIBKM to check
*/
#define CACHE_LINE_SIZE 64

static inline void	copy_unrolled(int64_t* restrict dst, const int64_t* restrict src, size_t size)
{
	// copying 64 bytes at a time
	for (; size > 0; --size, dst += 8, src += 8) {
		dst[0] = src[0];
		dst[1] = src[1];
		dst[2] = src[2];
		dst[3] = src[3];
		dst[4] = src[4];
		dst[5] = src[5];
		dst[6] = src[6];
		dst[7] = src[7];
	}
}

static inline size_t align_memory(char* restrict dst, const char* restrict src)
{
	size_t offset = 0;

	/*
	** Copy bytes until src is aligned on a cache line boundry
	*/
	while (((unsigned long)src & (unsigned long)(CACHE_LINE_SIZE - 1)) != 0) {
		*dst = *src;
		++dst;
		++src;
		++offset;
	}
	return (offset);
}

void*	km_memcpy(void* restrict dst, const void* restrict src, size_t n)
{
	size_t leftover = n;

	if (n >= CACHE_LINE_SIZE) {
		size_t	offset		= align_memory(dst, src);
		size_t	unrolled	= (n - offset) / CACHE_LINE_SIZE;
				leftover	= (n - offset) % CACHE_LINE_SIZE;

		copy_unrolled((int64_t*)(((char*)dst) + offset), (int64_t*)(((char*)src) + offset), unrolled);
	}

	// copying leftover bytes
	while (leftover > 0) {
		--n;
		--leftover;
		((char*)dst)[n] = ((char*)src)[n];
	}
	return (dst);
}

#undef CACHE_LINE_SIZE
