CC = gcc 
CFLAGS = -Wall -pedantic -std=c11

all: buildidx key2val val2key

util: util.c util.h
	$(CC) $(CFLAGS) -c util.c -o util.o

hashfn: hashfn.c hashfn.h
	$(CC) $(CFLAGS) -c hashfn.c -o hashfn.o

buildidx.o: buildidx.c buildidx.h
	$(CC) $(CFLAGS) -c buildidx.c -o buildidx.o

buildidx: buildidx.o util.o hashfn.o
	$(CC) $(CFLAGS) -o buildidx buildidx.o util.o hashfn.o

key2val.o: key2val.c 
	$(CC) $(CFLAGS) -c key2val.c -o key2val.o

key2val: key2val.o util.o hashfn.o
	$(CC) $(CFLAGS) -o key2val key2val.o util.o hashfn.o

val2key.o: val2key.c
	$(CC) $(CFLAGS) -c val2key.c -o val2key.o

val2key: val2key.o util.o hashfn.o
	$(CC) $(CFLAGS) -o val2key val2key.o util.o hashfn.o

clean:
	rm *.o buildidx key2val val2key *.khs *.vhs