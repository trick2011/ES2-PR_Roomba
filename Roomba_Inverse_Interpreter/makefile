#makefile for the Roomba Interpreter

prog.out: main.o opcodes.o failsave.o uart.o
	g++ -Wall -o prog.out main.o opcodes.o failsave.o uart.o

main.o: main.cpp opcodes.h failsave.h
	g++ -Wall -c main.cpp -std=c++11

opcodes.o: opcodes.cpp opcodes.h ./UART/uart.h
	g++ -Wall -c opcodes.cpp -std=c++11

failsave.o: failsave.cpp failsave.h opcodes.h ./UART/uart.h
	g++ -Wall -c failsave.cpp -std=c++11

uart.o: ./UART/uart.cpp ./UART/uart.h
	g++ -Wall -c ./UART/uart.cpp -std=c++11
