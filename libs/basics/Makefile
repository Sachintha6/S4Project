CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =
LDLIBS =

SRC = test.c graph.c list.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: graph_test

graph_test: test.o list.o graph.o

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} graph_test

# END