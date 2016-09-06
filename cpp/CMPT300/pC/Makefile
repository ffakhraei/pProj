COMPILER=g++
FLAGS=-c -g -Wall -lpthread

all: producer.consumer

producer.consumer: main.o
	$(COMPILER) -pthread main.o -o producer.consumer

main.o: producer_consumer.cpp
	$(COMPILER) $(FLAGS) producer_consumer.cpp -o main.o

clean:
	rm -rf *.o producer.consumer
