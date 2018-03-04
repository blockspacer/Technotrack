CC     = g++
CFLAGS = -c -Wall

all: sstack

sstack: stack.h stack.cpp main.cpp
	$(CC) main.cpp -o stack

stack: stack.o main.o
	$(CC) stack.o main.o -o stack

%.o: %.c stack.h
	$(CC) $(CFLAGS) $<

clean:
	rm *.o stack
