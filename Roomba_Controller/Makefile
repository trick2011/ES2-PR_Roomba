#all:
#	g++ main.cpp roombacontroller.cpp Cleaningprograms/autoclean.cpp Cleaningprograms/basicclean.cpp Cleaningprograms/dock.cpp Cleaningprograms/spotclean.cpp Cleaningprograms/walltrace.cpp Pipehandler/check_class.cpp Pipehandler/com_class.cpp Pipehandler/pipe_filler.cpp ../Roomba_Interpreter/interpreter.cpp ../Roomba_UART/uart.cpp ../Roomba_Logger/log.cpp -std=c++14 -lpthread -o bin/controller
debug:
	g++ debug_main.cpp -lpthread roombacontroller.cpp Cleaningprograms/autoclean.cpp Cleaningprograms/basicclean.cpp Cleaningprograms/dock.cpp Cleaningprograms/spotclean.cpp Cleaningprograms/walltrace.cpp Pipehandler/check_class.cpp Pipehandler/com_class.cpp Pipehandler/pipe_filler.cpp ../Roomba_Interpreter/interpreter.cpp ../Roomba_UART/uart.cpp ../Roomba_Logger/log.cpp -std=c++14 -o bin/HeadlessController_debug -g -Wall -Waddress -ggdb -lboost_system
release:
	g++ release_main.cpp roombacontroller.cpp Cleaningprograms/autoclean.cpp Cleaningprograms/basicclean.cpp Cleaningprograms/dock.cpp Cleaningprograms/spotclean.cpp Cleaningprograms/walltrace.cpp Pipehandler/check_class.cpp Pipehandler/com_class.cpp Pipehandler/pipe_filler.cpp ../Roomba_Interpreter/interpreter.cpp ../Roomba_UART/uart.cpp ../Roomba_Logger/log.cpp -std=c++14 -lpthread -o bin/HeadlessController_release  -lboost_system
	#nvwa/debug_new.cpp
install:
	cp bin/HeadlessController_release /usr/bin/headlesscontroller
auto_nothread:
	g++ controllers/auto_nothread.cpp -lpthread Cleaningprograms/autoclean.cpp Cleaningprograms/basicclean.cpp  ../Roomba_Interpreter/interpreter.cpp ../Roomba_UART/uart.cpp ../Roomba_Logger/log.cpp -std=c++14 -o bin/auto_nothread

spot_nothread:
	g++ controllers/spot_nothread.cpp -lpthread Cleaningprograms/spotclean.cpp Cleaningprograms/basicclean.cpp  ../Roomba_Interpreter/interpreter.cpp ../Roomba_UART/uart.cpp ../Roomba_Logger/log.cpp -std=c++14 -o bin/spot_nothread

wall_nothread:
	g++ controllers/wall_nothread.cpp -lpthread Cleaningprograms/walltrace.cpp Cleaningprograms/basicclean.cpp  ../Roomba_Interpreter/interpreter.cpp ../Roomba_UART/uart.cpp ../Roomba_Logger/log.cpp -std=c++14 -o bin/wall_nothread
auto_thread:
	g++ controllers/auto_thread.cpp roombacontroller.cpp Cleaningprograms/autoclean.cpp Cleaningprograms/basicclean.cpp Cleaningprograms/dock.cpp Cleaningprograms/spotclean.cpp Cleaningprograms/walltrace.cpp Pipehandler/check_class.cpp Pipehandler/com_class.cpp Pipehandler/pipe_filler.cpp ../Roomba_Interpreter/interpreter.cpp ../Roomba_UART/uart.cpp ../Roomba_Logger/log.cpp -std=c++14 -lpthread -o bin/auto_thread 
	
spot_thread:
	g++ controllers/spot_thread.cpp roombacontroller.cpp Cleaningprograms/autoclean.cpp Cleaningprograms/basicclean.cpp Cleaningprograms/dock.cpp Cleaningprograms/spotclean.cpp Cleaningprograms/walltrace.cpp Pipehandler/check_class.cpp Pipehandler/com_class.cpp Pipehandler/pipe_filler.cpp ../Roomba_Interpreter/interpreter.cpp ../Roomba_UART/uart.cpp ../Roomba_Logger/log.cpp -std=c++14 -lpthread -o bin/spot_thread 
	
wall_thread:
	g++ controllers/wall_thread.cpp roombacontroller.cpp Cleaningprograms/autoclean.cpp Cleaningprograms/basicclean.cpp Cleaningprograms/dock.cpp Cleaningprograms/spotclean.cpp Cleaningprograms/walltrace.cpp Pipehandler/check_class.cpp Pipehandler/com_class.cpp Pipehandler/pipe_filler.cpp ../Roomba_Interpreter/interpreter.cpp ../Roomba_UART/uart.cpp ../Roomba_Logger/log.cpp -std=c++14 -lpthread -o bin/wall_thread 
