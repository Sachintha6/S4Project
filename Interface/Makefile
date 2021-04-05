
TARGET= Interface
CC=gcc
DEBUG=-g
WARN=-Wall
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`
PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS=    main.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
    
main.o: main.c
	$(CC) -c $(CCFLAGS) main.c $(GTKLIB) -o main.o
    
clean:
	rm -f *.o $(TARGET)

