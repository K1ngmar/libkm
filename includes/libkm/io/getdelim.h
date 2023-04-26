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

#ifndef LIBKM_GETDELIM_H
# define LIBKM_GETDELIM_H

#include <sys/types.h>

/*!
 * @brief reads a line from stream, delimited by the character delimiter. 
 		  The getline() function is equivalent to getdelim() with the newline character as the delimiter.
		  The delimiter character is included as part of the line, unless the end of the file is reached.
 * @param line here the read line will be stored, make sure it is not allocated since that wil cause a leak
 * @param delim the character to 
 * @param fd filedescriptorto read from
 * @return amount of bytes in line, -1 on error
*/
ssize_t	km_getdelim(char** restrict line, int delim, int fd);

/*!
 * @brief getdelim but with a delimiter of '\n'
 * @param line here the read line will be stored, make sure it is not allocated because that will cause a leak
 * @param fd the filedescriptor to read from
 * @return amount of bytes in line, -1 on error
*/
ssize_t	km_getline(char** restrict line, int fd);

#endif
