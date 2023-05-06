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

#include <ctype.h>
#include <inttypes.h>
#include <stddef.h>

/*
** Because fsanitize is annoying and wont let me do bytehacks
*/
#if !__has_feature(address_sanitizer)

	// 8 bytes, with the most significant bit set in each of them
	#define HI_MAGIC 0x8080808080808080ULL
	// single byte: 1000 0000

	// 8 bytes, with the least signifcant bit set in each of them
	#define LO_MAGIC 0x0101010101010101ULL
	// single byte: 0000 0001

	static inline size_t align_eight_byte(const char* str)
	{
		size_t i = 0;

		while (str[i] != '\0' && ((size_t)(str + i) & (size_t)(sizeof(uint64_t) - 1)) != 0)
			i++;
		return (i);
	}

	static inline size_t magic_nullbyte_detector(const uint64_t* longword_ptr)
	{
		size_t		i = 0;
		uint64_t	longword;
		const char* found;

		while (1) {
			longword = *longword_ptr;

			/*
			** This statement will result in 0 if no null byte is found
			** Note: this will missfire if a byte has a value > 128
			*/
			if (((longword - LO_MAGIC) & HI_MAGIC) != 0)
			{
				found = (const char*)longword_ptr;

				if (found[0] == '\0')
					return (i);
				if (found[1] == '\0')
					return (i + 1);
				if (found[2] == '\0')
					return (i + 2);
				if (found[3] == '\0')
					return (i + 3);
				if (found[4] == '\0')
					return (i + 4);
				if (found[5] == '\0')
					return (i + 5);
				if (found[6] == '\0')
					return (i + 6);
				if (found[7] == '\0')
					return (i + 7);
			}
			i += sizeof(uint64_t);
			++longword_ptr;
		}
	}

	/*
	** Returns the length of the string
	*/
	size_t	km_strlen(const char* str)
	{
		// Align on eight byte boundry to ensure that you wont cross a cacheline whilst reading
		size_t offset = align_eight_byte(str);

		if (str[offset] == '\0')
			return (offset);

		// Make sure the pointer given is algined on an eight byte boundry
		return (magic_nullbyte_detector((const uint64_t*)(str + offset)) + offset);
	}

	#undef HI_MAGIC
	#undef LO_MAGIC

#else // Fsanitize is being used

	size_t km_strlen(const char* str)
	{
		size_t i = 0;

		while(str[i])
			++i;
		return (i);
	}

#endif

/*
** Returns the smallest out of length of the string or max_size,
** depending on which one is smaller
*/
size_t km_strnlen(const char* str, size_t max_size) {
	size_t i = 0;

	while (i < max_size && str[i]) {
		++i;
	}
	return (i);
}
