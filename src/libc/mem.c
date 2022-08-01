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
#include <libkm.h>

void*	km_memmove(void* dstp, const void* srcp, size_t n)
{
	      unsigned char* dst =       (unsigned char*) dstp;
	const unsigned char* src = (const unsigned char*) srcp;

	if (src == dst || n == 0)
		return (dstp);
	// dst overlaps with src, do reverse copy
	if (dst > src && dst - src < (int)n) {
		for(long i = n - 1; i >= 0; --i)
			dst[i] = src[i];
	}
	// src overlaps with dst, copy forward
	else if (src > dst && src - dst < (int)n) {
		for(size_t i = 0; i < n; ++i)
			dst[i] = src[i];
	}
	else {
	// no overlap, more efficient memcpy
		km_memcpy(dstp, srcp, n);
	}
	return (dstp);
}

void	km_bzero(void* s, size_t n) {
	km_memset(s, 0, n);
}
