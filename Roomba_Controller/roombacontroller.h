#include "../Roomba_Simulator/file.h"
//#include "../Roomba_FrontEnd/pipehandler.h"
#include "../Interpreter_NoThread/interpreter.h"

#include "basicclean.h"
#include "spotclean.h"

class Roombacontroller;
//class Cleaningprogram;
//class Wallclean;

class Roombacontroller{
private:
//        sensors Sensors;

/**< hier moet een reference naar de interpreter komen **/
	interpreter& interpreterreference;
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




