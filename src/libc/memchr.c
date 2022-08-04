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
#include <stdlib.h>

#define ALIGN_SIZE sizeof(int64_t)

// 8 bytes, with the most significant bit set in each of them
#define HI_MAGIC 0x8080808080808080ULL
// single byte: 1000 0000

// 8 bytes, with the least signifcant bit set in each of them
#define LO_MAGIC 0x0101010101010101ULL
// single byte: 0000 0001

static inline size_t	search_unrolled(int64_t* restrict ptr, unsigned char c, size_t size)
{
	int64_t repeated_c = (c << 8) | c;
			repeated_c |= repeated_c << 16;
			repeated_c |= repeated_c << 32;

	int64_t longword;

	// searching 8bytes at a time
	for (size_t i = 0; size > 0; --size, ++ptr, i += sizeof(int64_t))
	{
		// turn the matching byte into null byte
		longword = (*ptr) ^ repeated_c; 

		// follow strlen logic for nullbytes :D
		if (((longword - LO_MAGIC) & (~longword) & HI_MAGIC) != 0) {
			const char* found = (const char*)ptr;

				if (found[0] == c)
					return (i);
				if (found[1] == c)
					return (i + 1);
				if (found[2] == c)
					return (i + 2);
				if (found[3] == c)
					return (i + 3);
				if (found[4] == c)
					return (i + 4);
				if (found[5] == c)
					return (i + 5);
				if (found[6] == c)
					return (i + 6);
				if (found[7] == c)
					return (i + 7);
		}
	}
	return (0);
}

static inline size_t align_memory(const unsigned char* restrict s, unsigned char c)
{
	size_t offset = 0;

	/*
	** Compare bytes until src is aligned on a cache line boundry
	*/
	while (((unsigned long)(s + offset) & (unsigned long)(ALIGN_SIZE - 1)) != 0) {
		if (s[offset] == c)
			break ;
		++offset;
	}
	return (offset);
}

void*	km_memchr(void const *s_in, int c_in, size_t n)
{
	size_t leftover = n;
	const unsigned char* s	= (const unsigned char*)s_in;
		  unsigned char  c	= (unsigned char)c_in;

	if (n >= ALIGN_SIZE) {
		size_t	offset = align_memory(s, c);
		
		if (s[offset] == c)
			return ((void*)(s + offset));

		size_t	unrolled	= (n - offset) / ALIGN_SIZE;
				leftover	= (n - offset) % ALIGN_SIZE;

		offset += search_unrolled((int64_t*)(s + offset), c_in, unrolled);
		if (s[offset] == c)
			return ((void*)(s + offset));
	}

	// copying leftover bytes
	while (leftover > 0) {
		if (s[n - leftover] == c)
			return ((void*)(s + n - leftover));
		--leftover;
	}
	return (NULL);
}

#undef ALIGN_SIZE
#undef HI_MAGIC
#undef LO_MAGIC
