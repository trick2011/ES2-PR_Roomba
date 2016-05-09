#include "inv_interpreter.h"

Inv_interpreter::Inv_interpreter(Roomclass& room):room(room){

}
Inv_interpreter::~Inv_interpreter(){
	//delete uart;
}


void Inv_interpreter::drive(){
	//uart.receiveUart();
	HByte1 = uart.getElement();   //Velocity high byte
	LByte1 = uart.getElement();   //Velocity low  byte
	HByte2 = uart.getElement();   //Radius high byte
	LByte2 = uart.getElement();   //Radius low  byte

    //speed
	if((HByte1 == 0x00)&&(LByte1 <= 0x7F))
        iCurrentSpeed = roomba::speed::SLOW;
	if((HByte1 == 0x08)&&(LByte1 <= 0x00))
        iCurrentSpeed = roomba::speed::CRUISE;
	if((HByte1 == 0x7F)&&(LByte1 < 0xFF))
        iCurrentSpeed = roomba::speed::FAST;
	if((HByte1 == 0x00)&&(LByte1 <= 0x00))
        iCurrentSpeed = roomba::speed::STOP;
	if((HByte1 == 0xFF)&&(LByte1 <= 0x81))
        iCurrentSpeed = roomba::speed::BACKWARDS;

    //radius
	if((HByte2 == 0x00)&&(LByte2 <= 0x81))
        iCurrentRadius = roomba::radius::SMALL_LEFT;
	if((HByte2 == 0x08)&&(LByte2 <= 0x60))
        iCurrentRadius = roomba::radius::BIG_LEFT;
	if((HByte2 == 0x80)&&(LByte2 <= 0x7F))
        iCurrentRadius = roomba::radius::SMALL_RIGHT;
	if((HByte2 == 0xF7)&&(LByte2 <= 0xA0))
        iCurrentRadius = roomba::radius::BIG_RIGHT;

    //for Jelle's angle function, smallest turn possible is needed (counter clockwise)
    if((HByte2 == 0x00)&&(LByte2 <= 0x01)){
        //iCurrentRadius = roomba::radius::##TBD##;
    }
    //for Jelle's angle function, smallest turn possible is needed (clockwise)
    if((HByte2 == 0xFF)&&(LByte2 <= 0xFF)){
        //iCurrentRadius = roomba::radius::##TBD##;
    }

	room.roomba->setspeed(iCurrentSpeed);
	room.roomba->setangle(iCurrentRadius);
}
void Inv_interpreter::sendBumpAndWheel(){
    //send bumpAndWheel
	room.roomba->sensors.

}
void Inv_interpreter::sendWall(){
    //send wall

}
void Inv_interpreter::sendCliffL(){
    //send cliffLeft

}
void Inv_interpreter::sendCliffFL(){
    //send cliffFrontLeft

}
void Inv_interpreter::sendCliffFR(){
    //send cliffFrontRight

}
void Inv_interpreter::sendCliffR(){
    //send cliffRight

}
void Inv_interpreter::sendDistance(){
    //send distance

}
void Inv_interpreter::sendAngle(){
    //send angle
    //reset angle

}
void Inv_interpreter::sendWallSignal(){
    //send wallSignal

}
void Inv_interpreter::sendCliffL_Signal(){
    //send cliffLeftSignal
    //2 bytes

}
void Inv_interpreter::sendCliffFL_Signal(){
    //send cliffFrontLeftSignal
    //2 bytes

}
void Inv_interpreter::sendCliffFR_Signal(){
    //send cliffFrontRightSignal
    //2 bytes

}
void Inv_interpreter::sendCliffR_Signal(){
    //send cliffRightSignal
    //2 bytes

}
void Inv_interpreter::sendLightBumper(){
    //send lightBumper

}
void Inv_interpreter::sendLightBumpL_Signal(){
    //send lightBumper L

}
void Inv_interpreter::sendLightBumpFL_Signal(){
    //send lightBumper FL

}
void Inv_interpreter::sendLightBumpCL_Signal(){
    //send lightBumper CL

}
void Inv_interpreter::sendLightBumpCR_Signal(){
    //send lightBumper CR

}
void Inv_interpreter::sendLightBumpFR_Signal(){
    //send lightBumper FR

}
void Inv_interpreter::sendLightBumpR_Signal(){
    //send lightBumper R

}

void Inv_interpreter::receivestart(void){
	while(true){
		uart.receiveUart();
		int tmp = uart.getQueSize();
		for(int i=0;i<tmp;i++)
			if(uart.getElement() == roomba::Start)
				return;
	}
}
void Inv_interpreter::mainroutine(void){
	receivestart();
	while(true){
		uart.receiveUart();
		switch(uart.getElement()){
		case roomba::power:
			//uitzetten?
			break;

		case roomba::Stop:
			//Stop driving and everything
			room.roomba->setspeed(0);
			break;

		case roomba::drive:
			drive();
			break;
		default: // all sensors
		//case roomba::sensors:
			//verzend gevraagde sensor info
			//welke sensor info is gevraagd?
			//meer ontvangen
			uart.receiveUart();
			switch(uart.getElement()){
			case roomba::sensors::bumpAndWheel:
					sendBumpAndWheel();
					break;
			case roomba::sensors::wall:
					sendWall();
					break;
			case roomba::sensors::cliffLeft:
					sendCliffL();
					break;
			case roomba::sensors::cliffFrontLeft:
					sendCliffFL();
					break;
			case roomba::sensors::cliffFrontRight:
					sendCliffFR();
					break;
			case roomba::sensors::cliffRight:
					sendCliffR();
					break;
			case roomba::sensors::distance:
					sendDistance();
					break;
			case roomba::sensors::angle:
					sendAngle();
					break;
			case roomba::sensors::wallSignal:
					sendWallSignal();
					//2 bytes
					break;
			case roomba::sensors::cliffLeftSignal:
					sendCliffL_Signal();
					break;
			case roomba::sensors::cliffFrontLeftSignal:
					sendCliffFL_Signal();
					break;
			case roomba::sensors::cliffFrontRightSignal:
					sendCliffFR_Signal();
					break;
			case roomba::sensors::cliffRightSignal:
					sendCliffR_Signal();
					break;
			case roomba::sensors::lightBumper:
					sendLightBumper();
					break;
			case roomba::sensors::lightBumpLeftSignal:
					sendLightBumpL_Signal();
					break;
			case roomba::sensors::lightBumpFrontLeftSignal:
					sendLightBumpFL_Signal();
					break;
			case roomba::sensors::lightBumpCenterLeftSignal:
					sendLightBumpCL_Signal();
					break;
			case roomba::sensors::lightBumpCenterRightSignal:
					sendLightBumpCR_Signal();
					break;
			case roomba::sensors::lightBumpFrontRightSignal:
					sendLightBumpFR_Signal();
					break;
			case roomba::sensors::lightBumpRightSignal:
					sendLightBumpR_Signal();
					break;
			default:
					//do nothing
					break;
			}
			break;
//		default:
//			//do nothing
//			break;
		}
		if(int tmp = uart.getQueSize() != 0)
			for(int i=0;i<tmp;i++)
				uart.getElement();
	}
}
