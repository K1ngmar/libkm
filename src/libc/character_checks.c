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

#define IsBetween(left_bound, right_bound) c >= left_bound && c <= right_bound

int	km_isupper(int c) {
	return (IsBetween('A', 'Z'));
}

int	km_islower(int c) {
	return (IsBetween('a', 'z'));
}

int	km_isalpha(int c) {
	return (km_isupper(c) || km_islower(c));
}

int km_isdigit(int c) {
	return (IsBetween('0', '9'));
}

int km_isascii(int c) {
	return (IsBetween(0, 127));
}

int km_isprint(int c) {
	return (IsBetween(32, 126));
}

#undef IsBetween
