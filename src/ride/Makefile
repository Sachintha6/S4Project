CC     = gcc
CFLAGS = ``
LIBS   = ``
DEBUG  = -Wall -Wextra

OBJECTS = test.o ride.o mapGraph.o list.o
OBJFOLDER = ../../objects

.PHONY: clean

all: main

main: $(OBJECTS)
	$(CC) $(DEBUG) $(OBJFOLDER)/test.o $(OBJFOLDER)/ride.o $(OBJFOLDER)/mapGraph.o $(OBJFOLDER)/list.o $(LIBS) -o $@

test.o: test.c ride.h ../../libs/map/mapGraph.h ../../libs/map/list.h
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $(OBJFOLDER)/$@

ride.o: ride.c ride.h ../../libs/map/mapGraph.h ../../libs/map/list.h
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $(OBJFOLDER)/$@

mapGraph.o: ../../libs/map/mapGraph.c ../../libs/map/mapGraph.h ../../libs/map/list.h
	$(CC) $(DEBUG) -c $< -o $(OBJFOLDER)/$@

list.o: ../../libs/map/list.c ../../libs/map/list.h
	$(CC) $(DEBUG) -c $< -o $(OBJFOLDER)/$@

clean:
	rm -f $(OBJFOLDER)/*.o main

run:
	./main