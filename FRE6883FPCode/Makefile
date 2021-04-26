CC=g++
CFLAGS=-Wall -g -std=c++11 -O3

all: main

main: main.o Matrix.o Stock.o Util.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

Matrix.o: Matrix.cpp Matrix.h
	$(CC) $(CFLAGS) -c $< -o $@

Stock.o: Stock.cpp Stock.h
	$(CC) $(CFLAGS) -c $< -o $@

Util.o: Util.cpp Util.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o main *.dSYM
