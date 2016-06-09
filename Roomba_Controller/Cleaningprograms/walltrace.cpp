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
#ifdef VERBOSE
        cout << "Walltrace enabled" << endl;
#endif
		interpreterreference.drives(roomba::speed::SLOW);

        do{
            Run = true;
#ifdef VERBOSE
            cout << "go" << endl;
#endif

            while((interpreterreference.getBumpRight() == false) && (getEnableCleaning() == true) ){
                interpreterreference.drives(roomba::speed::SLOW);
            }
            interpreterreference.drives(roomba::speed::STOP);

            while((interpreterreference.getBumpRight()) && (getEnableCleaning() == true)){
				interpreterreference.turnRoomba(-2);
            }
            if(!getEnableCleaning())
            {
                break;
            }
            interpreterreference.drives(roomba::speed::SLOW);
            usleep(250);
            interpreterreference.drives(roomba::speed::STOP);
			interpreterreference.turnRoomba(6);
#ifdef VERBOSE
            cout << Run << endl;
#endif
        }while((Run == true) && (getEnableCleaning() == true));

#ifdef VERBOSE
        if(!getEnableCleaning()){
            cout << "out"<<endl;
            break;
        }
#endif

        interpreterreference.uart->flushQueue();
    }

//	cout << "wall out" << endl;
    interpreterreference.drives(roomba::speed::STOP);
	Basicclean::ProcessPID = 0;
}
