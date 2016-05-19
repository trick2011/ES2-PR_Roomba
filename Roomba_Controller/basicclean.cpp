#include "basicclean.h"
#include <iostream>

Basicclean::Basicclean(interpreter& iref):interpreterreference(iref)
{

}

void Basicclean::SetEnableCleaning(void)
{
    bEnableCleaning = true;
}

void Basicclean::SetDisableCleaning(void)
{
    bEnableCleaning = false;
}

Basicclean::~Basicclean()
{
}

