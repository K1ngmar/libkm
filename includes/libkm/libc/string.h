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

#ifndef LIBKM_LIBC_STRING_H
# define LIBKM_LIBC_STRING_H

# include <ctype.h>

/////////////////////////
// ascii_to_integral.c //
/////////////////////////

	/*!
	 * @brief converts str to integer
	 * @param str -
	 * @return -
	 * @NOTE: first skips whitespace, then stops at first non number char
	*/
	int			km_atoi(const char* str);

	/*!
	 * @brief converts str to long
	 * @param str -
	 * @return -
	 * @NOTE: first skips whitespace, then stops at first non number char
	*/
	long		km_atol(const char* str);

	/*!
	 * @brief converts str to long long
	 * @param str -
	 * @param endptr will point to the character the conversion stopped at (if not NULL)
	 * @param base base must be between 2 and 36 or the special value 0
	 *			   if base is 0, the base will be determined by the leading characters:
	 *			   0b = binary, 0 = octal, 1-9 = decimal, 0x = hexadecimal
	 * @return -
	 * @NOTE: first skips whitespace, then stops at first non number char
	*/
	long long	km_strtoll(const char* restrict str, char** restrict endptr, int base);

	/*!
	 * @brief converts str to long
	 * @param str -
	 * @param endptr will point to the character the conversion stopped at (if not NULL)
	 * @param base base must be between 2 and 36 or the special value 0
	 *			   if base is 0, the base will be determined by the leading characters:
	 *			   0b = binary, 0 = octal, 1-9 = decimal, 0x = hexadecimal
	 * @return -
	 * @NOTE: first skips whitespace, then stops at first non number char
	*/
	long		km_strtol(const char* restrict str, char** restrict endptr, int base);

////////////////////////
// character_checks.c //
////////////////////////

	/*!
	 * @brief checks if c is uppercase
	 * @param c -
	 * @return true, false
	*/
	int	km_isupper(int c);

	/*!
	 * @brief checks if c is lowercase
	 * @param c -
	 * @return true, false
	*/
	int	km_islower(int c);

	/*!
	 * @brief checks if c is in the alphabet
	 * @param c -
	 * @return true, false
	*/
	int	km_isalpha(int c);

	/*!
	 * @brief checks if c is a digit
	 * @param c -
	 * @return true, false
	*/
	int	km_isdigit(int c);

	/*!
	 * @brief checks if c is a valid ascii value
	 * @param c -
	 * @return true, false
	*/
	int	km_isascii(int c);

	/*!
	 * @brief checks if c is a visible character
	 * @param c -
	 * @return true, false
	*/
	int	km_isprint(int c);

