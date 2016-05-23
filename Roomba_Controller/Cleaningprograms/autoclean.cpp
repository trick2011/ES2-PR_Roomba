#include "autoclean.h"

AutoClean::~AutoClean(){}

void AutoClean::clean(void)
{
	while(getEnableCleaning() == true)
	{
		do
		{
			interpreterreference.drives(roomba::speed::CRUISE);
            interpreterreference.brushes(roomba::brush::MAINBRUSH);

			Run |= interpreterreference.Bumps.bLeft;
			Run |= interpreterreference.Bumps.bRight;
			Run |= interpreterreference.Cliff.bFrontLeft;
			Run |= interpreterreference.Cliff.bFrontRight;
			Run |= interpreterreference.Cliff.bLeft;
			Run |= interpreterreference.Cliff.bRight;
		}
		while(Run == false && getEnableCleaning() == true);

        switch(state)
        {
        case 0:
            interpreterreference.turnRoomba(90);
            interpreterreference.drives(roomba::speed::SLOW);
            sleep(2);
            interpreterreference.turnRoomba(90);
            interpreterreference.brushes(roomba::brush::BOTH);
            state++;
            break;
        case 1:
            interpreterreference.turnRoomba(270);
            interpreterreference.drives(roomba::speed::SLOW);
            sleep(2);
            interpreterreference.turnRoomba(270);
            interpreterreference.brushes(roomba::brush::BOTH);
            state--;
            break;
        default:
            state = 0;
        }
	 }
}
