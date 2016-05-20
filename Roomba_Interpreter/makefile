#makefile for the Roomba Interpreter

prog.out: main.o interpreter.o uart.o
	g++ -Wall -o prog.out main.o interpreter.o uart.o

main.o: main.cpp opcodes.h 
	g++ -Wall -c main.cpp -std=c++11

interpreter.o: interpreter.cpp interpreter.h opcodes.h
	g++ -Wall -c interpreter.cpp -std=c++11

uart.o: ../Roomba_UART/uart.cpp ../Roomba_UART/uart.h
	g++ -Wall -c ../Roomba_UART/uart.cpp -std=c++11
