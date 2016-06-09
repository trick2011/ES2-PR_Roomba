#all:
#	g++ main.cpp roombacontroller.cpp Cleaningprograms/autoclean.cpp Cleaningprograms/basicclean.cpp Cleaningprograms/dock.cpp Cleaningprograms/spotclean.cpp Cleaningprograms/walltrace.cpp Pipehandler/check_class.cpp Pipehandler/com_class.cpp Pipehandler/pipe_filler.cpp ../Roomba_Interpreter/interpreter.cpp ../Roomba_UART/uart.cpp ../Roomba_Logger/log.cpp -std=c++14 -lpthread -o bin/controller
debug:
	g++ debug_main.cpp -lpthread roombacontroller.cpp Cleaningprograms/autoclean.cpp Cleaningprograms/basicclean.cpp Cleaningprograms/dock.cpp Cleaningprograms/spotclean.cpp Cleaningprograms/walltrace.cpp Pipehandler/check_class.cpp Pipehandler/com_class.cpp Pipehandler/pipe_filler.cpp ../Roomba_Interpreter/interpreter.cpp ../Roomba_UART/uart.cpp ../Roomba_Logger/log.cpp -std=c++14 -o bin/HeadlessController_debug -g -Wall -Waddress -ggdb nvwa/debug_new.cpp
release:
	g++ release_main.cpp roombacontroller.cpp Cleaningprograms/autoclean.cpp Cleaningprograms/basicclean.cpp Cleaningprograms/dock.cpp Cleaningprograms/spotclean.cpp Cleaningprograms/walltrace.cpp Pipehandler/check_class.cpp Pipehandler/com_class.cpp Pipehandler/pipe_filler.cpp ../Roomba_Interpreter/interpreter.cpp ../Roomba_UART/uart.cpp ../Roomba_Logger/log.cpp -std=c++14 -lpthread -o bin/HeadlessController_release nvwa/debug_new.cpp
install:
	cp bin/HeadlessController_release /usr/bin/headlesscontroller
# 
# link:
# 	g++ -o bin/HeadlessController_release -lpthread -std=c++14 obj/* Cleaningprograms/*.h
# 
# buildobj: autoclean.o basicclean.o dock.o spotclean.o walltrace.o pipe_filler.o com_class.o check_class.o log.o uart.o interpreter.o
# 
# autoclean.o: Cleaningprograms/autoclean.cpp Cleaningprograms/autoclean.h
# 	g++ -o obj/autoclean.o -std=c++14 -c Cleaningprograms/autoclean.cpp
# 
# basicclean.o: Cleaningprograms/basicclean.cpp Cleaningprograms/basicclean.h
# 	g++ -o obj/basicclean.o -std=c++14 -c Cleaningprograms/basicclean.cpp
# 
# dock.o: Cleaningprograms/dock.cpp Cleaningprograms/dock.h
# 	g++ -o obj/dock.o -std=c++14 -c Cleaningprograms/dock.cpp
# 
# spotclean.o: Cleaningprograms/spotclean.cpp Cleaningprograms/spotclean.h
# 	g++ -o obj/spotclean.o -std=c++14 -c Cleaningprograms/spotclean.cpp
# 
# walltrace.o: Cleaningprograms/walltrace.cpp Cleaningprograms/walltrace.h
# 	g++ -o obj/walltrace.o -std=c++14 -c Pipehandler/walltrace.cpp
# 
# pipe_filler.o: Pipehandler/pipe_filler.cpp Pipehandler/pipe_filler.h Pipehandler/macros.h
# 	g++ -o obj/pipe_filler.o -std=c++14 -c Pipehandler/pipe_filler.cpp
# 
# com_class.o: Pipehandler/com_class.cpp Pipehandler/com_class.h Pipehandler/macros.h
# 	g++ -o obj/com_class.o -std=c++14 -c Pipehandler/com_class.cpp
# 
# check_class.o: Pipehandler/check_class.cpp Pipehandler/check_class.h Pipehandler/macros.h
# 	g++ -o obj/check_class.o -std=c++14 -c Pipehandler/check_class.cpp
# 
# log.o: ../Roomba_Logger/log.cpp ../Roomba_Logger/log.h
# 	g++ -o obj/log.o -std=c++14 -c ../Roomba_Logger/log.cpp
# 
# uart.o: ../Roomba_UART/uart.cpp ../Roomba_UART/uart.h
# 	g++ -o obj/uart.o -std=c++14 -c ../Roomba_UART/uart.cpp
# 
# interpreter.o: ../Roomba_Interpreter/interpreter.cpp ../Roomba_Interpreter/interpreter.h ../Roomba_Interpreter/opcodes.h	
# 	g++ -o obj/interpreter.o -std=c++14 -c ../Roomba_Interpreter/interpreter.cpp
