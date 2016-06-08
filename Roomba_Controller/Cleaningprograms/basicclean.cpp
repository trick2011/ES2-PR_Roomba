#include "basicclean.h"
#include <iostream>

bool Basicclean::bEnableCleaning;
pid_t Basicclean::ProcessPID;

Basicclean::Basicclean(interpreter& iref):interpreterreference(iref){
	bEnableCleaning = false;
}
void Basicclean::operator()(){
	if(Basicclean::getEnableCleaning())
		this->clean();
}

Basicclean::~Basicclean(){}

