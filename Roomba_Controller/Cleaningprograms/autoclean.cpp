#include "autoclean.h"


AutoClean::~AutoClean(){

}

void AutoClean::clean(void)
{
#ifdef __linux
	Basicclean::ProcessPID = syscall(SYS_gettid);
#endif
	while(Basicclean::getEnableCleaning() == true){
		cout << "enabled" << endl;
		interpreterreference.drives(roomba::speed::SLOW);
		do{
			Run = false;
			cout << "go" << endl;
			//interpreterreference.drives(roomba::speed::CRUISE);

			if(interpreterreference.getBumpLeft())
				// break;
				Run = true;
			//Run |= interpreterreference.getBumpLeft();
			if(interpreterreference.getBumpRight())
				Run = true;
			//Run |= interpreterreference.getBumpRight();

			cout << interpreterreference.getBumpLeft() << endl;
			cout << interpreterreference.getBumpRight() << endl;
			cout << Run << endl;

		}while((Run == false)/*true*/ && (getEnableCleaning() == true));

        switch(iState)
        {
        case 0: //bocht naar links
            cout << "bocht naar links" << endl;
            Run = false;
            interpreterreference.turnLeft();
            sleep(1);
            interpreterreference.drives(roomba::speed::SLOW);
            sleep(1);
            interpreterreference.turnLeft();
            iState = 1;
            break;
        case 1: //bocht naar rechts
            cout << "bocht naar recht" << endl;
            Run = false;
            interpreterreference.turnRoomba(90);
            sleep(1);
            interpreterreference.drives(roomba::speed::SLOW);
            sleep(1);
            interpreterreference.turnRoomba(90);
            iState = 0;
            break;
        default:
            iState = 0;
        }
	 }
	interpreterreference.drives(roomba::speed::STOP);
	Basicclean::ProcessPID = 0;
}


