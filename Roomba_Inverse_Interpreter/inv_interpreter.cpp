#include "inv_interpreter.h"

inv_interpreter::inv_interpreter()
{
    uart = new UARTClass;
}

inv_interpreter::~inv_interpreter()
{
    delete uart;
}


void inv_interpreter::drive()
{
    UARTClass::receiveUart();
    HByte1 = UARTClass::getElement();   //Velocity high byte
    LByte1 = UARTClass::getElement();   //Velocity low  byte
    HByte2 = UARTClass::getElement();   //Radius high byte
    LByte2 = UARTClass::getElement();   //Radius low  byte

    //speed
    if((HByte1 == 0x00)&&(LByte1 <= 0x7F)){
        iCurrentSpeed = roomba::speed::SLOW;
    }
    if((HByte1 == 0x08)&&(LByte1 <= 0x00)){
        iCurrentSpeed = roomba::speed::CRUISE;
    }
    if((HByte1 == 0x7F)&&(LByte1 <= 0xFF)){
        iCurrentSpeed = roomba::speed::FAST;
    }
    if((HByte1 == 0x00)&&(LByte1 <= 0x00)){
        iCurrentSpeed = roomba::speed::STOP;
    }
    if((HByte1 == 0xFF)&&(LByte1 <= 0x81)){
        iCurrentSpeed = roomba::speed::BACKWARDS;
    }

    //radius
    if((HByte2 == 0x00)&&(LByte2 <= 0x81)){
        iCurrentRadius = roomba::radius::SMALL_LEFT;
    }
    if((HByte2 == 0x08)&&(LByte2 <= 0x60)){
        iCurrentRadius = roomba::radius::BIG_LEFT;
    }
    if((HByte2 == 0x80)&&(LByte2 <= 0x7F)){
        iCurrentRadius = roomba::radius::SMALL_RIGHT;
    }
    if((HByte2 == 0xF7)&&(LByte2 <= 0xA0)){
        iCurrentRadius = roomba::radius::BIG_RIGHT;
    }

}

void inv_interpreter::sendBumpAndWheel()
{
    //send bumpAndWheel

}

void inv_interpreter::sendWall()
{
    //send wall

}

void inv_interpreter::sendCliffL()
{
    //send cliffLeft

}

void inv_interpreter::sendCliffFL()
{
    //send cliffFrontLeft

}

void inv_interpreter::sendCliffFR()
{
    //send cliffFrontRight

}

void inv_interpreter::sendCliffR()
{
    //send cliffRight

}

void inv_interpreter::sendDistance()
{
    //send distance

}

void inv_interpreter::sendAngle()
{
    //send angle
    //reset angle

}

void inv_interpreter::sendWallSignal()
{
    //send wallSignal

}

void inv_interpreter::sendCliffL_Signal()
{
    //send cliffLeftSignal
    //2 bytes

}

void inv_interpreter::sendCliffFL_Signal()
{
    //send cliffFrontLeftSignal
    //2 bytes

}

void inv_interpreter::sendCliffFR_Signal()
{
    //send cliffFrontRightSignal
    //2 bytes

}

void inv_interpreter::sendCliffR_Signal()
{
    //send cliffRightSignal
    //2 bytes

}

void inv_interpreter::sendLightBumper()
{
    //send lightBumper

}

void inv_interpreter::sendLightBumpL_Signal()
{
    //send lightBumper L

}

void inv_interpreter::sendLightBumpFL_Signal()
{
    //send lightBumper FL

}

void inv_interpreter::sendLightBumpCL_Signal()
{
    //send lightBumper CL

}

void inv_interpreter::sendLightBumpCR_Signal()
{
    //send lightBumper CR

}

void inv_interpreter::sendLightBumpFR_Signal()
{
    //send lightBumper FR

}

void inv_interpreter::sendLightBumpR_Signal()
{
    //send lightBumper R

}
