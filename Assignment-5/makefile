CC = gcc
FLAGS = -std=c99 -Wall -pedantic

all: hash.o

hash.o: hash.c hash.h
	$(CC) $(FLAGS) -c hash.c

clean:
	rm *.o h