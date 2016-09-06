COMPILER=g++
COMPILER_FLAGS=-c -g -Wall

all: is.permutation

is.permutation: main.o
	$(COMPILER) main.o -o is.permutation

main.o: is_permutation.cpp
	$(COMPILER) $(COMPILER_FLAGS) is_permutation.cpp -o main.o

clean:
	rm -rf *.o is.permutation