//////////////
// string.c //
//////////////

	/*!
	 * @brief copies up to dstsize - 1 characters from the string src to dst, NUL-terminating the result if dstsize is not 0.
	 * @param dst -
	 * @param src -
	 * @param dstsize - 
	 * @return return the total length of the string they tried to create.
	 * 
	 * @NOTE: If the return value is >= dstsize, the output string has been truncated.
	 * 		  It is the caller's responsibility to handle this.
	*/
	size_t	km_strlcpy(char* restrict dst, const char* restrict src, size_t dstsize);

	/*!
	 * @brief appends string src to the end of dst. It will append at most dstsize - strlen(dst) - 1 characters. 
	 		  It will then NUL-terminate, unless dstsize is 0 or the original dst string was longer than dstsize
			  (in practice this should not happen as it means that either dstsize is incorrect or that dst is not a proper string).
	 * @param dst -
	 * @param src -
	 * @param dstsize - 
	 * @return return the total length of the string they tried to create.
	 * 
	 * @NOTE: If the return value is >= dstsize, the output string has been truncated.
	 * 		  It is the caller's responsibility to handle this.
	*/
	size_t	km_strlcat(char* restrict dst, const char* restrict src, size_t dstsize);

	/*!
	 * @brief returns c to its uppercase variant, if not lowercase returns c
	 * @param c -
	 * @return uppercase variant of c
	*/
	int		km_toupper(int c);

	/*!
	 * @brief returns c to its lowercase variant, if not uppercase returns c
	 * @param c -
	 * @return lowercase variant of c
	*/
	int		km_tolower(int c);

	/*!
	 * @brief locates the first occurrence of needle in the string pointed to by haystack.
	 		  The terminating null character is considered to be part of the string;
			  therefore if needle is ‘\0’, the functions locate the terminating ‘\0’.
	 * @param haystack -
	 * @param needle (converted to a char)
	 * @return return a pointer to the located character, or NULL if the character does not appear in the string.
	*/
	char*	km_strchr(const char* haystack, int needle);

	/*!
	 * @brief locates the last occurrence of needle in the string pointed to by haystack.
	 		  The terminating null character is considered to be part of the string;
			  therefore if needle is ‘\0’, the functions locate the terminating ‘\0’.
	 * @param haystack -
	 * @param needle (converted to a char)
	 * @return return a pointer to the located character, or NULL if the character does not appear in the string.
	*/
	char*	km_strrchr(const char* haystack, int needle);

	/*!
	 * @brief lexicographically compare the null-terminated strings s1 and s2.
	 * @param s1 -
	 * @param s2 -
	 * @return return an integer greater than, equal to, or less than 0
	*/
	int		km_strcmp(const char* s1, const char* s2);

	/*!
	 * @brief lexicographically compare the null-terminated strings s1 and s2. but not more than n characters
	 * @param s1 -
	 * @param s2 -
	 * @param n the maximum amount of bytes to compare
	 * @return return an integer greater than, equal to, or less than 0
	*/
	int		km_strncmp(const char* s1, const char* s2, size_t n);

	/*!
	 * @brief function locates the first occurrence of the null-terminated string needle in the null-terminated string haystack.
	 * @param haystack -
	 * @param needle -
	 * @return If needle is an empty string, haystack is returned;
	 * 		   if needle occurs nowhere in haystack, NULL is returned; 
	 * 		   otherwise a pointer to the first character of the first occurrence of needle is returned.
	*/
	char*	km_strstr(const char* haystack, const char* needle);

	/*!
	 * @brief function locates the first occurrence of the null-terminated string needle in the null-terminated string haystack.
	 		  where not more than len characters are searched.
	 * @param haystack -
	 * @param needle -
	 * @param len -
	 * @return If needle is an empty string, haystack is returned;
	 * 		   if needle occurs nowhere in haystack, NULL is returned; 
	 * 		   otherwise a pointer to the first character of the first occurrence of needle is returned.
	*/
	char*	km_strnstr(const char* haystack, const char* needle, size_t len);

	/*!
	 * @brief similar to strstr(), but ignores the case of both strings.
	 * @param haystack -
	 * @param needle -
	 * @return If needle is an empty string, haystack is returned;
	 * 		   if needle occurs nowhere in haystack, NULL is returned; 
	 * 		   otherwise a pointer to the first character of the first occurrence of needle is returned.
	*/
	char*	km_strcasestr(const char* haystack, const char* needle);

	/*!
	 * @brief function is used to isolate sequential tokens in a null-terminated string, str.
	 		   These tokens are separated in the string by at least one of the characters in sep.
			   The first time that strtok() is called, str should be specified;
			   subsequent calls, wishing to obtain further tokens from the same string, should pass a null pointer instead.
			   The separator string, sep, must be supplied each time, and may change between calls.
	* @param str -
	* @param sep - 
	*
    * @NOTE: The implementation will behave as if no library function calls strtok().
	*/
	char*	km_strtok(char* restrict str, const char* restrict sep);

	/*!
	 * @brief allocates sufficient memory for a copy of the string s1, does the copy, and returns a pointer to it.
	 * @param s1 -
	 * @return copy of s1, NULL on failure
	*/
	char*	km_strdup(const char* s1);

	/*!
	 * @brief copies at most n characters from the string s1 always NUL terminating the copied string.
	 * @param s1 -
	 * @param n
	 * @return copy of s1, NULL on failure
	*/
	char*	km_strndup(const char* s1, size_t n);

//////////////
// strlen.c //
//////////////

	/*!
	 * @brief gets length of str
	 * @param str -
	 * @return -
	*/
	size_t	km_strlen(const char* str);

	/*!
	 * @brief attempts to compute the length of s, but never scans beyond the first maxlen bytes of s.
	 * @param str -
	 * @param max_size -
	 * @return -
	*/
	size_t	km_strnlen(const char* str, size_t max_size);

#endif
