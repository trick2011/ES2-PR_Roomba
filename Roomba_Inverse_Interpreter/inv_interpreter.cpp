#include "inv_interpreter.h"

inv_interpreter::interpreter()
{
    uart = new Uart;
}

inv_interpreter::~interpreter()
{
    delete uart;
}


inv_interpreter::sendBumpAndWheel()
{
    //send bumpAndWheel

}

inv_interpreter::sendWall()
{
    //send wall

}

inv_interpreter::sendCliffLeft()
{
    //send cliffLeft

}

inv_interpreter::sendCliffFrontLeft()
{
    //send cliffFrontLeft

}

inv_interpreter::sendCliffFrontRight()
{
    //send cliffFrontRight

}

inv_interpreter::sendCliffRight()
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

inv_interpreter::sendCliffLeftSignal()
{
    //send cliffSignal
    //2 bytes

}

inv_interpreter::sendCliffFrontLeftSignal()
{
    //send cliffSignal
    //2 bytes

}

inv_interpreter::sendCliffFrontRightSignal()
{
    //send cliffSignal
    //2 bytes

}

inv_interpreter::sendCliffRightSignal()
{
    //send cliffSignal
    //2 bytes

}

inv_interpreter::sendLightBump()
{
    //send lightBumper

}

inv_interpreter::sendLightBump()
{
    //send lightBumper

}

inv_interpreter::sendLightBump()
{
    //send lightBumper

}

inv_interpreter::sendLightBump()
{
    //send lightBumper

}

inv_interpreter::sendLightBump()
{
    //send lightBumper

}

inv_interpreter::sendLightBump()
{
    //send lightBumper

}
