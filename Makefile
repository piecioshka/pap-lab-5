SHELL = /bin/bash

CC = gcc
CFLAGS = -Wall --pedantic

TARGET = bin/
SRC = source/

all:
	@for number in {1..12} ; do \
	    echo ${SRC}zad$$number/client.* ; \
	    ${CC} ${CFLAGS} ${SRC}zad$$number/client.c -o ${TARGET}zad$$number/client.o ; \
	    echo ${SRC}zad$$number/server.* ; \
	    ${CC} ${CFLAGS} ${SRC}zad$$number/server.c -o ${TARGET}zad$$number/server.o ; \
	    if [ $$number -lt 12 ]; then \
		echo "------------------------------------------------------------" ; \
	    fi ; \
	done

clean:
	find ${TARGET} -name "*.o" | xargs rm -rf

.PHONY: all clean
