CC=gcc

calendar: main.c utils.c io.c
	$(CC) -Wall -o calendar *.c
