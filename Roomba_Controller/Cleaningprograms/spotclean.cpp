#include "spotclean.h"
#include "autoclean.h"

Spotclean::~Spotclean(){}

void Spotclean::clean(void)
{
#ifdef __linux
    Basicclean::ProcessPID = syscall(SYS_gettid);
#endif
    while(Basicclean::getEnableCleaning()){
#ifdef VERBOSE
        cout << "Spotclean enabled" << endl;
#endif
        interpreterreference.drives(roomba::speed::SLOW);
        usleep(100);
        interpreterreference.turnRoomba(23);
        interpreterreference.drives(roomba::speed::SLOW);
        usleep(100);


        //failsafe
        if(interpreterreference.getCliffFrontLeft() ||
           interpreterreference.getCliffLeft() ||
           interpreterreference.getCliffFrontRight() ||
           interpreterreference.getCliffRight())
        {
            interpreterreference.drives(roomba::speed::BACKWARDS);
            usleep(250);
            interpreterreference.drives(roomba::speed::STOP);
            interpreterreference.turnRoomba(5);
        }
        if(interpreterreference.getWheelDropLeft()||
           interpreterreference.getWheelDropRight()||
           interpreterreference.getWheelOvercurrents())
        {
            interpreterreference.drives(roomba::speed::STOP);
        }

    }
#ifdef VERBOSE
	cout << "spots out" << endl;
#endif
    interpreterreference.drives(roomba::speed::STOP);
    Basicclean::ProcessPID = 0;
}
