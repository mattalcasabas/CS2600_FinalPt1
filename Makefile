CC=gcc

all: lsh

lsh: src/main.c
	$(CC) src/main.c -o lsh

clean: 
	rm -r lsh