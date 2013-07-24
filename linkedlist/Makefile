CFLAGS=-Wall -c -g
LFLAGS=-lm
all: main

main: main.o list.o
	${CC} -o main main.o list.o ${LFLAGS}

main.o: main.c
	${CC} ${CFLAGS} main.c

list.o: list.c
	${CC} ${CFLAGS} list.c

clean:
	rm -rf *.o main
