#include "walltrace.h"
#include "autoclean.h"

Walltrace::~Walltrace(){

}

void Walltrace::clean(void)
{
#ifdef __linux
	Basicclean::ProcessPID = syscall(SYS_gettid);
#endif
    while(getEnableCleaning()==true)
    {
        interpreterreference.drives(roomba::speed::SLOW);

        Run |= interpreterreference.Bumps.bLeft;
        Run |= interpreterreference.Bumps.bRight;
        Run |= interpreterreference.Cliff.bFrontLeft;
        Run |= interpreterreference.Cliff.bFrontRight;
        Run |= interpreterreference.Cliff.bLeft;
        Run |= interpreterreference.Cliff.bRight;

        interpreterreference.brushes(roomba::brush::MAINBRUSH);


        while(Run == false && getEnableCleaning()== true);
        {
           interpreterreference.turnRoomba(5);
           interpreterreference.drives(roomba::speed::SLOW);
           interpreterreference.brushes(roomba::brush::BOTH);

        }
    }
	Basicclean::ProcessPID = 0;
}
