#include "autoclean.h"


AutoClean::~AutoClean(){

}

namespace actionlist{
static const int CliffLeft	= 0;
static const int CliffRight	= 1;
static const int Turn		= 2;
static const int WheelDrop	= 3;
}

void AutoClean::clean(void)
{
#ifdef __linux
	Basicclean::ProcessPID = syscall(SYS_gettid);
#endif
	bool TurnLeft = true;
	while(Basicclean::getEnableCleaning()){
        cout << "autoclean enabled" << endl;
		interpreterreference.drives(roomba::speed::SLOW);
		do{
			Run = true;
			cout << "go" << endl;

			if(interpreterreference.getCliffFrontLeft() || interpreterreference.getCliffLeft()){
				Run = false;
				iState = actionlist::CliffLeft;
				break;
			}

			if(interpreterreference.getCliffFrontRight() || interpreterreference.getCliffRight()){
				Run = false;
				iState = actionlist::CliffRight;
				break;
			}

			if(interpreterreference.getBumpLeft()||interpreterreference.getBumpRight()){ // bump kan wel samen
				Run = false;
				iState = actionlist::Turn;
				break;
            }

			//cout << interpreterreference.getBumpLeft() << endl;
			//cout << interpreterreference.getBumpRight() << endl;
			cout << Run << endl;

        }while((Run == true) && (getEnableCleaning() == true));

		if(!getEnableCleaning()){
			cout << "out"<<endl;
			break;
		}

		switch(iState){

		case actionlist::CliffLeft: //Cliff links
			cout << "cliff links" << endl;
			//Run = true;
			interpreterreference.drives(roomba::speed::BACKWARDS);
			usleep(500);
			interpreterreference.turnRoomba(5); // rechts
			iState = actionlist::Turn;
			TurnLeft = false;
			break;

		case actionlist::CliffRight: // Cliff rechts
			cout << "cliff rechts" << endl;
			Run = false;
			interpreterreference.drives(roomba::speed::BACKWARDS);
			usleep(500);
			interpreterreference.turnRoomba(-5); // links
			iState = actionlist::Turn;
			TurnLeft = true;
			break;

		case actionlist::Turn: //bocht naar links
            cout << "bocht naar links" << endl;
			if(TurnLeft){ // turnleft
				//interpreterreference.drives(roomba::speed::BACKWARDS);
				//sleep(1);
				interpreterreference.drives(roomba::speed::STOP);
				interpreterreference.turnLeft();
				//sleep(1);
				//chrono en while zie uart
                interpreterreference.drives(roomba::speed::SLOW);
				sleep(1);
				interpreterreference.turnLeft();
				iState = actionlist::Turn;
				TurnLeft = false;
			}
			else{ // turnright
				cout << "bocht naar recht" << endl;
				//interpreterreference.drives(roomba::speed::BACKWARDS);
				//sleep(1);
				interpreterreference.drives(roomba::speed::STOP);
				interpreterreference.turnRight();
				//sleep(1);
                interpreterreference.drives(roomba::speed::SLOW);
				sleep(1);
				interpreterreference.turnRight();
				iState = actionlist::Turn;
				TurnLeft = true;
			}
			break;
		case actionlist::WheelDrop:
			interpreterreference.drives(roomba::speed::STOP);
			interpreterreference.stopRoomba();
			break;
        default:
            iState = actionlist::Turn;
			break;
        }
	 }
	interpreterreference.drives(roomba::speed::STOP);
	Basicclean::ProcessPID = 0;
}


