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
#include <stdlib.h>

char*	km_substr(const char* s, unsigned int start, size_t len)
{
	size_t	nlen = km_strnlen(s + start, len);
	char*	substr;

	substr = malloc(sizeof(char) * (nlen + 1));
	if (substr == NULL)
		return (NULL);
	km_memcpy(substr, s + start, nlen);
	substr[nlen] = '\0';
	return (substr);
}

char*	km_strjoin(const char* s1, const char* s2)
{
	char*	joined;
	size_t	len = km_strlen(s1) + km_strlen(s2);

	joined = malloc(sizeof(char) * (len + 1));
	if (joined != NULL) {
		km_strlcat(joined, s1, len + 1);
		km_strlcat(joined, s2, len + 1);
	}
	return (joined);
}
