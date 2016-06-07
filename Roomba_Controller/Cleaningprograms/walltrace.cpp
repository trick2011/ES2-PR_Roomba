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
        do{
            if(interpreterreference.getBumpLeft()){
                Run = false;
                iState = actionlist::BumpLeft;
                break;
            }
            if(interpreterreference.getBumpRight()){
                Run = false;
                iState = actionlist::BumpRight;
                break;
            }
            cout << Run << endl;
           }

        while((Run == true) && (getEnableCleaning()== true));
        {
            switch(iState){
            case actionlist::BumpLeft:
                interpreterreference.turnRoomba(300);
                interpreterreference.drives(roomba::speed::SLOW);
                break;
            case actionlist::BumpRight:
                interpreterreference.turnRoomba(5);
                interpreterreference.drives(roomba::speed::SLOW);
                break;
            default:
                iState = actionlist::BumpLeft;
                break;
            }
        }
    }
    interpreterreference.drives(roomba::speed::STOP);
	Basicclean::ProcessPID = 0;
}
