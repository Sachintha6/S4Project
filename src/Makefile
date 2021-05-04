CC     = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0 gmodule-export-2.0 glib-2.0`
LIBS   = `pkg-config --libs gtk+-3.0 gmodule-2.0 glib-2.0`
DEBUG  = -Wall -g

OBJECTS = interface.o print.o events.o mapGraph.o list.o

.PHONY: clean

all: main

main: $(OBJECTS)
	$(CC) $(DEBUG) $(OBJECTS) $(LIBS) -o $@

interface.o: main.c gui.h ../libs/map/mapGraph.h ../libs/map/list.h
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@

print.o: gui_print.c gui.h
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@

events.o: gui_events.c gui.h
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@

mapGraph.o: ../libs/map/mapGraph.c ../libs/map/mapGraph.h ../libs/map/list.h
	$(CC) $(DEBUG) -c $< -o $@

list.o: ../libs/map/list.c ../libs/map/list.h
	$(CC) $(DEBUG) -c $< -o $@

clean:
	rm -f *.o main

run:
	./main
