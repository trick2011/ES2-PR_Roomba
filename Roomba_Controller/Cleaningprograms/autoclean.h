#ifndef AUTOCLEAN_H
#define AUTOCLEAN_H

#include "basicclean.h"

#include <iostream>

//class AutoCleana;
//class AutoClean : public Basicclean
class AutoClean : public Basicclean
{
public:
	//AutoClean(){}
	AutoClean(interpreter& interpreterreference):Basicclean(interpreterreference){}
	~AutoClean();
	void clean(void);
private:

};

#endif // AUTOCLEAN_H
