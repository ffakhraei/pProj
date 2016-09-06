COMPILER=g++
FLAGS=-c -g -Wall

all: compress

compress: main.o
	$(COMPILER) main.o -o compress

main.o: compress.cpp
	$(COMPILER) $(FLAGS) compress.cpp -o main.o

clean:
	rm -rf *.0 compress
