all: build run

build:
	g++ *.cpp -o main -Wall -Wextra -l gpiod 

run:
	./main
