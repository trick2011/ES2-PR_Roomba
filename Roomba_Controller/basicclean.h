#ifndef BASICCLEAN_H
#define BASICCLEAN_H

#include "../Interpreter_NoThread/interpreter.h"

class Basicclean
{
private:
    bool bEnableCleaning = false;
    bool Run = false;
protected:
	int ID;
	interpreter& interpreterreference;
public:
    Basicclean(interpreter& iref);
    virtual ~Basicclean();

	virtual void clean(void) = 0;
};

//class Cleaningprogram{
//protected:
//	//sensors& Sensors;
//	bool Run;
//public:
//	Cleaningprogram(sensors& Sensors) : Sensors{Sensors}, Run(true){}

//	virtual void clean(void) = 0;

//	void EnableCleaning(void){Run = true;}
//	void DisableCleaning(void){Run = false;}

//};

#endif // BASICCLEAN_H



