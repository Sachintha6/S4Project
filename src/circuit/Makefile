CC     = gcc
CFLAGS = ``
LIBS   = ``
DEBUG  = -Wall -Wextra

OBJECTS = test.o dijkstra.o mapGraph.o list.o

.PHONY: clean

all: main

main: $(OBJECTS)
	$(CC) $(DEBUG) $(OBJECTS) $(LIBS) -o $@

test.o: test.c dijkstra.h ../../libs/map/mapGraph.h ../../libs/map/list.h
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@

dijkstra.o: dijkstra.c dijkstra.h ../../libs/map/mapGraph.h ../../libs/map/list.h
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@

mapGraph.o: ../../libs/map/mapGraph.c ../../libs/map/mapGraph.h ../../libs/map/list.h
	$(CC) $(DEBUG) -c $< -o $@

list.o: ../../libs/map/list.c ../../libs/map/list.h
	$(CC) $(DEBUG) -c $< -o $@

clean:
	rm -f *.o main

run:
	./main