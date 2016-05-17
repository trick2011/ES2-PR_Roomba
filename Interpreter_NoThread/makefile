#makefile for the Roomba Interpreter

prog.out: main.o interpreter.o uart.o
	g++ -Wall -o prog.out main.o interpreter.o uart.o

main.o: main.cpp opcodes.h 
	g++ -Wall -c main.cpp -std=c++11

interpreter.o: interpreter.cpp interpreter.h opcodes.h
	g++ -Wall -c interpreter.cpp -std=c++11

uart.o: ./UART/uart.cpp ./UART/uart.h
	g++ -Wall -c ./UART/uart.cpp -std=c++11
