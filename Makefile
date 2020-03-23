CC = gcc
CFLAGS = -lncurses -I$(INCDIR)

SRCDIR = ./src/
INCDIR = ./include/

SOURCES = $(SRCDIR)*.c

all: rogue run clean

run: 
	./rogue

rogue: 
	$(CC) $(SOURCES) $(CFLAGS) -o $(@)

clean: 
	rm rogue
