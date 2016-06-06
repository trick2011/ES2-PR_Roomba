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

            if(interpreterreference.getCliffFrontLeft() || interpreterreference.getCliffLeft()== true)
            {
                Run = true;
                iState = 0;
                break;
            }

            if(interpreterreference.getCliffFrontRight() || interpreterreference.getCliffRight() == true)
            {
                Run = true;
                iState = 1;
                break;
            }

            if(interpreterreference.getBumpLeft()== true)
            {
                Run = true;
                iState = 2;
                break;
            }
            if(interpreterreference.getBumpRight()== true)
            {
				Run = true;
                iState = 3;
                break;
            }

			cout << interpreterreference.getBumpLeft() << endl;
			cout << interpreterreference.getBumpRight() << endl;
			cout << Run << endl;

        }while((Run == true) && (getEnableCleaning() == true));

        switch(iState)
        {
        case 0: //Cliff links
            cout << "cliff links" << endl;
            Run = false;
            interpreterreference.drives(roomba::speed::BACKWARDS);
            sleep(1);
            interpreterreference.turnRoomba(30);
            break;
        case 1: // Cliff rechts
            cout << "cliff rechts" << endl;
            Run = false;
            interpreterreference.drives(roomba::speed::BACKWARDS);
            sleep(1);
            interpreterreference.turnRoomba(-30);
            break;
            break;
        case 2: //bocht naar links
            cout << "bocht naar links" << endl;
            Run = false;
            interpreterreference.turnLeft();
            sleep(1);
            //chrono en while zie uart
            interpreterreference.drives(roomba::speed::SLOW);
            sleep(1);
            interpreterreference.turnLeft();
            iState = 1;
            break;
        case 3: //bocht naar rechts
            cout << "bocht naar recht" << endl;
            Run = false;
            interpreterreference.turnRight();
            sleep(1);
            interpreterreference.drives(roomba::speed::SLOW);
            sleep(1);
            interpreterreference.turnRight();
            iState = 0;
            break;
        default:
            iState = 0;
			break;
        }
	 }
	interpreterreference.drives(roomba::speed::STOP);
	Basicclean::ProcessPID = 0;
}


