CFLAGS=-Wall -c -g
LFLAGS=-L./ -llist
all: main

main: main.o liblist.a
	${CC} -o main main.o ${LFLAGS}

main.o: main.c
	${CC} ${CFLAGS} main.c

liblist.a: list.o
	ar rcs liblist.a list.o

list.o: list.c
	${CC} ${CFLAGS} list.c

clean:
	rm -rf *.o *.a main
