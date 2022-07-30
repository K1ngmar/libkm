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

#ifndef LIBKM_H
# define LIBKM_H

# include <ctype.h>

//////////
// libc //
//////////

	/*
	** character_checks.c
	*/
	int	km_isupper(int c);
	int	km_islower(int c);
	int	km_isalpha(int c);
	int	km_isdigit(int c);
	int	km_isascii(int c);
	int	km_isprint(int c);

	/*
	** strlen.c
	*/
	size_t	km_strlen(const char* str);
	size_t	km_strnlen(const char* str, size_t max_size);

	/*
	** string.c
	*/
	size_t	km_strlcpy(char* restrict dst, const char* restrict src, size_t dstsize);
	size_t	km_strlcat(char* restrict dst, const char* restrict src, size_t dstsize);
	int		km_toupper(int c);
	int		km_tolower(int c);
	char*	km_strchr(const char* haystack, int needle);
	char*	km_strrchr(const char* haystack, int needle);
	int		km_strcmp(const char *s1, const char *s2);

	/*
	** memcpy.c
	*/
	void*	km_memcpy(void *restrict dst, const void *restrict src, size_t n);

/////////
// sys //
/////////

	/*
	** cache_line_size.c
	*/
	size_t	get_cache_line_size(void);

#endif
