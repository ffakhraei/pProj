COMPILER=g++
FLAGS=-c -g -Wall

all: replace.spaces

replace.spaces: main.o
	$(COMPILER) main.o -o replace.spaces

main.o: replace_spaces.cpp
	$(COMPILER) $(FLAGS) replace_spaces.cpp -o main.o

clean:
	rm -rf *.o replace.spaces
