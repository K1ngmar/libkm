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
#include <string.h>

size_t	km_strlcpy(char* restrict dst, const char* restrict src, size_t dstsize)
{
	const size_t src_len = km_strlen(src);

	if (src_len < dstsize) {
		// src fits entirely into dst
		km_memcpy(dst, src, src_len + 1);
	} else if (dstsize != 0) {
		// dst is smaller than src
		km_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return src_len;
}

size_t	km_strlcat(char* restrict dst, const char* restrict src, size_t dstsize)
{
	const size_t src_len = km_strlen(src);
	const size_t dst_len = km_strnlen(dst, dstsize);

	if (dst_len == dstsize) {
		// dst is completely filled
		return dstsize + src_len;
	}

	if (src_len < dstsize - dst_len) {
		// src will fit entirely in dst
		km_memcpy(dst + dst_len, src, src_len + 1);
	} else {
		// src will partially fit into dst
		km_memcpy(dst + dst_len, src, dstsize - dst_len - 1);
		dst[dstsize - 1] = '\0';
	}
	return (dst_len + src_len);
}

int	km_toupper(int c) {
	return (c - (32 * (c >= 'a' && c <= 'z')));
}

int	km_tolower(int c) {
	return (c + (32 * (c >= 'A' && c <= 'Z')));
}
