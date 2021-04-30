CC = gcc
CFLAGS = -Wall -Wextra

all: test

test: test.o mapGraph.o list.o
test.o: test.c mapGraph.h list.h
mapGraph.o: mapGraph.c mapGraph.h list.h
list.o: list.c list.h

.PHONY: clean

clean:
	${RM} test test.o mapGraph.o list.o