CFLAGS=-Wall -c -g
LFLAGS=-L./ -llist
all: liblist.a main 

liblist.a: list.o
	ar rcs liblist.a list.o

list.o: list.c
	${CC} ${CFLAGS} list.c

main: main.o 
	${CC} -o main main.o ${LFLAGS}

main.o: main.c
	${CC} ${CFLAGS} main.c


clean:
	rm -rf *.o *.a main
