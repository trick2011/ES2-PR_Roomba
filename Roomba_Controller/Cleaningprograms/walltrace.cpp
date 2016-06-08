#include "walltrace.h"
#include "autoclean.h"

Walltrace::~Walltrace(){

}

namespace actionlist {
static const int Trace = 0;
static const int Cliff = 1;
static const int Drop  = 2;
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
            Run = true;
            cout << "go" << endl;

//            if(interpreterreference.getCliffFrontLeft() ||
//               interpreterreference.getCliffLeft() ||
//               interpreterreference.getCliffFrontRight() ||
//               interpreterreference.getCliffRight())
//            {
//                Run = false;
//                iState = actionlist::Cliff;
//                break;
//            }
//            if(interpreterreference.getWheelDropLeft()||
//               interpreterreference.getWheelDropRight()||
//               interpreterreference.getWheelOvercurrents())
//            {
//                Run = false;
//                iState = actionlist::Drop;
//                break;
//            }

            while(interpreterreference.getBumpRight() == false){
                interpreterreference.drives(roomba::speed::SLOW);
            }
            interpreterreference.drives(roomba::speed::STOP);

//			while(interpreterreference.getBumpLeft())
//			{
//				interpreterreference.drives(roomba::speed::STOP);
//				interpreterreference.turnRoomba(-5);
//			}

			while(interpreterreference.getBumpRight()){
				interpreterreference.turnRoomba(-2);
            }
            interpreterreference.drives(roomba::speed::SLOW);
            usleep(250);
            interpreterreference.drives(roomba::speed::STOP);
			interpreterreference.turnRoomba(6);

            cout << Run << endl;
        }while((Run == true) && (getEnableCleaning() == true));

        if(!getEnableCleaning()){
            cout << "out"<<endl;
            break;
        }

//        switch(iState){

//        case actionlist::Drop:
//            interpreterreference.drives(roomba::speed::STOP);
//            sleep(3);
//            break;

//        case actionlist::Cliff:
//            interpreterreference.drives(roomba::speed::BACKWARDS);
//            usleep(250);
//            interpreterreference.drives(roomba::speed::STOP);
//            interpreterreference.turnRoomba(5);
//            break;
//        }


        interpreterreference.uart->flushQueue();
    }

	cout << "wall out" << endl;
    interpreterreference.drives(roomba::speed::STOP);
	Basicclean::ProcessPID = 0;
}
