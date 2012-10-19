CC=gcc
CFLAGS=-I.
APP=Wator

build: Fish.o
	$(CC) -o $(APP) Fish.o $(CFLAGS)

clean:
	rm *.o
	rm $(APP)