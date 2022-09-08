all: build run

build:
	g++ *.cpp -o main -Wall -l gpiod

run:
	./main
