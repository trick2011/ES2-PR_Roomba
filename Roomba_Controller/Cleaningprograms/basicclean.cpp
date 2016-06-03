#include "basicclean.h"
#include <iostream>

bool Basicclean::bEnableCleaning;
pid_t Basicclean::ProcessPID;

Basicclean::Basicclean(interpreter& iref):interpreterreference(iref){
	bEnableCleaning = false;
}
void Basicclean::operator()(){
	this->clean();
}

Basicclean::~Basicclean(){}

