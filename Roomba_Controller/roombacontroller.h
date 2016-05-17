#include "../Roomba_Simulator/file.h"
//#include "../Roomba_FrontEnd/pipehandler.h"
#include "../Interpreter_NoThread/interpreter.h"

#include "basicclean.h"
#include "spotclean.h"

//class Cleaningprogram;
//class Wallclean;

class Roombacontroller{
private:
    interpreter& interpreterreference; //reference naar interpreter
public:
        Basicclean * CleaningProgram;
		Roombacontroller(interpreter& interpreterreference):interpreterreference{interpreterreference}{;}
		~Roombacontroller(){;}

//        timerclass timer(*this,0.5); // this is just some code for threading and the pipe
//        thread tTimerThread(timer);
//        tTimerThread.detach();
public:
		//sensors& getSensorsReference(void){return(Sensors);}
};




