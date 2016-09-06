#g++ -g -Wall string_unique_chars.cpp -o string.unique.chars
# variables:
COMPILER=g++

COMPILER_FLAGS=-c -g -Wall

all: string.unique.chars

string.unique.chars: main.o
	$(COMPILER) main.o -o string.unique.chars

main.o: string_unique_chars.cpp
	$(COMPILER) $(COMPILER_FLAGS) string_unique_chars.cpp -o main.o

clean:
	rm -rf *.o string.unique.chars
