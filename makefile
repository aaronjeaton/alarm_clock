all: main.o


main.o : main.cc
	g++ -std=c++0x  main.cc -o clock

