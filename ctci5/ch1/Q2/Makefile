# Variables
COMPILER=g++
COMPILER_FLAGS=-c -g -Wall
OBJECT_OUTPUT_FLAGS=-o main.o
OUTPUT_FLAGS=-o reverse.string

all: reverse.string

reverse.string: main.o
	$(COMPILER) main.o $(OUTPUT_FLAGS)

main.o: reverse_string.cpp
	$(COMPILER) $(COMPILER_FLAGS) reverse_string.cpp $(OBJECT_OUTPUT_FLAGS)

clean:
	rm -rf *.o reverse.string
