#include "inv_interpreter.h"

inv_interpreter::inv_interpreter()
{
    uart = new Uart;
}

inv_interpreter::~inv_interpreter()
{
    delete uart;
}


inv_interpreter::drive()
{
    UARTClass::receiveUart();
    HByte1 = UARTClass::getElement();   //Velocity high byte
    LByte1 = UARTClass::getElement();   //Velocity low  byte
    HByte2 = UARTClass::getElement();   //Radius high byte
    LByte2 = UARTClass::getElement();   //Radius low  byte

    if((HByte1 == 0x00)&&(LByte1 <= 0x7F)){
        iCurrentSpeed = roomba::speed:SLOW;
    }



}

inv_interpreter::sendBumpAndWheel()
{
    //send bumpAndWheel

}

inv_interpreter::sendWall()
{
    //send wall

}

inv_interpreter::sendCliffL()
{
    //send cliffLeft

}

inv_interpreter::sendCliffFL()
{
    //send cliffFrontLeft

}

inv_interpreter::sendCliffFR()
{
    //send cliffFrontRight

}

inv_interpreter::sendCliffR()
{
    //send cliffRight

}

inv_interpreter::sendDistance()
{
    //send distance

}

inv_interpreter::sendAngle()
{
    //send angle
    //reset angle

}

inv_interpreter::sendWallSignal()
{
    //send wallSignal

}

inv_interpreter::sendCliffL_Signal()
{
    //send cliffLeftSignal
    //2 bytes

}

inv_interpreter::sendCliffFL_Signal()
{
    //send cliffFrontLeftSignal
    //2 bytes

}

inv_interpreter::sendCliffFR_Signal()
{
    //send cliffFrontRightSignal
    //2 bytes

}

inv_interpreter::sendCliffR_Signal()
{
    //send cliffRightSignal
    //2 bytes

}

inv_interpreter::sendLightBumper()
{
    //send lightBumper

}

inv_interpreter::sendLightBumpL_Signal()
{
    //send lightBumper L

}

inv_interpreter::sendLightBumpFL_Signal()
{
    //send lightBumper FL

}

inv_interpreter::sendLightBumpCL_Signal()
{
    //send lightBumper CL

}

inv_interpreter::sendLightBumpCR_Signal()
{
    //send lightBumper CR

}

inv_interpreter::sendLightBumpFR_Signal()
{
    //send lightBumper FR

}

inv_interpreter::sendLightBumpR_Signal()
{
    //send lightBumper R

}
