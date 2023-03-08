all:hello bit shift

hello.o: hello.c
	gcc -std=c99 -Wall -pedantic -c hello.c -o hello.o

hello: hello.o
	gcc -std=c99 -Wall -pedantic hello.o -o hello

bit.o: bit.c
	gcc -std=c99 -Wall -pedantic -c bit.c -o bit.o

bit: bit.o
	gcc -std=c99 -Wall -pedantic bit.o -o bit

shift.o: shift.c
	gcc -std=c99 -Wall -pedantic -c shift.c -o shift.o

shift: shift.o
	gcc -std=c99 -Wall -pedantic shift.o -o shift


clean:
	rm -i hello.o hello bit.o bit shift.o shift
