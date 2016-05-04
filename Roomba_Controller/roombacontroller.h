#include "../Roomba_Simulator/file.h"
#include "../Roomba_FrontEnd/pipehandler.h"

class Roombacontroller;
class Cleaningprogram;
class Wallclean;

class Roombacontroller{
private:
        sensors Sensors;
		Cleaningprogram * CleaningProgram;
//        timerclass timer(*this,0.5); // this is just some code for threading and the pipe
//        thread tTimerThread(timer);
//        tTimerThread.detach();
public:
        sensors& getSensorsReference(void){return(Sensors);}
};

class Cleaningprogram{
protected:
	sensors& Sensors;
	bool Run;
public:
	Cleaningprogram(sensors& Sensors) : Sensors{Sensors}, Run(true){}

	virtual void clean(void) = 0;
        
	void EnableCleaning(void){Run = true;}
	void DisableCleaning(void){Run = false;}

};

/** lonneke implementeer deze klasse maar **/
/** wat ik hier heb gedaan is ik heb een klasse genaamt cleaning program aangemaakt waaruit ik wallclean afleidt **/
/** wall clean heeft via een overerfde sensors reference toegang tot de sensoren die de roomba heeft en kan daarmee aktie's bepalen **/

class Wallclean : public Cleaningprogram{
        
        
};

class Spotclean : public Cleaningprogram{
public:
	Spotclean(sensors& Sensors) : Cleaningprogram(Sensors){;}

	void clean(void);

};
