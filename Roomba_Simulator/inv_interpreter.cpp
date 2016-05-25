#include "inv_interpreter.h"

/*
    to do:
    wall?
    Statis?
    angle
    distance

    IR!!!???
*/

Inv_interpreter::Inv_interpreter(Roomclass& room):room(room){

}

Inv_interpreter::~Inv_interpreter(){

}

void Inv_interpreter::drive(){
	//uart.receiveUart();
	try{
		HByte1 = uart.getElement();   //Velocity high byte
	}catch(int){cout << "		TRY CATCH" << endl;cout << "		" << uart.getQueSize() << endl;}

	try{
		LByte1 = uart.getElement();   //Velocity low  byte
	}catch(int){cout << "		TRY CATCH" << endl;cout << "		" << uart.getQueSize() << endl;}

	try{
		HByte2 = uart.getElement();   //Radius high byte
	}catch(int){cout << "		TRY CATCH" << endl;cout << "		" << uart.getQueSize() << endl;}

	try{
		LByte2 = uart.getElement();   //Radius low  byte
	}catch(int){
		cout << "		TRY CATCH" << endl;
		cout << "		" << uart.getQueSize() << endl;
	}

//	  HByte1 = uart.getContElement();   //Velocity high byte
//    LByte1 = uart.getContElement();   //Velocity low  byte
//    HByte2 = uart.getContElement();   //Radius high byte
//    LByte2 = uart.getContElement();   //Radius low  byte

    //speed
	if((HByte1 == 0x00)&&(LByte1 <= 0x7F))
		iCurrentSpeed = roomba::speed::SLOW+1;
	if((HByte1 == 0x08)&&(LByte1 <= 0x00))
		iCurrentSpeed = roomba::speed::CRUISE+1;
	if((HByte1 == 0x7F)&&(LByte1 < 0xFF))
		iCurrentSpeed = roomba::speed::FAST+1;
	if((HByte1 == 0x00)&&(LByte1 <= 0x00))
		iCurrentSpeed = roomba::speed::STOP-3;
	if((HByte1 == 0xFF)&&(LByte1 <= 0x81))
		iCurrentSpeed = roomba::speed::BACKWARDS-5;

    //radius
    iCurrentAngle = (LByte2 | (HByte2 << 8));
    //negatief getal draait met klok mee en positief getal draait tegen de klok in
    //dus logisch maken en nu is negatief tegen de klok in en positief met de klok mee
	iCurrentAngle = -iCurrentAngle;
	if(HByte2 == 0x80 & LByte2 == 0x00) //straight
		iCurrentAngle = 0;
	if(HByte2 == 0x7F & LByte2 == 0xFF) //straight
		iCurrentAngle = 0;
	if(HByte2 == 0xFF & LByte2 == 0xFF)  //clockwise
		iCurrentAngle = 90;
	if(HByte2 == 0x00 & LByte2 == 0x01) //counter clockwise
		iCurrentAngle = -90;

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
void Inv_interpreter::sendAngle(){
    //send angle
    //reset angle
    uart.sendUart(iCurrentAngle << 8);
    uart.sendUart(iCurrentAngle);
    iCurrentAngle = 0;
}
void Inv_interpreter::sendLightBumper(){
    //send lightBumper
    uint8_t temp = 0;
    if((room.roomba->sensorref.getLightBumpLeft()) >= iLightBump){
    temp = (temp | 0x00000001);
    }
    if((room.roomba->sensorref.getLightBumpFrontLeft()) >= iLightBump){
    temp = (temp | 0x00000010);
    }
    if((room.roomba->sensorref.getLightBumpCenter()) >= iLightBump){
    temp = (temp | 0x00001100);
    }
    if((room.roomba->sensorref.getLightBumpFrontRight()) >= iLightBump){
    temp = (temp | 0x00010000);
    }
    if((room.roomba->sensorref.getLightBumpRight()) >= iLightBump){
    temp = (temp | 0x00100000);
    }
    uart.sendUart(temp);
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

void Inv_interpreter::sendRequestedVelocity()
{
    //send requestedVelocity
    uint16_t temp = iCurrentSpeed;
    uart.sendUart(temp << 8);
    uart.sendUart(temp);
}

void Inv_interpreter::receivestart(void){
	bool clear =false;
	uint8_t ReceiveValue = 0;
	while(true){
		uart.receiveUart();
		int tmp = uart.getQueSize();
		for(int i=0;i<tmp;i++){
			ReceiveValue = uart.getElement();
			if(ReceiveValue == roomba::Start)
				clear = true;
			if(clear)
				if(ReceiveValue == roomba::modes::safeMode)
					return;
		}
	}
#warning "not in full mode"
}
void Inv_interpreter::mainroutine(void){
	receivestart();
	while(true){
		uart.flushQueue();
		uart.receiveUartFast();
		cout << "mainqueue		" << uart.getQueSize() << endl;
		uint8_t element = uart.getElement();

//		uart.startUartContinuous();
//        uart.receiveUartContinuous();
//        uint8_t element = uart.getContElement();
		switch(element){
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
			uart.receiveUartFast();
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
//#####################################################################################################################
            case roomba::sensors::virtualWall:
                    sendVirtualWall();
                    break;
            case roomba::sensors::wheelOvercurrents:
                    sendWheelOvercurrents();
                    break;
            case roomba::sensors::dirtDetect:
                    sendDirtDetect();
                    break;
            case roomba::sensors::irReceiver:
                    sendIrReceiver();
                    break;
            case roomba::sensors::chargingState:
                    sendChargingState();
                    break;
            case roomba::sensors::chargingSource:
                    sendChargingSource();
                    break;
            case roomba::sensors::batteryVoltage:
                    sendBatteryVoltage();
                    break;
            case roomba::sensors::batteryCurrent:
                    sendBatteryCurrent();
                    break;
            case roomba::sensors::batteryTemperature:
                    sendBatteryTemperature();
                    break;
            case roomba::sensors::batteryCharge:
                    sendBatteryCharge();
                    break;
            case roomba::sensors::batteryCapacity:
                    sendBatteryCapacity();
                    break;
            case roomba::sensors::oiMode:
                    sendOiMode();
                    break;
            case roomba::sensors::songNumber:
                    sendSongNumber();
                    break;
            case roomba::sensors::songPlaying:
                    sendSongPlaying();
                    break;
            case roomba::sensors::requestedVelocity:
                    sendRequestedVelocity();
                    break;
            case roomba::sensors::requestedRadius:
                    sendRequestedRadius();
                    break;
            case roomba::sensors::requestedRightVelocity:
                    sendRequestedRightVelocity();
                    break;
            case roomba::sensors::requestedLeftVelocity:
                    sendRequestedLeftVelocity();
                    break;
            case roomba::sensors::leftEncoderCount:
                    sendLeftEncoderCount();
                    break;
            case roomba::sensors::rightEncoderCount:
                    sendRightEncoderCount();
                    break;
            case roomba::sensors::leftMotorCurrent:
                    sendLeftMotorCurrent();
                    break;
            case roomba::sensors::rightMotorCurrent:
                    sendRightMotorCurrent();
                    break;
            case roomba::sensors::mainBrushMotorCurrent:
                    sendMainBrushMotorCurrent();
                    break;
            case roomba::sensors::sideBrushMotorCurrent:
                    sendSideBrushMotorCurrent();
                    break;
            case roomba::sensors::statis:
                    sendStatis();
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


//#####################################################################################################################
//#####################################################################################################################
//#####################################################################################################################
//v Dummy Functions     ^real functions

void Inv_interpreter::sendWall()
{
    //send wall
    uint8_t temp = 0;
    uart.sendUart(temp);
}

void Inv_interpreter::sendVirtualWall()
{
    //send virtualWall
    uint8_t temp = 0;
    uart.sendUart(temp);
}

void Inv_interpreter::sendDirtDetect()
{
    //send dirtDetect
    uint8_t temp = 0;
    uart.sendUart(temp);
}

void Inv_interpreter::sendIrReceiver()
{
    //send irReceiver
    uint8_t temp = 0;
    uart.sendUart(temp);
}

void Inv_interpreter::sendDistance()
{
    //send distance
    int16_t temp = 0;
    uart.sendUart(temp << 8);
    uart.sendUart(temp);
}

void Inv_interpreter::sendChargingState()
{
    //send chargingState
    uint8_t temp = 0;
    uart.sendUart(temp);
}

void Inv_interpreter::sendBatteryVoltage()
{
    //send batteryVoltage
    int16_t temp = 12000;
    uart.sendUart(temp << 8);
    uart.sendUart(temp);
}

void Inv_interpreter::sendBatteryCurrent()
{
    //send batteryCurrent
    int16_t temp = -800;
    uart.sendUart(temp << 8);
    uart.sendUart(temp);
}

void Inv_interpreter::sendBatteryTemperature()
{
    //send batteryTemperature
    uint8_t temp = 30;
    uart.sendUart(temp);
}

void Inv_interpreter::sendBatteryCharge()
{
    //send batteryCharge
    uint16_t temp = 10000;
    uart.sendUart(temp << 8);
    uart.sendUart(temp);
}

void Inv_interpreter::sendBatteryCapacity()
{
    //send batteryCapacity
    uint16_t temp = 14000;
    uart.sendUart(temp << 8);
    uart.sendUart(temp);
}

void Inv_interpreter::sendWallSignal()
{
    //send wallSignal
    uint16_t temp = 0;
    uart.sendUart(temp << 8);
    uart.sendUart(temp);
}

void Inv_interpreter::sendCliffL_Signal(){
    //send cliffLeftSignal
    uint16_t temp = 0;
    if((room.roomba->sensorref.getCliffLeft()) == true){temp = 2050;}
    uart.sendUart(temp);
}
void Inv_interpreter::sendCliffFL_Signal(){
    //send cliffFrontLeftSignal
    uint16_t temp = 0;
    if((room.roomba->sensorref.getCliffFrontLeft()) == true){temp = 2050;}
    uart.sendUart(temp);
}
void Inv_interpreter::sendCliffFR_Signal(){
    //send cliffFrontRightSignal
    uint16_t temp = 0;
    if((room.roomba->sensorref.getCliffFrontRight()) == true){temp = 2050;}
    uart.sendUart(temp);
}
void Inv_interpreter::sendCliffR_Signal(){
    //send cliffRightSignal
    uint16_t temp = 0;
    if((room.roomba->sensorref.getCliffRight()) == true){temp = 2050;}
    uart.sendUart(temp);
}

void Inv_interpreter::sendChargingSource()
{
    //send chargingSource
    uint8_t temp = 0;
    uart.sendUart(temp);
}

void Inv_interpreter::sendOiMode()
{
    //send oiMode
    uint8_t temp = 3;
    uart.sendUart(temp);
}

void Inv_interpreter::sendSongNumber()
{
    //send songNumber
    uint8_t temp = 0;
    uart.sendUart(temp);
}

void Inv_interpreter::sendSongPlaying()
{
    //send songPlaying
    uint8_t temp = 0;
    uart.sendUart(temp);
}

void Inv_interpreter::sendRequestedRadius()
{
    //send requestedRadius
    int16_t temp = 0;
    uart.sendUart(temp << 8);
    uart.sendUart(temp);
}

void Inv_interpreter::sendRequestedRightVelocity()
{
    //send requestedRightVelocity
    int16_t temp = (iCurrentSpeed / 2);
    uart.sendUart(temp << 8);
    uart.sendUart(temp);
}

void Inv_interpreter::sendRequestedLeftVelocity()
{
    //send requestedLeftVelocity
    int16_t temp = (iCurrentSpeed / 2);
    uart.sendUart(temp << 8);
    uart.sendUart(temp);
}

void Inv_interpreter::sendLeftEncoderCount()
{
    //send LeftEncoderCount
    uint8_t temp = 0;
    uart.sendUart(temp);
}

void Inv_interpreter::sendRightEncoderCount()
{
    //send RightEncoderCount
    uint8_t temp = 0;
    uart.sendUart(temp);
}

void Inv_interpreter::sendLeftMotorCurrent()
{
    //send LeftMotorCurrent
    int16_t temp = 500;
    uart.sendUart(temp << 8);
    uart.sendUart(temp);
}

void Inv_interpreter::sendRightMotorCurrent()
{
    //send RightMotorCurrent
    int16_t temp = 500;
    uart.sendUart(temp << 8);
    uart.sendUart(temp);
}

void Inv_interpreter::sendMainBrushMotorCurrent()
{
    //send MainBrushMotorCurrent
    int16_t temp = 300;
    uart.sendUart(temp << 8);
    uart.sendUart(temp);
}

void Inv_interpreter::sendSideBrushMotorCurrent()
{
    //send SideBrushMotorCurrent
    int16_t temp = 100;
    uart.sendUart(temp << 8);
    uart.sendUart(temp);
}

void Inv_interpreter::sendStatis()
{
    //send Statis
    uint8_t temp = 0;
    uart.sendUart(temp);
}

void Inv_interpreter::sendWheelOvercurrents()
{
    //send wheelOvercurrents
    uint8_t temp = 0;
    uart.sendUart(temp);
}

