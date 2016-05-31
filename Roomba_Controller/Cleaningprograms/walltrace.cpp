#include "walltrace.h"
#include "autoclean.h"

Walltrace::~Walltrace(){

}

void Walltrace::clean(void)
{
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
           interpreterreference.turnRoomba(23);
           interpreterreference.drives(roomba::speed::SLOW);
           interpreterreference.brushes(roomba::brush::BOTH);

        }
    }
}
