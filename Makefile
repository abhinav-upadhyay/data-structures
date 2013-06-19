CFLAGS=-Wall -c -g
LFLAGS=-lm
all: test

test: test.o hashtable.o
	${CC} -o test test.o hashtable.o ${LFLAGS}

test.o: test.c
	${CC} ${CFLAGS} test.c

hashtable.o: hashtable.c
	${CC} ${CFLAGS} hashtable.c

clean:
	rm -rf *.o test
