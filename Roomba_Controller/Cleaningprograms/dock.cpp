#include "dock.h"


Dock::~Dock()
{

}

void Dock::clean(void)
{
	Basicclean::ProcessPID = syscall(SYS_gettid);
    switch(iState)
    {
    case 0: //no signal
        break;
    case 1: //red signal
        break;
    case 2: //green signal
        break;
    case 3: //both
        break;
    case 4: //close
        break;
    }
	Basicclean::ProcessPID = 0;
}

