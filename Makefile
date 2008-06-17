# This is the Makefile for the lprog project
# ToDo : Add command line support
# :P

SHELL=/bin/sh

# set all Warnings and switch on debug

C++ = g++
C++-FLAGS = -Wall -g -c
LINKER = g++
LINKER-FLAGS = -o

# set VPATH so that we can refer to dependencies
# in a more natural manner
VPATH=src:include:obj


all: makeReqdDirs md

#md = matrix driver
md: md.cpp matrix.cpp matrix.h exceptions.h 
	g++ -I include -Wall -g src/md.cpp -o bin/md

makeReqdDirs:
# This is to be replaced by an if clause later in time
# to ensure compatibility across various *NIX machines
# mkdir -p creates directory if not present
# and throws no error in case it is present
	mkdir -p bin
	mkdir -p data
	mkdir -p obj

clean:
	rm -rf *~ *.o 
	rm -rf bin
	rm -rf obj
	rmdir --ignore-fail-on-non-empty data
