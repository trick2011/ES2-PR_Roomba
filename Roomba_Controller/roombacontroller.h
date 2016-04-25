#include "../Roomba_Simulator/file.h"
#include "../Roomba_FrontEnd/pipehandler.h"

class roombacontroller;
class cleaningprogram;
class wallclean;

class roombacontroller{
private:
        sensors Sensors;
        cleaningprogram * CleaningProgram;
//        timerclass timer(*this,0.5); // this is just some code for threading and the pipe
//        thread tTimerThread(timer);
//        tTimerThread.detach();
public:
        sensors& getSensorsReference(void){return(Sensors);}
};

class cleaningprogram{
private:
    sensors& Sensors;
public:
    cleaningprogram(sensors& Sensors) : Sensors{Sensors}{}
        
};

/** lonneke implementeer deze klasse maar **/
/** wat ik hier heb gedaan is ik heb een klasse genaamt cleaning program aangemaakt waaruit ik wallclean afleidt **/
/** wall clean heeft via een overerfde sensors reference toegang tot de sensoren die de roomba heeft en kan daarmee aktie's bepalen **/

class wallclean : public cleaningprogram{
        
        
};
