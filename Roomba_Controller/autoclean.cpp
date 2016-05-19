#include "autoclean.h"
//#include <iostream>
//#include "basicclean.h"

///class AutoClean;

AutoClean::~AutoClean(){

}

void AutoClean::clean(void)
{
    while(bEnableCleaning == true)
    {
        do
        {
            interpreterreference.drives(roomba::speed::CRUISE);

            Run |= interpreterreference.Bumps.bLeft;
            Run |= interpreterreference.Bumps.bRight;
            Run |= interpreterreference.Cliff.bFrontLeft;
            Run |= interpreterreference.Cliff.bFrontRight;
            Run |= interpreterreference.Cliff.bLeft;
            Run |= interpreterreference.Cliff.bRight;
        }
        while(Run == false || bEnableCleaning == true);

        interpreterreference.turnRoomba(90);
        interpreterreference.drives(roomba::speed::SLOW);
        sleep(2);
        interpreterreference.turnRoomba(90);
     }


}


