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

#define CACHE_LINE_SIZE 64

/*
** find the byte that differs
*/
static inline size_t	find_the_culprit(const unsigned char* s1, const unsigned char* s2)
{
	if (s1[1] != s2[1])
		return (1);
	if (s1[2] != s2[2])
		return (2);
	if (s1[3] != s2[3])
		return (3);
	if (s1[4] != s2[4])
		return (4);
	if (s1[5] != s2[5])
		return (5);
	if (s1[6] != s2[6])
		return (6);
	if (s1[7] != s2[7])
		return (7);
	return (0);
}

static inline size_t	compare_unrolled(const int64_t* restrict s1, const int64_t* restrict s2, size_t size)
{
	// comparing 64bytes at a time
	size_t i = 0;
	for (; size > 0; --size, s1 += sizeof(int64_t), s2 += sizeof(int64_t), i += CACHE_LINE_SIZE)
	{
		if (s1[0] != s2[0])
			break ;
		if (s1[1] != s2[1]) {
			i += 1 * sizeof(int64_t); break ;
		} if (s1[2] != s2[2]) {
			i += 2 * sizeof(int64_t); break ;
		} if (s1[3] != s2[3]) {
			i += 3 * sizeof(int64_t); break ;
		} if (s1[4] != s2[4]) {
			i += 4 * sizeof(int64_t); break ;
		} if (s1[5] != s2[5]) {
			i += 5 * sizeof(int64_t); break ;
		} if (s1[6] != s2[6]) {
			i += 6 * sizeof(int64_t); break ;
		} if (s1[7] != s2[7]) {
			i += 7 * sizeof(int64_t); break ;
		}
	}
	if (size != 0)
		return (i + find_the_culprit(((const unsigned char*)s1) + i, ((const unsigned char*)s2) + i));
	return (0);
}

static inline size_t align_memory(const unsigned char* restrict s1, const unsigned char* restrict s2)
{
	size_t offset = 0;

	/*
	** Copy bytes until src is aligned on a cache line boundry
	*/
	while (((unsigned long)(s1 + offset) & (unsigned long)(CACHE_LINE_SIZE - 1)) != 0) {
		if (s1[offset] != s2[offset])
			break ;
		++offset;
	}
	return (offset);
}

int	km_memcmp(const void* s1p, const void* s2p, size_t n)
{
	size_t leftover = n;
	const unsigned char* s1 = (const unsigned char*)s1p; 
	const unsigned char* s2 = (const unsigned char*)s2p; 

	if (n >= CACHE_LINE_SIZE) {
		size_t	offset = align_memory(s1, s2);
		
		if (s1[offset] != s2[offset])
			return (s1[offset] - s2[offset]);

		size_t	unrolled = (n - offset) / CACHE_LINE_SIZE;
				leftover = (n - offset) % CACHE_LINE_SIZE;

		offset += compare_unrolled((int64_t*)(s1 + offset), (int64_t*)(s2 + offset), unrolled);
		if (s1[offset] != s2[offset])
			return (s1[offset] - s2[offset]);
	}

	// copying leftover bytes
	size_t idx;
	while (leftover > 0) {
		idx = n - leftover;
		if (s1[idx] != s2[idx])
			return (s1[idx] - s2[idx]);
		--leftover;
	}
	return (0);
}

#undef CACHE_LINE_SIZE
#undef HI_MAGIC
#undef LO_MAGIC
