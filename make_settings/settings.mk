ifndef SETTINGS_MK
SETTINGS_MK = 1

NAME	= libkm.a

CFLAGS	= -Wall -Wextra -Werror -pedantic
IFLAGS	= -I$(IDIR)

SDIR	= src
ODIR	= .obj
IDIR	= includes

TEST	= tests
TESTS	= $(wildcard $(TEST)/*.c)
TESTBIN = $(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TESTS))


OS := $(shell uname -s)

ADDITIONAL_LIBRARIES = 
ifeq ($(OS), Linux)
	ADDITIONAL_LIBRARIES += -lbsd
endif

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
OBJ := $(addprefix $(ODIR)/, $(SRC:.c=.o))

# TEST_OBJ    := $(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(SRC))

endif
