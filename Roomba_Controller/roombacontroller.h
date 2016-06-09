#ifndef ROOMBACONTROLLER_H
#define ROOMBACONTROLLER_H


//C++ includes
#include <thread>
#include <typeinfo>

#include "../Roomba_Interpreter/interpreter.h"

// cleaning programs
#include "Cleaningprograms/autoclean.h"
#include "Cleaningprograms/basicclean.h"
//#include "Cleaningprograms/cell.h"
#include "Cleaningprograms/dock.h"
#include "Cleaningprograms/spotclean.h"
#include "Cleaningprograms/walltrace.h"



//class Cleaningprogram;
//class Wallclean;
class Roombacontroller;

class Roombacontroller{
private:
    interpreter& interpreterreference; //reference naar interpreter

	bool bEnableCleaning = false;
	thread* CleaningThread;

	pid_t OwnPID;
	Basicclean * CleaningProgram;
public:
		void SetCleaningProgram(Basicclean*);

		void EnableCleaning();
		void DisableCleaning();
#ifdef __linux
		Roombacontroller(interpreter& interpreterreference):interpreterreference{interpreterreference},CleaningThread{NULL},CleaningProgram{NULL}{OwnPID = syscall(SYS_gettid);CleaningThread=NULL;}
#else
		Roombacontroller(interpreter& interpreterreference):interpreterreference{interpreterreference},CleaningThread{NULL},CleaningProgram{NULL}{OwnPID = 0;CleaningThread=NULL;}
#endif
		~Roombacontroller();



//        timerclass timer(*this,0.5); // this is just some code for threading and the pipe
//        thread tTimerThread(timer);
//        tTimerThread.detach();
		//sensors& getSensorsReference(void){return(Sensors);}
};




#endif
