COMPILER=g++
FLAGS=-c -g -Wall

all: rip.all.in.one

rip.all.in.one: main.o router.o
	$(COMPILER) main.o router.o -o rip.all.in.one

main.o: rip_all_in_one.cpp
	$(COMPILER) $(FLAGS) rip_all_in_one.cpp -o main.o

router.o: router.cpp
	$(COMPILER) $(FLAGS) router.cpp -o router.o

clean:
	rm -rf *.o rip.all.in.one; clear
