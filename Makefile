CC=gcc
CFLAGS=-std=c99

calendar: main.c utils.c io.c
	$(CC) -o calendar *.c $(CFLAGS)
