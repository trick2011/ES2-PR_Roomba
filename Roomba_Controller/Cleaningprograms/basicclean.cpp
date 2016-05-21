#include "basicclean.h"
#include <iostream>

bool Basicclean::bEnableCleaning;

Basicclean::Basicclean(interpreter& iref):interpreterreference(iref){
	bEnableCleaning = false;
}

Basicclean::~Basicclean(){}

