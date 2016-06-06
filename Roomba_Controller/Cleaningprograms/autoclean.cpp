#include "autoclean.h"


AutoClean::~AutoClean(){

}

void AutoClean::clean(void)
{
#ifdef __linux
	Basicclean::ProcessPID = syscall(SYS_gettid);
#endif
	while(Basicclean::getEnableCleaning()){
		cout << "enabled" << endl;
		interpreterreference.drives(roomba::speed::SLOW);
		
        do{
			Run = true;
			cout << "go" << endl;

            if(interpreterreference.getCliffFrontLeft() || interpreterreference.getCliffLeft())
            {
                Run = false;
                iState = 0;
                break;
            }

            if(interpreterreference.getCliffFrontRight() || interpreterreference.getCliffRight())
            {
                Run = false;
                iState = 1;
                break;
            }

            if(interpreterreference.getBumpLeft())
            {
                Run = false;
                break;
            }
            if(interpreterreference.getBumpRight())
            {
				Run = false;
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
            //Run = true;
            interpreterreference.drives(roomba::speed::BACKWARDS);
            sleep(1);
            interpreterreference.turnRoomba(30);
            iState = 2;
            break;
        case 1: // Cliff rechts
            cout << "cliff rechts" << endl;
            Run = false;
            interpreterreference.drives(roomba::speed::BACKWARDS);
            sleep(1);
            interpreterreference.turnRoomba(-30);
            iState = 3;
            break;
        case 2: //bocht naar links
            cout << "bocht naar links" << endl;
            //Run = true;
            interpreterreference.drives(roomba::speed::BACKWARDS);
            sleep(1);
            interpreterreference.drives(roomba::speed::STOP);
            interpreterreference.turnLeft();
            //sleep(1);
            //chrono en while zie uart
            interpreterreference.drives(roomba::speed::SLOW);
            //sleep(1);
            for(unsigned int i = 0 ; i < 100 ; i += Peter->getDistance())
            {
                if(interpreterreference.getCliffFrontLeft() || interpreterreference.getCliffLeft())
                {
                    interpreterreference.drives(roomba::speed::BACKWARDS);
                    sleep(1);
                    interpreterreference.drives(roomba::speed::STOP);
                    break;
                }

                if(interpreterreference.getCliffFrontRight() || interpreterreference.getCliffRight())
                {
                    interpreterreference.drives(roomba::speed::BACKWARDS);
                    sleep(1);
                    interpreterreference.drives(roomba::speed::STOP);
                    break;
                }

                if(interpreterreference.getBumpLeft())
                {
                    interpreterreference.drives(roomba::speed::BACKWARDS);
                    sleep(1);
                    interpreterreference.drives(roomba::speed::STOP);
                    break;
                }
                if(interpreterreference.getBumpRight())
                {
                    interpreterreference.drives(roomba::speed::BACKWARDS);
                    sleep(1);
                    interpreterreference.drives(roomba::speed::STOP);
                    break;
                }
            }
            interpreterreference.turnLeft();
            iState = 3;
            break;
        case 3: //bocht naar rechts
            cout << "bocht naar recht" << endl;
            //Run = true;
            interpreterreference.drives(roomba::speed::BACKWARDS);
            sleep(1);
            interpreterreference.drives(roomba::speed::STOP);
            interpreterreference.turnRight();
            //sleep(1);
            interpreterreference.drives(roomba::speed::SLOW);
            for(unsigned int i = 0 ; i < 100 ; i += Peter->getDistance())
            {
                if(interpreterreference.getCliffFrontLeft() || interpreterreference.getCliffLeft())
                {
                    interpreterreference.drives(roomba::speed::BACKWARDS);
                    sleep(1);
                    interpreterreference.drives(roomba::speed::STOP);
                    break;
                }

                if(interpreterreference.getCliffFrontRight() || interpreterreference.getCliffRight())
                {
                    interpreterreference.drives(roomba::speed::BACKWARDS);
                    sleep(1);
                    interpreterreference.drives(roomba::speed::STOP);
                    break;
                }

                if(interpreterreference.getBumpLeft())
                {
                    interpreterreference.drives(roomba::speed::BACKWARDS);
                    sleep(1);
                    interpreterreference.drives(roomba::speed::STOP);
                    break;
                }
                if(interpreterreference.getBumpRight())
                {
                    interpreterreference.drives(roomba::speed::BACKWARDS);
                    sleep(1);
                    interpreterreference.drives(roomba::speed::STOP);
                    break;
                }
            }
            interpreterreference.turnRight();
            iState = 2;
            break;
        default:
            iState = 2;
			break;
        }
	 }
	interpreterreference.drives(roomba::speed::STOP);
	Basicclean::ProcessPID = 0;
}


