#include "spotclean.h"
#include "autoclean.h"

Spotclean::~Spotclean(){}

void Spotclean::clean(void)
{
    while(getEnableCleaning()==true)
    {
        interpreterreference.turnRoomba(1);

        Run |= interpreterreference.Bumps.bLeft;
        Run |= interpreterreference.Bumps.bRight;
        Run |= interpreterreference.Cliff.bFrontLeft;
        Run |= interpreterreference.Cliff.bFrontRight;
        Run |= interpreterreference.Cliff.bLeft;
        Run |= interpreterreference.Cliff.bRight;

        interpreterreference.brushes(roomba::brush::MAINBRUSH);


        while(Run == false && getEnableCleaning()== true);
        {
           interpreterreference.drives(roomba::speed::BACKWARDS);
           sleep(1);
           interpreterreference.turnRoomba(23);
           interpreterreference.brushes(roomba::brush::BOTH);

        }
    }
}
