#include "interpreter.h"

interpreter::interpreter()
{
    uart = new Uart;
}

interpreter::~interpreter()
{
    delete uart;
}


