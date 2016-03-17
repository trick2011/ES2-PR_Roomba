#include "failsave.h"
#include "opcodes.h"

failsave::failsave(std::mutex &tex):tex(tex)
{
    stop = false;
    Opcodes = new opcodes;
}

failsave::~failsave()
{
    stopFailsave();
    delete Opcodes;
}

void failsave::stopFailsave()
{
    tex.lock();
    stop = true;
    tex.unlock();
}

void failsave::checkCodes()
{
    while(1)
    {
        if(checkRunning())break; // stop thread when requested
        usleep(100);

        Opcodes->lockMutex(); // lock mutex for send and receive

        /* check critical sensors and intervene if neccesary*/
        if(Opcodes->getBumpAndWheel())Opcodes->sendUart(Stop);
        if(Opcodes->getCliffLeftSignal() > 2048)Opcodes->sendUart(Stop);
        if(Opcodes->getCliffFrontLeftSignal() > 2048)Opcodes->sendUart(Stop);
        if(Opcodes->getCliffFrontRightSignal() > 2048)Opcodes->sendUart(Stop);
        if(Opcodes->getCliffRightSignal() > 2048)Opcodes->sendUart(Stop);
        if(Opcodes->getLeftWheelOvercurrent())Opcodes->sendUart(Stop);
        if((Opcodes->getBatteryCapacity()/Opcodes->getBatteryCharge()*100) < 10)Opcodes->sendUart(Stop);

        Opcodes->unlockMutex(); // free mutex for standard procedure
    }
}

bool failsave::checkRunning()
{
    tex.lock();
    bool temp = stop;
    tex.unlock();
    return temp;
}
