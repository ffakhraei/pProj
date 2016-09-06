COMPILER=g++
FLAGS=-c -g -Wall

all: rotate90

rotate90: main.o
	$(COMPILER) main.o -o rotate90

main.o: rotate90.cpp
	$(COMPILER) $(FLAGS) rotate90.cpp -o main.o

clean:
	rm -rf *.o rotate90
