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

	static bool getEnableCleaning(void){return(Basicclean::bEnableCleaning);}
	static void EnableCleaning(void){Basicclean::bEnableCleaning=true;}
	static void DisableCleaning(void){Basicclean::bEnableCleaning=false;}

	void operator()();
	virtual void clean(void) = 0;
};

#endif // BASICCLEAN_H



