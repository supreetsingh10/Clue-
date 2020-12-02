CC=gcc
CFLAGS=-c -Wall
all: clue

clue: adventure.o room.o character.o items.o
	$(CC) adventure.o room.o character.o items.o -o CLUE

main.o: adventure.c
	$(CC) -c adventure.c 

room.o: room.c 
	$(CC) $(CFLAGS) -c room.c

character.o: character.c 
	$(CC) $(CFLAGS) -c character.c

items.o: items.c
	$(CC) $(CFLAGS) -c items.c
