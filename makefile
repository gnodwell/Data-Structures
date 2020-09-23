all: bandb test_getbytes test_getbits test_bits2ull test_bits2ll test_spff test_dpff

bandb.o: bandb.c bandb.h
	gcc -std=c99 -Wall -pedantic -c bandb.c -o bandb.o

bandb: bandb.o
	gcc -std=c99 -Wall -pedantic bandb.o -o bandb

test_getbytes.o: test_getbytes.c bandb.h
	gcc -std=c99 -Wall -pedantic -c test_getbytes.c -o test_getbytes.o

test_getbytes: test_getbytes.o
	gcc -std=c99 -Wall -pedantic test_getbytes.o -o test_getbytes

test_getbits.o: test_getbits.c bandb.h
	gcc -std=c99 -Wall -pedantic -c test_getbits.c -o test_getbits.o

test_getbits: test_getbits.o
	gcc -std=c99 -Wall -pedantic test_getbits.c -o test_getbits.o

test_bits2ull.o: test_bits2ull.c bandb.h
	gcc -std=c99 -Wall -pedantic -c test_bits2ull.c -o test_bits2ull.o

test_bits2ull: test_bits2ull.o
	gcc -std=c99 -Wall -pedantic test_bits2ull.o -o test_bits2ull

test_bits2ll.o: test_bits2ll.c bandb.h
	gcc -std=c99 -Wall -pedantic -c test_bits2ll.c -o test_bits2ll.o

test_bits2ll: test_bits2ll.o
	gcc -std=c99 -Wall -pedantic test_bits2ll.o -o test_bits2ll

test_spff.o: test_spff.c bandb.h
	gcc -std=c99 -Wall -pedantic -c test_spff.c -o test_spff.o

test_spff: test_spff.o
	gcc -std=c99 -Wall -pedantic test_spff.o -o test_spff

test_dpff.o: test_dpff.c bandb.h
	gcc -std=c99 -Wall -pedantic -c test_dpff.c -o test_dpff.o

test_dpff: test_dpff.o
	gcc -std=c99 -Wall -pedantic test_dpff.o -o test_dpff


clean:
	rm 	-i bandb.o bandb test_getbytes.o test_getbytes test_getbits.o test_getbits test_bits2ull.o test_bits2ull test_bits2ll.o test_bits2ll test_spff.o test_spff test_dpff.o test_dpff