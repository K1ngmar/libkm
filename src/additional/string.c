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
		joined[0] = '\0';
		km_strlcat(joined, s1, len + 1);
		km_strlcat(joined, s2, len + 1);
	}
	return (joined);
}

char*	km_safe_strjoin(const char* s1, const char* s2)
{
	if (s1 == NULL)
		return km_strjoin("", s2);
	return km_strjoin(s1, s2);
}

char*	km_strtrim(const char* str, const char* set)
{
	size_t len = km_strlen(str);
	size_t front = 0;
	size_t back = 0;

	// get amt to trim from front
	for (size_t i = 0; i < len && km_strchr(set, str[i]) != NULL; ++i)
		++front;
	// get amt to trim from back and there are characters left to trim
	if (front != len) {
		for (size_t i = len - 1; i > 0 && km_strchr(set, str[i]) != NULL; --i)
			++back;
	}

	len -= front + back;
	char* trimmed = malloc(sizeof(char) * (len + 1));
	if (trimmed == NULL)
		return (NULL);
	trimmed[len] = '\0';
	return (km_memcpy(trimmed, str + front, len));
}

static int	char_amt(long int nb)
{
	if (nb == 0)
		return (1);

	size_t amt = 0;
	if (nb < 0)
		++amt;
	while (nb != 0) {
		nb /= 10;
		++amt;
	}
	return (amt);  
}

char*	km_ltoa(long int nb)
{
	short int len = char_amt(nb);
	char* snb = malloc(sizeof(char) * len + 1);

	if (snb == NULL)
		return (NULL);
	snb[len] = '\0';

	size_t nbr = nb;
	if (nb < 0) {
		snb[0] = '-';
		nbr = -nb;
	}
	while (len > (0 + (nb < 0))) {
		--len;
		snb[len] = '0' + (nbr % 10);
		nbr /= 10;
	}
	return (snb);
}

char*	km_itoa(int nb) {
	return (km_ltoa(nb));
}

/*
** creates a copy of str with f applied to each character
*/
char*	km_strmapi(const char* str, char (*f)(unsigned int, char))
{
	size_t len = km_strlen(str);
	char* res = malloc(sizeof(char) * (len + 1));
	res[len] = '\0';

	if (res == NULL)
		return (NULL);

	while (len > 0) {
		len--;
		res[len] = f(len, str[len]);
	}
	return (res);
}

/*
** applies f to each character in str
*/
void km_striteri(char* str, void (*f)(unsigned int, char*))
{
	for (size_t i = 0; str[i] != '\0'; ++i)
		f(i, str);
}
