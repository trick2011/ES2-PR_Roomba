prog: main.o opcodes.o failsave.o
	g++ -Wall -o prog main.o opcodes.o failsave.o

main.o: main.cpp opcodes.h failsave.h
	g++ -Wall -c main.cpp

opcodes.o: opcodes.cpp opcodes.h
	g++ -Wall -c opcodes.cpp

failsave.o: failsave.cpp failsave.h
	g++ -Wall -c failsave.cpp
