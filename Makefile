CC = gcc
CFLAGS = -lncurses -I$(INCDIR)

SRCDIR = ./src/
INCDIR = ./include/

SOURCES = $(SRCDIR)*.c $(SRCDIR)utils/*.c

all: rogue

run: 
	./rogue

rogue: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(@)

clean: 
	rm -f rogue
