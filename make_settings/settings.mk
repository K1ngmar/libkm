ifndef SETTINGS_MK
SETTINGS_MK = 1

NAME	= libkm

CFLAGS	= -Wall -Wextra -Werror -pedantic -std=c98
IFLAGS	= -I$(IDIR)
LFLAGS	= 

SDIR	= src
ODIR	= obj
IDIR	= includes

ifdef DEBUG
	CFLAGS += -D DEBUG
endif

ifdef LEAKS
	CFLAGS += -D LEAKS
endif

ifdef FSANITIZE
	CFLAGS += -D FSANITIZE
	LFLAGS = -fsanitize=address
endif

include ./make_settings/src.mk
OBJ := $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SRC))

endif
