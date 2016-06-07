#include "walltrace.h"
#include "autoclean.h"

Walltrace::~Walltrace(){

}

namespace actionlist {
static const int BumpLeft  = 0;
static const int BumpRight = 1;
}

void Walltrace::clean(void)
{
#ifdef __linux
	Basicclean::ProcessPID = syscall(SYS_gettid);
#endif
    while(Basicclean::getEnableCleaning()){

        cout << "Walltrace enabled" << endl;
        interpreterreference.drives(roomba::speed::SLOW);

            while(interpreterreference.getBumpRight() == false)
                interpreterreference.drives(roomba::speed::SLOW);
            }
            while(interpreterreference.getBumpRight()){
                interpreterreference.turnRoomba(-1);
            }
            interpreterreference.drives(roomba::speed::SLOW);
            usleep(250);
            interpreterreference.turnRoomba(5);
    }
    interpreterreference.drives(roomba::speed::STOP);
	Basicclean::ProcessPID = 0;
}
