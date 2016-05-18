#include "autoclean.h"
#include <iostream>
#include "basicclean.h"

void Basicclean::clean(void)
{
    do
    {
      interpreterreference.drives(CRUISE);

      Run |= interpreterreference.Bumps.bLeft;
      Run |= interpreterreference.Bumps.bRight;
      Run |= interpreterreference.Cliff.bFrontLeft;
      Run |= interpreterreference.Cliff.bFrontRight;
      Run |= interpreterreference.Cliff.bLeft;
      Run |= interpreterreference.Cliff.bRight;
    }
    while(Run = 0);

    interpreterreference.turnRoomba(90);
    interpreterreference.drives(SLOW);
    interpreterreference.turnRoomba(90);


}


