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

inv_interpreter::sendCliff()
{
    //send Cliff
    //cliffLeft
    //cliffFrontLeft
    //cliffFrontRight
    //cliffRight

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

inv_interpreter::sendCliffSignal()
{
    //send cliffSignal
    //cliffLeftSignal
    //cliffFrontLeftSignal
    //cliffFrontRightSignal
    //cliffRightSignal

}

inv_interpreter::sendLightBumper()
{
    //send lightBumper
    //lightBumper
    //lightBumpLeftSignal
    //lightBumpFrontLeftSignal
    //lightBumpCenterLeftSignal
    //lightBumpCenterRightSignal
    //lightBumpFrontRightSignal
    //lightBumpRightSignal

}
