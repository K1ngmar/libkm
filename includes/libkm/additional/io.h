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

#ifndef USELESS_IO_FUNCTIONS_H
# define USELESS_IO_FUNCTIONS_H

/*!
 * @brief prints char to fd
 * @param c char to print
 * @param fd filedescriptor to print to
 * @return apprearantly write cant fail XD
*/
void	km_putchar_fd(const char c, int fd);

/*!
 * @brief prints s to fd
 * @param s string to print
 * @param fd filedescriptor to print to
 * @return apprearantly write cant fail lol
*/
void	km_putstr_fd(const char* s, int fd);

/*!
 * @brief prints s with a newline after to fd
 * @param s string to print
 * @param fd filedescriptor to print to
 * @return apprearantly write cant fail...
*/
void	km_putendl_fd(const char* s, int fd);

/*!
 * @brief prints n to fd
 * @param n number to print
 * @param fd filedescriptor to print to
 * @return apprearantly write cant fail :)
*/
void	km_putnbr_fd(int n, int fd);

#endif
