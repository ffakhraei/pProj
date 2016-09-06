COMPILER=g++
FLAGS=-c -g -Wall

all: client

client: main.o
	$(COMPILER) main.o -o client

main.o: client.cpp
	$(COMPILER) $(FLAGS) client.cpp -o main.o

clean:
	rm -rf *.o client; clear
