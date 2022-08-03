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

#include <unistd.h>
#include <stdlib.h>
#include <libkm.h>

void	km_putchar_fd(const char c, int fd) {
	write(fd, &c, 1);
}

void	km_putstr_fd(const char* s, int fd) {
	size_t len = km_strlen(s);
	write(fd, s, len);
}

void	km_putendl_fd(const char* s, int fd) {
	km_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

void	km_putnbr_fd(int n, int fd) {
	char* snb = km_itoa(n);
	if (snb == NULL)
		return ;
	km_putstr_fd(snb, fd);
	free(snb);
}
