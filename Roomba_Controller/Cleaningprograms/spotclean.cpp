#include "spotclean.h"
#include "autoclean.h"

Spotclean::~Spotclean(){}

void Spotclean::clean(void)
{
#ifdef __linux
	Basicclean::ProcessPID = syscall(SYS_gettid);
#endif
    while(getEnableCleaning()==true)
    {
        interpreterreference.turnRoomba(1);

        /*Run |= interpreterreference.Bumps.bLeft;
        Run |= interpreterreference.Bumps.bRight;
        Run |= interpreterreference.Cliff.bFrontLeft;
        Run |= interpreterreference.Cliff.bFrontRight;
        Run |= interpreterreference.Cliff.bLeft;
        Run |= interpreterreference.Cliff.bRight;*/ //deze alleen gebruiken als interpreter een thread is.

        Run = interpreterreference.getBumpRight()       | interpreterreference.getBumpLeft()
            | interpreterreference.getCliffLeft()       | interpreterreference.getCliffFrontLeft()
            | interpreterreference.getCliffFrontRight() | interpreterreference.getCliffRight();


        while(Run == false && getEnableCleaning()== true);
        {
           interpreterreference.drives(roomba::speed::BACKWARDS);
           sleep(1);
           interpreterreference.turnRoomba(23);
        }
    }
	Basicclean::ProcessPID = 0;
}
