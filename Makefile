
# set all Warnings and switch on debug
CC=g++ -Wall -Iinclude -g

all: matrixLibs

matrixLibs: src/matrix.cpp include/matrix.h include/exceptions.h
	$(CC) -c src/matrix.cpp -o obj/matrix.o
	$(CC) obj/matrix.o -o bin/matrixLib

clean:
	rm -rf *~ *.o bin/*
