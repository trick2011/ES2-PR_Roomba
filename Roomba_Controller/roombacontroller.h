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
public:
        Basicclean * CleaningProgram;
		void SetCleaningProgram(Basicclean*);

		void EnableCleaning();
		void DisableCleaning();

		Roombacontroller(interpreter& interpreterreference):interpreterreference{interpreterreference},CleaningThread{NULL},CleaningProgram{NULL}{OwnPID = syscall(SYS_gettid);}
		~Roombacontroller(){;}

		void LoadCleaningProgram(Basicclean* inputprogram){
			Basicclean* tmpdostuff = inputprogram;
			tmpdostuff->clean();/*stuff*/
		}


//        timerclass timer(*this,0.5); // this is just some code for threading and the pipe
//        thread tTimerThread(timer);
//        tTimerThread.detach();
public:
		//sensors& getSensorsReference(void){return(Sensors);}
};




#endif
