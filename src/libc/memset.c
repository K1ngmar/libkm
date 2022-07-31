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

#include <ctype.h>
#include <inttypes.h>

/*
** Generally it is 64 bytes
** Use get_cache_line_size() in LIBKM to check
*/
#define CACHE_LINE_SIZE 64

static inline void	fill_unrolled(int64_t* restrict dst, char cc, size_t size)
{
	int64_t c = cc;
	c = c << 8 | c;
	c = c << 16 | c;
	c = c << 32 | c;

	// copying 64 bytes at a time
	for (; size > 0; --size, dst += 8) {
		dst[0] = c;
		dst[1] = c;
		dst[2] = c;
		dst[3] = c;
		dst[4] = c;
		dst[5] = c;
		dst[6] = c;
		dst[7] = c;
	}
}

static inline size_t align_memory(char* restrict dst, unsigned char c)
{
	size_t offset = 0;

	/*
	** Copy bytes until dst is aligned on a cache line boundry
	*/
	while (((unsigned long)dst & (unsigned long)(CACHE_LINE_SIZE - 1)) != 0) {
		dst[offset] = c;
		++offset;
	}
	return (offset);
}

void*	km_memset(void *b, int c, size_t len)
{
	size_t leftover = len;

	if (len >= CACHE_LINE_SIZE) {
		size_t	offset		= align_memory(b, c);
		size_t	unrolled	= (len - offset) / CACHE_LINE_SIZE;
				leftover	= (len - offset) % CACHE_LINE_SIZE;

		fill_unrolled((int64_t*)(((char*)b) + offset), c, unrolled);
	}

	// copying leftover bytes
	while (leftover > 0) {
		--len;
		--leftover;
		((char*)b)[len] = c;
	}
	return (b);
}

#undef CACHE_LINE_SIZE
