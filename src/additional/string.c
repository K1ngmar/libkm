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

	substr = malloc((nlen + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	km_memcpy(substr, s + start, nlen);
	substr[nlen] = '\0';
	return (substr);
}
