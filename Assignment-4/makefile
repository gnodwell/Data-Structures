CC = gcc
FLAGS = -std=c99 -Wall -pedantic

all: tree.o

tree.o: tree.c tree.h
	$(CC) $(FLAGS) -c tree.c

clean:
	rm *.o