ifndef SETTINGS_MK
SETTINGS_MK = 1

NAME	= libkm

CC		= clang

CFLAGS	= -Wall -Wextra -Werror -pedantic
IFLAGS	= -I$(IDIR)

SDIR	= src
ODIR	= obj
IDIR	= includes

TEST	= tests
TESTS	= $(wildcard $(TEST)/*.c)
TESTBIN = $(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TESTS))

ifdef DEBUG
	CFLAGS += -g -D DEBUG
endif

ifdef LEAKS
	CFLAGS += -D LEAKS
endif

ifdef FSANITIZE
	CFLAGS += -D FSANITIZE
	CFLAGS += -g -fsanitize=address
endif

include ./make_settings/src.mk
OBJ := $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SRC))

endif
