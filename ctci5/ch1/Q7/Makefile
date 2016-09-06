COMPILER=g++
FLAGS=-c -g -Wall

all: set.to.zero

set.to.zero: main.o
	$(COMPILER) main.o -o set.to.zero

main.o: set_to_zero.cpp
	$(COMPILER) $(FLAGS) set_to_zero.cpp -o main.o

clean:
	rm -rf *.o set.to.zero
