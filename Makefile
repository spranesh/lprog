# This is the Makefile for the lprog project
# ToDo : Add command line support
# :P

SHELL=/bin/sh

# set all Warnings and switch on debug
CC=g++ -Wall -I include -g

# set VPATH so that we can refer to dependencies
# in a more natural manner
VPATH=src:include:obj


all: makeReqdDirs matrixLibs md

#md = matrix driver
md: md.cpp matrix.cpp matrix.h exceptions.h matrix.o
	$(CC) -c src/md.cpp -o obj/md.o
	$(CC) obj/md.o obj/matrix.o -o bin/md


makeReqdDirs:
# This is to be replaced by an if clause later in time
# to ensure compatibility across various *NIX machines
# mkdir -p creates directory if not present
# and throws no error in case it is present
	mkdir -p bin
	mkdir -p data
	mkdir -p obj


matrixLibs: matrix.cpp matrix.h exceptions.h
	$(CC) -c src/matrix.cpp -o obj/matrix.o


clean:
	rm -rf *~ *.o 
	rm -rf bin
	rm -rf obj
	rmdir --ignore-fail-on-non-empty data
