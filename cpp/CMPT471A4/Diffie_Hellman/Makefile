COMPILER=g++
FLAGS=-c -g -Wall

all: dh

dh: main.o
	$(COMPILER) main.o -o dh

main.o: dh.cpp
	$(COMPILER) $(FLAGS) dh.cpp -o main.o

clean:
	rm -rf *.o dh; clear
	
