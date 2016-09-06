COMPILER=g++
FLAGS=-c -g -Wall

all: server

server: main.o
	$(COMPILER) main.o -o server

main.o: server.cpp
	$(COMPILER) $(FLAGS) server.cpp -o main.o

clean:
	rm -rf *.o server; clear
