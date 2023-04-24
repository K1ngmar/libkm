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

# include <sys/types.h>
# include <unistd.h>

/////////////
// Macro's //
/////////////

# define RETURN_IF_FAILED(x) do { if (x < 0) return (-1); } while(0)

# define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
# define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

///////////
// stdio //
///////////

	/*
	** getdelim.c
	*/
	ssize_t	km_getdelim(char** restrict line, int delim, int fd);
	ssize_t	km_getline(char** restrict line, int fd);

	/*
	** printf/printf.c
	*/
	int	km_dprintf(int fd, const char* restrict format, ...);
# define km_printf(format, ...) km_dprintf(STDOUT_FILENO, format, ##__VA_ARGS__)
	int	km_sprintf(char* restrict* str, const char* restrict format, ...);
	int km_snprintf(char* restrict str, const size_t size, const char* restrict format, ...);

/////////
// sys //
/////////

	/*
	** cache_line_size.c
	*/
	size_t	get_cache_line_size(void);

#endif
