CC = g++
CFLAGS = -W -Wall -ansi -pedantic --std=c++11

.PHONY : clean martist

martist : libmartist.a martist.o

martist.o : martist.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

libmartist.a : parser.o expression.o
	ar rcU $@ $^; rm -rf $^

parser.o : parser.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

expression.o: expression.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean : 
	rm -rf *.o
