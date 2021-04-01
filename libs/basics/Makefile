CC = gcc
CFLAGS = -Wall -Wextra

all: test

test: test.o graph.o list.o
test.o: test.c graph.h list.h
graph.o: graph.c graph.h list.h
list.o: list.c list.h

.PHONY: clean

clean:
	${RM} test test.o graph.o list.o