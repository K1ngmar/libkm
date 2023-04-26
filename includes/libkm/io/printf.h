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

#ifndef LIBKM_PRINTF_H
# define LIBKM_PRINTF_H

#include <ctype.h>
#include <unistd.h>

/*!
 * @brief you know how dprintf works :p
 * @param fd -
 * @param format -
 * @param va_args -
 * @return number of characters printed, -1 on failure
*/
int	km_dprintf(int fd, const char* restrict format, ...);

/*!
 * @brief you know how printf works :p
 * @param format -
 * @param va_args -
 * @return number of characters printed, -1 on failure
*/
# define km_printf(format, ...) km_dprintf(STDOUT_FILENO, format, ##__VA_ARGS__)

/*!
 * @brief will allocated a string that will fit your data :p
 * @param str Do not pass this an allocated pointer, will cause a leak
 * @param format -
 * @param va_args -
 * @return number of characters printed, -1 on failure
*/
int	km_sprintf(char* restrict* str, const char* restrict format, ...);

/*!
 * @brief you know how snprintf works :p
 * @param str string where it will put all the formatted data
 * @param size maximum amount of characters it can write to str
 * @param format -
 * @param va_args -
 * @return number of characters printed, -1 on failure
*/
int km_snprintf(char* restrict str, const size_t size, const char* restrict format, ...);

#endif
