#ifndef BASICCLEAN_H
#define BASICCLEAN_H

#include "../Interpreter_NoThread/interpreter.h"

class Basicclean
{
private:
protected:
	bool Run = false;
	bool bEnableCleaning = false;
	int ID;
	interpreter& interpreterreference;
public:
    Basicclean(interpreter& iref);
    virtual ~Basicclean();
	void SetEnableCleaning(void);
	void SetDisableCleaning(void);
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



