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

#include <stdlib.h>

#define IsWhiteSpace(c) c == ' ' || (c >= '\t' && c <= '\r')

long	km_atol(const char *str)
{
	long long res = 0;
	long long sgn = 1;

	while (IsWhiteSpace(*str))
		str++;
	if (*str == '-')
		sgn = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9') {
		res = res * 10 + *str - '0';
		str++;
	}
	return ((res * sgn));
}

int		km_atoi(const char *str)
{
	return ((int)km_atol(str));
}

static int determine_base(const char* restrict* str, int base)
{
	int tmp_base = 10;

	if (**str == '0') {
		(*str)++;
		switch (**str) {
			case 'b':
			case 'B':
				tmp_base = 2;
				(*str)++;
				break;
			case 'x': ;
			case 'X':
				tmp_base = 16;
				(*str)++;
				break;
			default:
				tmp_base = 1;
		}
	}
	return (base == 0) ? tmp_base : base;
}

/*
** base must be between 2 and 36 or the special value 0
** if base is 0, the base will be determined by the leading characters,
** 0b = binary, 0 = octal, 1-9 = decimal, 0x = hexadecimal
*/
long long km_strtoll(const char* restrict str, const char** restrict endptr, int base)
{
	long long	res		= 0;
	long long	sgn		= 1;
	const char*	begin	= str;

	while (IsWhiteSpace(*str))
		str++;
	if (*str == '-')
		sgn = -1;
	if (*str == '+' || *str == '-')
		str++;
	
	if (base == 0 || base == 2 || base == 16)
		base = determine_base(&str, base);

	char	c		= *str;
	int		offset	= (base > 10) ? base - 10 : 0;
	int		anchor;
	int		read = 0;

	while (c != '\0') {
		// its ugly, but its branchless
		anchor =	('0' * (c >= '0' && c <= '9')) +
					('a' * (c >= 'a' && c <= 'a' + offset)) +
					('A' * (c >= 'A' && c <= 'A' + offset));

		// found invalid character
		if (anchor == 0 || (anchor >= '9' && base <= 10) || (anchor == '0' && c >= '0' + base))
			break ;
		if (anchor > '9')
			anchor -= 10;

		res = res * base + c - anchor;
		c = *(++str);
		++read;
	}
	
	if (endptr != NULL) {
		if (c == '\0' && read == 0)
			*endptr = (char*)begin;
		else
			*endptr = (char*)str;
	}
	return ((res * sgn));
}

long	km_strtol(const char* restrict str, const char** restrict endptr, int base) {
	return ((long)km_strtoll(str, endptr, base));
}

#undef IsWhiteSpace
