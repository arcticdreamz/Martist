CC = g++
CFLAGS = -W -Wall -ansi -pedantic --std=c++11

.PHONY : clean all

all: martist

martist: martist.o parser.o expression.o
	ar rc libmartist.a martist.o parser.o expression.o

martist.o : martist.cpp 
	$(CC) -o $@ -c $< $(CFLAGS)

parser.o : parser.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

expression.o: expression.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf martist
