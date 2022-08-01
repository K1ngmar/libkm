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
	int		km_strcmp(const char* s1, const char* s2);
	int		km_strncmp(const char* s1, const char* s2, size_t n);
	char*	km_strstr(const char* haystack, const char* needle);
	char*	km_strnstr(const char* haystack, const char* needle, size_t len);
	char*	km_strcasestr(const char* haystack, const char* needle);
	char*	km_strtok(char* restrict str, const char* restrict sep);
	char*	km_strdup(const char* s1);
	char*	km_strndup(const char* s1, size_t n);

	/*
	** ascii_to_integral.c
	*/
	int			km_atoi(const char* str);
	long		km_atol(const char* str);
	long long	km_strtoll(const char* restrict str, char** restrict endptr, int base);
	long		km_strtol(const char* restrict str, char** restrict endptr, int base);

	/*
	** memcpy.c
	*/
	void*	km_memcpy(void* restrict dst, const void* restrict src, size_t n);

	/*
	** memset.c
	*/
	void*	km_memset(void* restrict b, int c, size_t len);

	/*
	** memchr.c
	*/
	void*	km_memchr(void const* s_in, int c_in, size_t n);

	/*
	** memcmp.c
	*/
	int		km_memcmp(const void* s1p, const void* s2p, size_t n);

	/*
	** mem.c
	*/
	void*	km_memmove(void* dstp, const void* srcp, size_t n);
	void	km_bzero(void* s, size_t n);
	void*	km_calloc(size_t count, size_t size);

/////////
// sys //
/////////

	/*
	** cache_line_size.c
	*/
	size_t	get_cache_line_size(void);

#endif
