#include "autoclean.h"
#include <iostream>
#include "basicclean.h"

void Basicclean::clean(void)
{
    while(Run){
            //roomba turn left
            Run |= interpreterreference.getbBumpLeft();
            Run |= interpreterreference.getbBumpRight();
            Run |= interpreterreference.getCliffLeft();
            Run |= interpreterreference.getCliffFrontLeft();
            Run |= interpreterreference.getCliffFrontRight();
            Run |= interpreterreference.getCliffRight();
            interpreterreference.Bumps.bLeft
        }
        // stop
    }
    interpreterreference.drives(5);
}


