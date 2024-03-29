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
#include <stdlib.h>

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

char*	km_strchr(const char* s, int needle)
{
	char c = needle;

	while (s) {
		if (*s == '\0')
			return (NULL);
		if (*s == c)
			break ;
		++s;
	}
	return (char*)s;
}

char*	km_strrchr(const char* s, int needle)
{
	char*	last = NULL;
	char	c	 = needle;

	while (s) {
		if (*s == '\0')
			break ;
		if (*s == c)
			last = (char*)s;
		++s;
	}
	return (last);
}

int	km_strcmp(const char *s1, const char *s2)
{
	while (*s1) {
		if (*s1 != *s2)
			break ;
		++s1;
		++s2;
	}
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int	km_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);

	while (*s1 && n > 1) {
		if (*s1 != *s2)
			break ;
		++s1;
		++s2;
		--n;
	}
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

char*	km_strstr(const char *haystack, const char *needle)
{
	if (needle == NULL || *needle == '\0')
		return ((char*)haystack);
	
	size_t j;
	for (size_t i = 0; haystack[i] != '\0'; i++) {
		j = 0;
		while (haystack[i + j] == needle[j]) {
			if (needle[j + 1] == '\0')
				return ((char*)haystack + i);
			j++;
		}
	}
	return (NULL);
}

char*	km_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (needle == NULL || *needle == '\0')
		return ((char*)haystack);
	
	size_t j;
	for (size_t i = 0; i < len && haystack[i] != '\0'; i++) {
		j = 0;
		while (i + j < len && haystack[i + j] == needle[j]) {
			if (needle[j + 1] == '\0')
				return ((char*)haystack + i);
			j++;
		}
	}
	return (NULL);
}

char*	km_strcasestr(const char *haystack, const char *needle)
{
	if (needle == NULL || *needle == '\0')
		return ((char*)haystack);
	
	size_t j;
	for (size_t i = 0; haystack[i] != '\0'; i++) {
		j = 0;
		while (km_toupper(haystack[i + j]) == km_toupper(needle[j])) {
			if (needle[j + 1] == '\0')
				return ((char*)haystack + i);
			j++;
		}
	}
	return (NULL);
}

char*	km_strtok(char* restrict str, const char* restrict sep)
{
	static char* cur = NULL;
	
	if (str != NULL)
		cur = str;
	if (cur == NULL)
		return (NULL);

	// skip leading delimiter
	while (km_strchr(sep, *cur) != NULL)
		cur++;

	char* ret = cur;
	// create token
	while (*cur != '\0') {
		if (km_strchr(sep, *cur) != NULL) {
			*cur = '\0';
			++cur;
			return (ret);
		}
		++cur;
	}
	if (*ret == '\0')
		ret = NULL;
	cur = NULL;
	return (ret);
}

char*	km_strdup(const char *s1)
{
	size_t	len = km_strlen(s1) + 1;
	char*	ret = malloc(sizeof(char) * len);

	if (ret == NULL)
		return (NULL);
	return (km_memcpy(ret, s1, len));
}

char*	km_strndup(const char *s1, size_t n)
{
	size_t	len = km_strnlen(s1, n);
	char*	ret = malloc(sizeof(char) * (len + 1));

	if (ret == NULL)
		return (NULL);
	ret[len] = '\0';
	return (km_memcpy(ret, s1, len));
}
