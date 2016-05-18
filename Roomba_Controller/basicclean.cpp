#include "basicclean.h"
#include <iostream>

Basicclean::Basicclean(interpreter& iref):interpreterreference(iref)
{

}

Basicclean::SetEnableCleaning()
{
    bEnableCleaning = true;
}

Basicclean::SetDisableCleaning()
{
    bEnableCleaning = false;
}

Basicclean::~Basicclean()
{
}

