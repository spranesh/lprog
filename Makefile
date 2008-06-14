#This is only an example Makefile. Make using 'make' in this directory

CC=(g++ -I include)

all: bin/matrix

bin/matrix: obj/matrix.o
	$(CC) obj/matrix.o -o bin/matrix #or something like that

obj/matrix.o:
	$(CC) -c src/matrix.cpp -o obj/matrix.o #compile only and place output in obj/matrix.o


clean:
	rm -rf *~ *.o bin/*
