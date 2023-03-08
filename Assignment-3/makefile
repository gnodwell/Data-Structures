CC = gcc
FLAGS = -std=c99 -Wall -pedantic

all: list.o 

list.o: list.c list.h
	$(CC) $(FLAGS) -c list.c

clean:
	rm *.o