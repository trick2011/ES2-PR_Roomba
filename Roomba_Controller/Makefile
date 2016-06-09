all:
	g++ main.cpp roombacontroller.cpp Cleaningprograms/autoclean.cpp Cleaningprograms/basicclean.cpp Cleaningprograms/dock.cpp Cleaningprograms/spotclean.cpp Cleaningprograms/walltrace.cpp Pipehandler/check_class.cpp Pipehandler/com_class.cpp Pipehandler/pipe_filler.cpp ../Roomba_Interpreter/interpreter.cpp ../Roomba_UART/uart.cpp ../Roomba_Logger/log.cpp -std=c++14 -lpthread -o bin/controller
debug:
	g++ debug_main.cpp roombacontroller.cpp Cleaningprograms/autoclean.cpp Cleaningprograms/basicclean.cpp Cleaningprograms/dock.cpp Cleaningprograms/spotclean.cpp Cleaningprograms/walltrace.cpp Pipehandler/check_class.cpp Pipehandler/com_class.cpp Pipehandler/pipe_filler.cpp ../Roomba_Interpreter/interpreter.cpp ../Roomba_UART/uart.cpp ../Roomba_Logger/log.cpp -std=c++14 -lpthread -o bin/HeadlessController_debug -g -Wall -Waddress -ggdb
release:
	g++ release_main.cpp roombacontroller.cpp Cleaningprograms/autoclean.cpp Cleaningprograms/basicclean.cpp Cleaningprograms/dock.cpp Cleaningprograms/spotclean.cpp Cleaningprograms/walltrace.cpp Pipehandler/check_class.cpp Pipehandler/com_class.cpp Pipehandler/pipe_filler.cpp ../Roomba_Interpreter/interpreter.cpp ../Roomba_UART/uart.cpp ../Roomba_Logger/log.cpp -std=c++14 -lpthread -o bin/HeadlessController_release
install:
	cp bin/HeadlessController_release /usr/bin/headlesscontroller
