COMPILER=g++
FLAGS=-c -g -Wall

all: rip.update.table

rip.update.table: main.o
	$(COMPILER) main.o -o rip.update.table

main.o: rip_update_table.cpp
	$(COMPILER) $(FLAGS) rip_update_table.cpp -o main.o

clean:
	rm -rf *.o rip.update.table; clear
