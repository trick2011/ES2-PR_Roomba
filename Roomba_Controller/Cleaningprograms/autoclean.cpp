#include "autoclean.h"

AutoClean::~AutoClean(){}

void AutoClean::clean(void)
{
//	while(getEnableCleaning() == true)
//	{
//		do
//		{
//			interpreterreference.drives(roomba::speed::CRUISE);
//            interpreterreference.brushes(roomba::brush::MAINBRUSH);

//			Run |= interpreterreference.Bumps.bLeft;
//			Run |= interpreterreference.Bumps.bRight;
//			Run |= interpreterreference.Cliff.bFrontLeft;
//			Run |= interpreterreference.Cliff.bFrontRight;
//			Run |= interpreterreference.Cliff.bLeft;
//			Run |= interpreterreference.Cliff.bRight;
//		}
//		while(Run == false && getEnableCleaning() == true);

//        switch(state)
//        {
//        case 0:
//            interpreterreference.turnRoomba(90);
//            interpreterreference.drives(roomba::speed::SLOW);
//            sleep(2);
//            interpreterreference.turnRoomba(90);
//            interpreterreference.brushes(roomba::brush::BOTH);
//            state++;
//            break;
//        case 1:
//            interpreterreference.turnRoomba(270);
//            interpreterreference.drives(roomba::speed::SLOW);
//            sleep(2);
//            interpreterreference.turnRoomba(270);
//            interpreterreference.brushes(roomba::brush::BOTH);
//            state--;
//            break;
//        default:
//            state = 0;
//        }

	while(getEnableCleaning() == true){
		cout << "enabled" << endl;
		interpreterreference.drives(roomba::speed::SLOW);
		do{
			Run = false;
			cout << "go" << endl;
			//interpreterreference.drives(roomba::speed::CRUISE);

			if(interpreterreference.getBumpLeft())
				Run = true;
			//Run |= interpreterreference.getBumpLeft();
			if(interpreterreference.getBumpRight())
				Run = true;
			//Run |= interpreterreference.getBumpRight();

			cout << interpreterreference.getBumpLeft() << endl;
			cout << interpreterreference.getBumpRight() << endl;
			cout << Run << endl;

			//interpreterreference.getclif
//			Run |= interpreterreference.Bumps.bLeft;
//			Run |= interpreterreference.Bumps.bRight;
//			Run |= interpreterreference.Cliff.bFrontLeft;
//			Run |= interpreterreference.Cliff.bFrontRight;
//			Run |= interpreterreference.Cliff.bLeft;
//			Run |= interpreterreference.Cliff.bRight;
			//sleep(1);
		}while((Run == false) && (getEnableCleaning() == true));

		Run = false;
		//interpreterreference.drives(roomba::speed::STOP);
		interpreterreference.turnRoomba(-90);
		sleep(1);
		interpreterreference.drives(roomba::speed::SLOW);
		//interpreterreference.drives(roomba::speed::STOP);
		sleep(1);
		interpreterreference.turnRoomba(-90);
	 }
}
