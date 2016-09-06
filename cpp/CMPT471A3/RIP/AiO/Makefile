COMPILER=g++
FLAGS=-c -g -Wall

all: rip.all.in.one

rip.all.in.one: main.o
	$(COMPILER) main.o -o rip.all.in.one

main.o: rip_all_in_one.cpp
	$(COMPILER) $(FLAGS) rip_all_in_one.cpp -o main.o

clean:
	rm -rf *.o rip.all.in.one; clear
