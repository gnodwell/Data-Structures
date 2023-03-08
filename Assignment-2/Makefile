CC = gcc
FLAGS = -std=c99 -Wall -pedantic

all: array.o

array.o: array.c array.h
	$(CC) $(FLAGS) -c array.c

clean:
	rm *.o 