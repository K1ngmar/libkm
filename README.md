# 📚libkm
Inspired by the 42 project Libft where we had to rewrite a bunch of libc functions with a couple additional ones, this project improves upon my libft and aims to be safer, cleaner, more complete and performant!

## 📦 CONTENTS
- [Containers](#-containers)
- [IO](#-io)
- [String](#-string)
- [Memory](#-memory)
- [Sys](#-sys)
- [Additional](#-additional)

## 🫙 Containers:
**Vector**  
Like in c++ this vector is templated, only you have to register the types yourself using macros
> For a more detailed description of vector check out [this!](https://github.com/K1ngmar/libkm/blob/main/includes/libkm/containers/vector.h)

Here is a quick example on how to create a vector of type int
```c++
#include "libkm/containers/vector.h"

// put this in the .h 
REGISTER_KM_VECTOR_PROTOTYPES(int, integer)

// put this in the .c
REGISTER_KM_VECTOR_SOURCE(int, integer)

//after registering the vector you can initialise it like this:
km_vector_integer_initialise(&vec, NULL, NULL);

// and destroy it like this
km_vector_integer_destroy(&vec);
```

## 🧬 IO:
**Printf family**
> For a more detailed description of the printf family check out [this!](https://github.com/K1ngmar/libkm/blob/main/includes/libkm/io/printf.h)
- km_dprintf()
- km_printf()
- km_sprintf()
- km_snprintf()

**Get delim**
> For a more detailed description of the getdelim functions check out [this!](https://github.com/K1ngmar/libkm/blob/main/includes/libkm/io/getdelim.h)
- getdelim
- getline

## 📖 String:
**Ascii to integral conversions**
> For a more detailed description of the integral conversions check out [this!](https://github.com/K1ngmar/libkm/blob/main/includes/libkm/string.h)
- km_atoi()
- km_atol()
- km_strtoll()
- km_strtol()

**String**
> For a more detailed description of the string functions check out [this!](https://github.com/K1ngmar/libkm/blob/main/includes/libkm/string.h#L110)
- km_strlcpy()
- km_strlcat()
- km_toupper()
- km_tolower()
- km_strchr()
- km_strrchr()
- km_strcmp()
- km_strncmp()
- km_strstr()
- km_strnstr()
- km_strcasestr()
- km_strtok()
- km_strdup()
- km_strndup()
- km_strlen()
- km_strnlen()
- km_isupper()
- km_islower()
- km_isalpha()
- km_isdigit()
- km_isascii()
- km_isprint()

## 🃏 Memory:
> For a more detailed description of the memory functions checkout [this!](https://github.com/K1ngmar/libkm/blob/main/includes/libkm/memory.h)
- km_memmove()
- km_bzero()
- km_calloc()
- km_stupid_realloc()
- km_memchr()
- km_memcmp()
- km_memcpy()
- km_memset()

## 💽 Sys:
> For a more detailed description of the system functions checkout [this!](https://github.com/K1ngmar/libkm/blob/main/includes/libkm/sys/cacheline.h)
- get_cache_line_size()

## ➕ Additional:
**IO**
> For a more detailed description about the additional IO functions checkout [this!](https://github.com/K1ngmar/libkm/blob/main/includes/libkm/additional/io.h)
- km_putchar_fd()
- km_putstr_fd()
- km_putendl_fd()
- km_putnbr_fd()

**String**
> For a more detailed description about the additional String functions checkout [this!](https://github.com/K1ngmar/libkm/blob/main/includes/libkm/additional/string.h)
- km_substr()
- km_strjoin()
- km_safe_strjoin()
- km_strtrim()
- km_ltoa()
- km_itoa()
- km_strmapi()
- km_striteri()
- km_split()

