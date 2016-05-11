#include "inv_interpreter.h"

/*
    to do:
    Lightbumper normal
    wall?
    angle
*/

Inv_interpreter::Inv_interpreter(Roomclass& room):room(room){

}

Inv_interpreter::~Inv_interpreter(){

}

void Inv_interpreter::drive(){
    uart.receiveUart();
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
    iCurrentAngle = (LByte2 | (HByte2 << 8));
    //negatief getal draait met klok mee en positief getal draait tegen de klok in
    //dus logisch maken en nu is negatief tegen de klok in en positief met de klok mee
    iCurrentAngle = iCurrentAngle * (-1);

	room.roomba->setspeed(iCurrentSpeed);
    room.roomba->setangle(iCurrentAngle);
}
void Inv_interpreter::sendBumpAndWheel(){
    //send bumpAndWheel
    uint8_t temp = 0;
    bool t1 = 0;
    bool t2 = 0;
    t1 = room.roomba->sensorref.getbBumpLeft();
    t2 = room.roomba->sensorref.getbBumpRight();

    if(t1 == true){temp = (temp | 0x00000010);}
    if(t2 == true){temp = (temp | 0x00000001);}

    uart.sendUart(temp);
}
void Inv_interpreter::sendWall(){
    //send wall
    //Not Implemented
}
void Inv_interpreter::sendCliffL(){
    //send cliffLeft
    uint8_t temp = 0;
    if((room.roomba->sensorref.getCliffLeft()) == true){temp = (temp | 0x00000001);}
    uart.sendUart(temp);
}
void Inv_interpreter::sendCliffFL(){
    //send cliffFrontLeft
    uint8_t temp = 0;
    if((room.roomba->sensorref.getCliffFrontLeft()) == true){temp = (temp | 0x00000001);}
    uart.sendUart(temp);
}
void Inv_interpreter::sendCliffFR(){
    //send cliffFrontRight
    uint8_t temp = 0;
    if((room.roomba->sensorref.getCliffFrontRight()) == true){temp = (temp | 0x00000001);}
    uart.sendUart(temp);
}
void Inv_interpreter::sendCliffR(){
    //send cliffRight
    uint8_t temp = 0;
    if((room.roomba->sensorref.getCliffRight()) == true){temp = (temp | 0x00000001);}
    uart.sendUart(temp);
}
void Inv_interpreter::sendDistance(){
    //send distance
    //Not Implemented
}
void Inv_interpreter::sendAngle(){
    //send angle
    //reset angle
//Not Implemented ###
}
void Inv_interpreter::sendWallSignal(){
    //send wallSignal
    //Not Implemented
}
void Inv_interpreter::sendCliffL_Signal(){
    //send cliffLeftSignal
    //2 bytes
    //Not Implemented
}
void Inv_interpreter::sendCliffFL_Signal(){
    //send cliffFrontLeftSignal
    //2 bytes
    //Not Implemented
}
void Inv_interpreter::sendCliffFR_Signal(){
    //send cliffFrontRightSignal
    //2 bytes
    //Not Implemented
}
void Inv_interpreter::sendCliffR_Signal(){
    //send cliffRightSignal
    //2 bytes
    //Not Implemented
}
void Inv_interpreter::sendLightBumper(){
    //send lightBumper
    //Not Implemented YET!!!
}
void Inv_interpreter::sendLightBumpL_Signal(){
    //send lightBumper L
    uart.sendUart(room.roomba->sensorref.getLightBumpLeft());
}
void Inv_interpreter::sendLightBumpFL_Signal(){
    //send lightBumper FL
    uart.sendUart(room.roomba->sensorref.getLightBumpFrontLeft());
}
void Inv_interpreter::sendLightBumpCL_Signal(){
    //send lightBumper CL
    uart.sendUart(room.roomba->sensorref.getLightBumpCenter());
}
void Inv_interpreter::sendLightBumpCR_Signal(){
    //send lightBumper CR
    uart.sendUart(room.roomba->sensorref.getLightBumpCenter());
}
void Inv_interpreter::sendLightBumpFR_Signal(){
    //send lightBumper FR
    uart.sendUart(room.roomba->sensorref.getLightBumpFrontRight());
}
void Inv_interpreter::sendLightBumpR_Signal(){
    //send lightBumper R
    uart.sendUart(room.roomba->sensorref.getLightBumpRight());
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
		}
		if(int tmp = uart.getQueSize() != 0)
			for(int i=0;i<tmp;i++)
				uart.getElement();
	}
}
