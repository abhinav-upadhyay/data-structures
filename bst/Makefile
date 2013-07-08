CFLAGS=-Wall -c -g
LFLAGS=-lm
all: main

main: main.o bst.o
	${CC} -o main main.o bst.o ${LFLAGS}

main.o: main.c
	${CC} ${CFLAGS} main.c

bst.o: bst.c
	${CC} ${CFLAGS} bst.c

clean:
	rm -rf *.o main
