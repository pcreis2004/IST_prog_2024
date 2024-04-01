CC = gcc
CFLAGS=-Wall -g -O3 

cifras: main.o lib.o
	$(CC) $(CFLAGS) -o cifras main.o lib.o

main.o: lib.h
	$(CC) -c $(CFLAGS) main.c

lib.o: lib.h
	$(CC) -c $(CFLAGS) lib.c

clean::
	rm -f *.o core a.out cifras *~ 