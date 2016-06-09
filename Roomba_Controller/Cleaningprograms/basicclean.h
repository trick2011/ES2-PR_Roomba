#ifndef BASICCLEAN_H
#define BASICCLEAN_H

#include <unistd.h>
#ifdef __linux
#include <sys/syscall.h>
#include <sys/types.h>
#endif

#include <thread>

#include "../../Roomba_Interpreter/interpreter.h"
//#include "../roombacontroller.h"
//namespace cln{
	//extern bool bEnableCleaning;// = false;
//}


class Basicclean
{
private:
protected:
	bool Run = false;
	static bool bEnableCleaning;
	static pid_t ProcessPID;

	int ID;
	interpreter& interpreterreference;
public:
	Basicclean(interpreter& iref);
    virtual ~Basicclean();

	static pid_t getProcessPID(void){return(ProcessPID);}
	static bool getEnableCleaning(void){return(Basicclean::bEnableCleaning);}
	static void EnableCleaning(void){roomba::runThread=Basicclean::bEnableCleaning=true;}
	static void DisableCleaning(void){roomba::runThread=Basicclean::bEnableCleaning=false;}

	void operator()();
	virtual void clean(void) = 0;
};

#endif // BASICCLEAN_H



