#include "dock.h"


Dock::~Dock()
{

}

void Dock::clean(void)
{
#ifdef __linux
	Basicclean::ProcessPID = syscall(SYS_gettid);
#endif
    switch(iState)
    {
    case 0: //no signal
       interpreterreference.sInfraRed.bClose



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

bool bLeft;
bool bRight;
bool bClose;
