#include "failsave.h"
#include "opcodes.h"

failsave::failsave()
{
    stop = false;
    Opcodes = new opcodes;
    uart = new Uart;
}

failsave::~failsave()
{
    stopFailsave();
    delete Opcodes;
}

void failsave::stopFailsave()
{
    stop = true;
}

void failsave::checkCodes()
{
    while(1)
    {
        if(checkRunning())break; // stop thread when requested
        usleep(100);

        Opcodes->lockMutex(); // lock mutex for send and receive

        /* check critical sensors and intervene if neccesary*/
        if(Opcodes->getBumpAndWheel())uart->sendUart(Stop);
        if(Opcodes->getCliffLeftSignal() > 2048)uart->sendUart(Stop);
        if(Opcodes->getCliffFrontLeftSignal() > 2048)uart->sendUart(Stop);
        if(Opcodes->getCliffFrontRightSignal() > 2048)uart->sendUart(Stop);
        if(Opcodes->getCliffRightSignal() > 2048)uart->sendUart(Stop);
        if(Opcodes->getLeftWheelOvercurrent())uart->sendUart(Stop);
        if((Opcodes->getBatteryCapacity()/Opcodes->getBatteryCharge()*100) < 10)uart->sendUart(Stop);

        Opcodes->unlockMutex(); // free mutex for standard procedure
    }
}

bool failsave::checkRunning()
{
    return stop;
}
