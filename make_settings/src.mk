ifndef SRC_MK
SRC_MK = 1

SRC :=	libc/character_checks.c \
		libc/string.c \
		libc/strlen.c \
		libc/ascii_to_integral.c \
		libc/memcpy.c \
		libc/memset.c \
		libc/memchr.c \
		libc/memcmp.c \
		libc/mem.c \
		additional/string.c \
		additional/split.c \
		additional/io.c \
		stdio/getdelim.c \
		stdio/printf/buffer.c \
		stdio/printf/conversion_integral.c \
		stdio/printf/conversion_string.c \
		stdio/printf/dispatcher.c \
		stdio/printf/integral_prefix.c \
		stdio/printf/printf.c

endif
