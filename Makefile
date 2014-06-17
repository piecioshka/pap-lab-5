SHELL = /bin/bash
CC = gcc
CFLAGS = -Wall --pedantic
TARGET = bin/
SRC = source/

zad1:
	${CC} ${CFLAGS} ${SRC}zad1/serwerPliki.c -o ${TARGET}zad1/serwerPliki.o
	${CC} ${CFLAGS} ${SRC}zad1/klientPliki.c -o ${TARGET}zad1/klientPliki.o

zad4:
	${CC} ${CFLAGS} ${SRC}zad4/serwer.c -o ${TARGET}zad4/serwer.o
	${CC} ${CFLAGS} ${SRC}zad4/klient.c -o ${TARGET}zad4/klient.o

zad7:
	echo "not ready for task 7"

zad8:
	echo "not ready for task 8"

zad9:
	echo "not ready for task 9"

clean:
	find ${TARGET} -name "*.o" | xargs rm -rf
