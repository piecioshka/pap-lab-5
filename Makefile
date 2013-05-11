SHELL = /bin/bash

CC = gcc
CFLAGS = -Wall --pedantic

TARGET = bin/
SRC = source/

all: zad1

zad1:
	${CC} ${CFLAGS} ${SRC}zad1/serwerPliki.c -o ${TARGET}zad1/serwerPliki.o
	${CC} ${CFLAGS} ${SRC}zad1/klientPliki.c -o ${TARGET}zad1/klientPliki.o

clean:
	find ${TARGET} -name "*.o" | xargs rm -rf

.PHONY: all clean
