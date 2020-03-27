CC = gcc
CFLAGS = -Wall -lncurses -lmenu -I$(INCDIR)

SRCDIR = ./src/
INCDIR = ./include/

SOURCES = $(SRCDIR)*.c \
			 $(SRCDIR)utils/*.c \
			 $(SRCDIR)windows/*.c \
			 $(SRCDIR)entities/*.c \
			 $(SRCDIR)entities/items/*.c

all: rogue

run: 
	./rogue

rogue: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(@)

clean: 
	rm -f rogue
