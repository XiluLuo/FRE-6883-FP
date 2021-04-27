CC=g++
CFLAGS=-Wall -g -std=c++11 -O3

all: main

main: main.o Matrix.o Stock.o Util.o YahooScrape.o
	$(CC) $(CFLAGS) $^ -lcurl -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

Matrix.o: Matrix.cpp Matrix.hpp
	$(CC) $(CFLAGS) -c $< -o $@

Stock.o: Stock.cpp Stock.hpp
	$(CC) $(CFLAGS) -c $< -o $@

Util.o: Util.cpp Util.hpp
	$(CC) $(CFLAGS) -c $< -o $@

YahooScrape.o: YahooScrape.cpp YahooScrape.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o main *.dSYM
