CC = gcc
CFLAGS = -lncurses -lmenu -I$(INCDIR)

SRCDIR = ./src/
INCDIR = ./include/

SOURCES = $(SRCDIR)*.c $(SRCDIR)utils/*.c $(SRCDIR)windows/*.c

all: rogue

run: 
	./rogue

rogue: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(@)

clean: 
	rm -f rogue
