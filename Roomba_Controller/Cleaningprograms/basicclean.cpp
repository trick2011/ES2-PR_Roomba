#include "basicclean.h"
#include <iostream>

bool Basicclean::bEnableCleaning;

Basicclean::Basicclean(interpreter& iref):interpreterreference(iref){
	bEnableCleaning = false;
}
void Basicclean::operator()(){
	this->clean();
}

Basicclean::~Basicclean(){}

