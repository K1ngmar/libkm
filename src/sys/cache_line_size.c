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

#include <sys/sysctl.h>
#include <stdio.h>

/*
** Returns cache line size in bytes
** Generally this will be 64 bytes
*/

#if defined(__APPLE__)
	
	size_t	get_cache_line_size(void)
	{
		size_t line_size = 0;
		size_t sizeof_line_size = sizeof(line_size);
		sysctlbyname("hw.cachelinesize", &line_size, &sizeof_line_size, NULL, 0);
		return line_size;
	}

#elif defined(linux)

	size_t	get_cache_line_size(void)
	{
		return sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
	}

#else
	#error Unrecognized platform
#endif
