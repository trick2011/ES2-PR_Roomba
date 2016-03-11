#makefile for the Roomba Interpreter

prog: main.o opcodes.o failsave.o
	g++ -Wall -o prog main.o opcodes.o failsave.o -std=c++11

main.o: main.cpp opcodes.h failsave.h
	g++ -Wall -c main.cpp -std=c++11

opcodes.o: opcodes.cpp opcodes.h
	g++ -Wall -c opcodes.cpp -std=c++11

failsave.o: failsave.cpp failsave.h
	g++ -Wall -c failsave.cpp -std=c++11
