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

#ifndef LIBKM_ADDITIONAL_STRING_H
# define LIBKM_ADDITIONAL_STRING_H

#include <ctype.h>

//////////////
// String.h //
//////////////

	/*!
	 * @brief copies from start for n bytes
	 * @param s the source string
	 * @param start the start offset
	 * @param len the amount of bytes to copy
	 * @return the substring or NULL on failure
	*/
	char*	km_substr(const char* s, unsigned int start, size_t len);

	/*!
	 * @brief concatenates s2 after s1
	 * @param s1 not checked for NULL
	 * @param s2 -
	 * @brief concatenated string, NULL on failure
	*/
	char*	km_strjoin(const char* s1, const char* s2);

	/*!
	 * @brief concatenates s2 after s1, even if s1 is NULL
	 * @param s1 -
	 * @param s2 -
	 * @return concatenated string, NULL on failure
	*/	
	char*	km_safe_strjoin(const char* s1, const char* s2);

	/*!
	 * @brief trims all characters contained in set from the front and the end of the string
	 * @param str -
	 * @param set -
	 * @return trimmed string, NULL on failure
	*/
	char*	km_strtrim(const char* str, const char* set);

	/*!
	 * @brief long to ascii
	 * @param nb -
	 * @return nb in string form, NULL on failure
	*/
	char*	km_ltoa(long int nb);

	/*!
	 * @brief integer to ascii
	 * @param nb -
	 * @return nb in string form, NULL on failure
	*/
	char*	km_itoa(int nb);

	/*!
	 * @brief creates a copy of str with f applied to each character
	 * @param str -
	 * @param f (takes index and character)
	 * @return a copy with f applied on each character or NULL on failure
	*/
	char*	km_strmapi(const char* str, char (*f)(unsigned int, char));

	/*!
	 * @brief applies f to each character in str
	 * @param str -
	 * @param f (takes index and character)
	*/
	void	km_striteri(char* str, void (*f)(unsigned int, char*));

/////////////
// split.c //
/////////////

	/*!
	 * @brief splits str into substrings on the delimiter c
	 * @param str -
	 * @param c a new substring will be created every time when this character is found in str
	 * @return list containing all substrings (allocated), NULL on failure
	 * 
	 * @NOTE: will crate a duplicate if c is not found.
	*/
	char**	km_split(const char* str, char c);

#endif
