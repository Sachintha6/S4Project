CC     = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0 gmodule-export-2.0 glib-2.0`
LIBS   = `pkg-config --libs gtk+-3.0 gmodule-2.0 glib-2.0` -fsanitize=address
DEBUG  = -Wall -g

COMMANDS = interface print events mapGraph list
OBJFOLDER = ../../objects
OBJECTS = $(OBJFOLDER)/interface.o $(OBJFOLDER)/print.o $(OBJFOLDER)/events.o $(OBJFOLDER)/mapGraph.o $(OBJFOLDER)/list.o

.PHONY: clean

all: main

main: $(COMMANDS)
	$(CC) $(DEBUG) $(OBJECTS) $(LIBS) -o $@

interface: main.c gui.h ../../libs/map/mapGraph.h ../../libs/map/list.h
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $(OBJFOLDER)/$@.o

print: gui_print.c gui.h
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $(OBJFOLDER)/$@.o

events: gui_events.c gui.h
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $(OBJFOLDER)/$@.o

mapGraph: ../../libs/map/mapGraph.c ../../libs/map/mapGraph.h ../../libs/map/list.h
	$(CC) $(DEBUG) -c $< -o $(OBJFOLDER)/$@.o

list: ../../libs/map/list.c ../../libs/map/list.h
	$(CC) $(DEBUG) -c $< -o $(OBJFOLDER)/$@.o

clean:
	rm -f $(OBJFOLDER)/*.o main

run:
	./main
