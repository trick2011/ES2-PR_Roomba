#ifndef BASICCLEAN_H
#define BASICCLEAN_H

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

	int ID;
	interpreter& interpreterreference;
public:

	Basicclean(interpreter& iref);
    virtual ~Basicclean();

	bool getEnableCleaning(void){return(bEnableCleaning);}
	void EnableCleaning(void){bEnableCleaning=true;}
	void DisableCleaning(void){bEnableCleaning=false;}

	virtual void clean(void) = 0;
};

#endif // BASICCLEAN_H



