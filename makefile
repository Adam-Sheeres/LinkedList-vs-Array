#name: Adam Sheeres-Paulicpulle
#student ID: 1035659
#email: asheeres@uoguelph.ca
CFLAGS = -ansi -Wall -pedantic
CC = gcc
ADD = git add

all: main.o ds_memory.o ds_list.o
	clear
	$(CC) $(CFLAGS) -c main.c -o main.o
	$(CC) $(CFLAGS) -c ds_memory.c -o ds_memory.o
	$(CC) $(CFLAGS) -c ds_list.c -o ds_list.o
	$(CC) $(CFLAGS) -c ds_array.c -o ds_array.o

test: testArray.o ds_memory.o ds_list.o
	clear
	$(CC) $(CFLAGS)	-c testArray.c -o testArray.o
	$(CC) $(CFLAGS) -c ds_memory.c -o ds_memory.o
	$(CC) $(CFLAGS) -c ds_list.c -o ds_list.o
	$(CC) $(CFLAGS) testArray.o ds_memory.o ds_list.o -o runTest

run : a1
	clear
	./a1
clean :
	rm *.o
	rm a1
	rm *.bin
	clear
add :
	$(ADD) *.c
	$(ADD) *.h
	$(ADD) makefile
