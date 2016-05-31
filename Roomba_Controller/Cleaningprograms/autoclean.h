#ifndef AUTOCLEAN_H
#define AUTOCLEAN_H
#include "basicclean.h"
#include <iostream>

class AutoClean : public Basicclean
{
public:
	AutoClean(interpreter& interpreterreference):Basicclean(interpreterreference){}
	~AutoClean();
	void clean(void);
private:
    int iState = 0;

};

#endif // AUTOCLEAN_H
