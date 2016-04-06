#include "interpreter.h"

interpreter::interpreter()
{
#ifdef fulldebug
    std::cout<<"\033[32m start function interpreter (constructor) \033[0m"<<std::endl;
#endif

    //uart = new UARTClass("/dev/ttyAMA0");
    //std::cout<<"tty path:";
    //std::string path;
    //std::cin>>path;
    //std::cout<<std::endl;

    uart = new UARTClass("/dev/ttyUSB0");
    //std::thread fails(failSave);
    //fails.detach();

#ifdef fulldebug
    std::cout<<"\033[31m end function interpreter (constructor) \033[0m"<<std::endl;
#endif
}

interpreter::~interpreter()
{
    stopFailSaveThread();
    delete uart;
}

void interpreter::startRoomba()
{
#ifdef fulldebug
    std::cout<<"\033[32m start function startRoomba \033[0m"<<std::endl;
#endif

    uart->sendUart(roomba::Start);
    uart->sendUart(roomba::fullMode);

#ifdef fulldebug
    std::cout<<"\033[31m end function startRoomba\033[0m"<<std::endl;
#endif

}

void interpreter::stopRoomba()
{
	uart->sendUart(roomba::Stop);
    uart->sendUart(roomba::playSong);
}

void interpreter::brushes(int brush)
{
#ifdef fulldebug
    std::cout<<"start function brushes"<<std::endl;
#endif
    switch (brush) {
    case 0: // no brush

        uart->sendUart(roomba::brushes);
        uart->sendUart(0b00000000);
        break;
    case 1: // side brush

        uart->sendUart(roomba::brushes);
        uart->sendUart(0b00000001);
        break;
    case 2: // main brush

        uart->sendUart(roomba::brushes);
        uart->sendUart(0b00000100);
        break;
    case 3: // side and main brush

        uart->sendUart(roomba::brushes);
        uart->sendUart(0b00000101);
        break;
    default:
        break;
    }
#ifdef fulldebug
    std::cout<<"end function brushes"<<std::endl;
#endif
} // werkt perfect


void interpreter::drives(int s)
{
#ifdef fulldebug
    std::cout<<"start function drives"<<std::endl;
#endif
    uart->sendUart(roomba::drive);
    switch (s) {
    case 0: //slow
        uart->sendUart(0x00); // Velocity high byte
        uart->sendUart(0x7F); // Velocity low  byte
        uart->sendUart(0x80); // Radius high byte
        uart->sendUart(0x00); // Radius low  byte
        break;
    case 1: //middle
        uart->sendUart(0x08); // Velocity high byte
        uart->sendUart(0x00); // Velocity low  byte
        uart->sendUart(0x80); // Radius high byte
        uart->sendUart(0x00); // Radius low  byte
        break;
    case 2: //fast (dont use)
        uart->sendUart(0x7F); // Velocity high byte
        uart->sendUart(0xFF); // Velocity low  byte
        uart->sendUart(0x80); // Radius high byte
        uart->sendUart(0x00); // Radius low  byte
        break;
    case 3: // stop
        uart->sendUart(0x00);
        uart->sendUart(0x00);
        uart->sendUart(0x00);
        uart->sendUart(0x00);
    case 4: // backwards
        uart->sendUart(0xFF);
        uart->sendUart(0x81);
        uart->sendUart(0x80);
        uart->sendUart(0x00);
    }
#ifdef fulldebug
    std::cout<<"end function drives"<<std::endl;
#endif
}

void interpreter::turnRoomba(int16_t angle)
{
#ifdef fulldebug
    std::cout<<"start function turnRoomba"<<std::endl;
#endif

    //uart->sendUart(roomba::Stop);   // stop roomba
    uint16_t i = getAngle();          // reset angle

#ifdef debug
    std::cout<<"got angle: "<<i<<std::endl;
#endif

    int16_t currentAngle = 0;
    uart->sendUart(roomba::drive);
    if(angle < 0) // counter clockwise
    {

#ifdef debug
    std::cout<<"counter clockwise"<<std::endl;
#endif

        uart->sendUart(0x00); // Velocity high byte
        uart->sendUart(0x7F); // Velocity low  byte
        uart->sendUart(0x00); // Radius high byte
        uart->sendUart(0x01); // Radius low  byte

        while(1)
        {
            currentAngle += getAngle();

#ifdef debug
    std::cout<<"Angle is: "<<currentAngle<<std::endl;
#endif

            if(currentAngle > angle)
            {
                uart->sendUart(roomba::Stop);
                break;
            }

        }
    }
    if(angle > 0) // clockwise
    {

#ifdef debug
    std::cout<<"clockwise"<<std::endl;
#endif

        uart->sendUart(0x00); // Velocity high byte
        uart->sendUart(0x7F); // Velocity low  byte
        uart->sendUart(0xFF); // Radius high byte
        uart->sendUart(0xFF); // Radius low  byte

        while(1)
        {
            currentAngle += getAngle();

#ifdef debug
    std::cout<<"Angle is: "<<currentAngle<<std::endl;
#endif

            if(currentAngle < angle)
            {
                uart->sendUart(roomba::Stop);
                break;
            }
        }
    }
#ifdef fulldebug
    std::cout<<"end function turnRoomba"<<std::endl;
#endif
}

void interpreter::failSave()
{
    while(1)
    {
        if(stopFailSave)break;


        /* check critical sensors and intervene if neccesary */
        using namespace roomba;

        uart->sendUart(bumpAndWheel);
        if(uart->receiveUart())
        {
            uart->sendUart(Stop);
        }

        uart->sendUart(cliffLeftSignal);
        if(uart->receiveUart() > 2048)
        {
            uart->sendUart(Stop);
        }

        uart->sendUart(cliffFrontLeftSignal);
        if(uart->receiveUart() > 2048)
        {
            uart->sendUart(Stop);
        }

        uart->sendUart(cliffFrontRightSignal);
        if(uart->receiveUart() > 2048)
        {
            uart->sendUart(Stop);
        }

        uart->sendUart(cliffRightSignal);
        if(uart->receiveUart() > 2048)
        {
            uart->sendUart(Stop);
        }

        uart->sendUart(wheelOvercurrents);
        if(uart->receiveUart())
        {
            uart->sendUart(Stop);
        }

        uart->sendUart(batteryCapacity);
        uint16_t cap = uart->receiveUart();
        uart->sendUart(batteryCharge);
        uint16_t charg = uart->receiveUart();
        if((cap/charg*100) < 10)
        {
            uart->sendUart(Stop); // stop roomba when battery is under 10%
        }



        //std::this_thread::sleep_for(interval);
    }

}

bool interpreter::getBumpAndWheel()
{
#ifdef fulldebug
    std::cout<<"start function getBumpAndWheel"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::bumpAndWheel);
    bool tmp = (uart->receiveUart() ? 1 : 0);

#ifdef fulldebug
    std::cout<<"end function getBumpAndWheel"<<std::endl;
#endif
    return tmp;
}

uint8_t interpreter::getWall()
{
#ifdef fulldebug
    std::cout<<"start function getWall"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::wall);
    uint8_t tmp = uart->receiveUart();

#ifdef fulldebug
    std::cout<<"end function getWall"<<std::endl;
#endif
    return tmp;
}

uint8_t interpreter::getCliffLeft()
{
#ifdef fulldebug
    std::cout<<"start function getCliffLeft"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::cliffLeft);
    uint8_t tmp = uart->receiveUart();

#ifdef fulldebug
    std::cout<<"end function getCliffLeft"<<std::endl;
#endif
    return tmp;
}

uint8_t interpreter::getCliffFrontLeft()
{
#ifdef fulldebug
    std::cout<<"start function getCliffFrontLeft"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::cliffFrontLeft);
    uint8_t tmp = uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getCliffFrontLeft"<<std::endl;
#endif
    return tmp;
}

uint8_t interpreter::getCliffFrontRight()
{
#ifdef fulldebug
    std::cout<<"start function getCliffFrontRight"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::cliffFrontRight);
    uint8_t tmp = uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getCliffFrontRight"<<std::endl;
#endif
    return tmp;
}

uint8_t interpreter::getCliffRight()
{
#ifdef fulldebug
    std::cout<<"start function getCliffRight"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::cliffRight);
    uint8_t tmp = uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getCliffRight"<<std::endl;
#endif
    return tmp;
}

uint8_t interpreter::getVirtualWall()
{
#ifdef fulldebug
    std::cout<<"start function getVirtualWall"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::virtualWall);
    uint8_t tmp = uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getVirtualWall"<<std::endl;
#endif
    return tmp;
}

bool interpreter::getWheelOvercurrents()
{
#ifdef fulldebug
    std::cout<<"start function getWheelOvercurrents"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::wheelOvercurrents);
    bool tmp = (uart->receiveUart() ? 1 : 0);
#ifdef fulldebug
    std::cout<<"end function getWheelOvercurrents"<<std::endl;
#endif
    return tmp;
}

uint8_t interpreter::getDirtDetect()
{
#ifdef fulldebug
    std::cout<<"start function getDirtDetect"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::dirtDetect);
    uint8_t tmp = uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getDirtDetect"<<std::endl;
#endif
    return tmp;
}

uint8_t interpreter::getIrReceiver()
{
#ifdef fulldebug
    std::cout<<"start function getIrReceiver"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::irReceiver);
    uint8_t tmp = uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getIrReceiver"<<std::endl;
#endif
    return tmp;
}

int16_t interpreter::getDistance()
{
#ifdef fulldebug
    std::cout<<"Start function getDistance"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::distance);
    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getDistance"<<std::endl;
#endif
    return halfWord;
}

int16_t interpreter::getAngle() /*******************************************************************/
{
#ifdef fulldebug
    std::cout<<"\033[32m start function getAngle\033[0m"<<std::endl;
#endif

    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::angle);

    volatile uint16_t halfWord = 0;
    volatile uint8_t highByte = 0;
    volatile uint8_t lowByte = 0;

    highByte = uart->receiveUart();

#ifdef debug
    std::cout<<"In function getAngle, highByte is: "<<std::hex<<highByte<<std::endl;
#endif

    lowByte = uart->receiveUart();

#ifdef debug
    std::cout<<"In function getAngle, lowByte is: "<<std::hex<<lowByte<<std::endl;
#endif

    halfWord = highByte <<8;
    halfWord |= lowByte;

#ifdef debug
    std::cout<<"In function getAngle, halfword is: "<<std::hex<<halfWord<<std::endl;
#endif

#ifdef fulldebug
    std::cout<<"\033[31m end function getAngle\033[0m"<<std::endl;
#endif
    return halfWord;
}/***************************************************************************************************/

uint8_t interpreter::getChargingState()
{
#ifdef fulldebug
    std::cout<<"start function getChargingState"<<std::endl;
#endif

    uart->sendUart(roomba::chargingState);
    uint8_t tmp = uart->receiveUart();

#ifdef fulldebug
    std::cout<<"\033[31m end function getChargingState\033[0m"<<std::endl;
#endif
    return tmp;
}

uint16_t interpreter::getBatteryVoltage()
{
#ifdef fulldebug
    std::cout<<"start function getBatteryVoltage"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::batteryVoltage);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getBatteryVoltage"<<std::endl;
#endif
    return halfWord;
}

int16_t interpreter::getBatteryCurrent()
{
#ifdef fulldebug
    std::cout<<"start function getBatteryCurrent"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
   uart->sendUart(roomba::batteryCurrent);

   uint16_t halfWord = 0;
   halfWord = (uart->receiveUart() << 8);
   halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getBatteryCurrent"<<std::endl;
#endif
   return halfWord;
}

int8_t interpreter::getBatteryTemperature()
{
#ifdef fulldebug
    std::cout<<"start function getBatteryTemperature"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::batteryTemperature);
    int8_t tmp = uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getBatteryTemperature"<<std::endl;
#endif
    return tmp;
}

uint16_t interpreter::getBatteryCharge()
{
#ifdef fulldebug
    std::cout<<"start function getBatteryCharge"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::batteryCharge);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getBatteryCharge"<<std::endl;
#endif
    return halfWord;
}

uint16_t interpreter::getBatteryCapacity()
{
#ifdef fulldebug
    std::cout<<"start function getBatteryCapacity"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::batteryCapacity);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getBatteryCapacity"<<std::endl;
#endif
    return halfWord;
}

uint16_t interpreter::getWallSignal()
{
#ifdef fulldebug
    std::cout<<"start function getWallSignal"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::wallSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getWallSignal"<<std::endl;
#endif
    return halfWord;
}

uint16_t interpreter::getCliffLeftSignal()
{
#ifdef fulldebug
    std::cout<<"start function getCliffLeftSignal"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::cliffLeftSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getCliffLeftSignal"<<std::endl;
#endif
    return halfWord;
}

uint16_t interpreter::getCliffFrontLeftSignal()
{
#ifdef fulldebug
    std::cout<<"start function getCliffFrontLeftSignal"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::cliffFrontLeftSignal);

    uint16_t halfWord;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getCliffFrontLeftSignal"<<std::endl;
#endif
    return halfWord;
}

uint16_t interpreter::getCliffFrontRightSignal()
{
#ifdef fulldebug
    std::cout<<"start function getCliffFrontRightSignal"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::cliffFrontRightSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getCliffFrontRightSignal"<<std::endl;
#endif
    return halfWord;
}

uint16_t interpreter::getCliffRightSignal()
{
#ifdef fulldebug
    std::cout<<"start function getCliffRightSignal"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::cliffRightSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getCliffRightSignal"<<std::endl;
#endif
    return halfWord;
}

uint8_t interpreter::getChargingSource()
{
#ifdef fulldebug
    std::cout<<"start function getChargingSource"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::chargingSource);
    uint8_t tmp = uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getChargingSource"<<std::endl;
#endif
    return tmp;
}

uint8_t interpreter::getOiMode()
{
#ifdef fulldebug
    std::cout<<"start function getOiMode"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::oiMode);
    uint8_t tmp = uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getOiMode"<<std::endl;
#endif
    return tmp;
}

uint8_t interpreter::getSongNumber()
{
#ifdef fulldebug
    std::cout<<"start function getSongNumber"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::songNumber);
    uint8_t tmp = uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getSongNumber"<<std::endl;
#endif
    return tmp;
}

uint8_t interpreter::getSongPlaying()
{
#ifdef fulldebug
    std::cout<<"start function getSongPlaying"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::songPlaying);
    uint8_t tmp = uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getSongPlaying"<<std::endl;
#endif
    return tmp;
}

int16_t interpreter::getRequestedVelocity()
{
#ifdef fulldebug
    std::cout<<"start function getRequestedVelocity"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::requestedVelocity);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getRequestedVelocity"<<std::endl;
#endif
    return halfWord;
}

int16_t interpreter::getRequestedRadius()
{
#ifdef fulldebug
    std::cout<<"start function getRequestedRadius"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::requestedRadius);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getRequestedRadius"<<std::endl;
#endif
    return halfWord;
}

int16_t interpreter::getRequestedRightVelocity()
{
#ifdef fulldebug
    std::cout<<"start function getRequestedRightVelocity"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::requestedRightVelocity);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getRequestedRightVelocity"<<std::endl;
#endif
    return halfWord;
}

int16_t interpreter::getRequestedLeftVelocity()
{
#ifdef fulldebug
    std::cout<<"start function getRequestedLeftVelocity"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::requestedLeftVelocity);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getRequestedLeftVelocity"<<std::endl;
#endif
    return halfWord;
}

uint16_t interpreter::getLeftEncoderCount()
{
#ifdef fulldebug
    std::cout<<"start function getLeftEncoderCount"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::leftEncoderCount);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getLeftEncoderCount"<<std::endl;
#endif
    return halfWord;
}

uint16_t interpreter::getRightEncoderCount()
{
#ifdef fulldebug
    std::cout<<"start function getRightEncoderCount"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::rightEncoderCount);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getRightEncoderCount"<<std::endl;
#endif
    return halfWord;
}

bool interpreter::getLightBumper()
{
#ifdef fulldebug
    std::cout<<"start function getLightBumper"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::lightBumper);
    bool tmp = (uart->receiveUart() ? 1 : 0);
#ifdef fulldebug
    std::cout<<"end function getLightBumper"<<std::endl;
#endif
    return tmp;
}

uint16_t interpreter::getLightBumpLeftSignal()
{
#ifdef fulldebug
    std::cout<<"start function getLightBumpLeftSignal"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::lightBumpLeftSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getLightBumpLeftSignal"<<std::endl;
#endif
    return halfWord;
}

uint16_t interpreter::getLightBumpFrontLeftSignal()
{
#ifdef fulldebug
    std::cout<<"start function getLightBumpFrontLeftSignal"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::lightBumpFrontLeftSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getLightBumpFrontLeftSignal"<<std::endl;
#endif
    return halfWord;
}

uint16_t interpreter::getLightBumpCenterLeftSignal()
{
#ifdef fulldebug
    std::cout<<"start function getLightBumpCenterLeftSignal"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::lightBumpCenterLeftSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getLightBumpCenterLeftSignal"<<std::endl;
#endif
    return halfWord;
}

uint16_t interpreter::getLightBumpCenterRightSignal()
{
#ifdef fulldebug
    std::cout<<"start function getLightBumpCenterRightSignal"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::lightBumpCenterRightSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getLightBumpCenterRightSignal"<<std::endl;
#endif
    return halfWord;
}

uint16_t interpreter::getLightBumpFrontRightSignal()
{
#ifdef fulldebug
    std::cout<<"start function getLightBumpFrontRightSignal"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::lightBumpFrontRightSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getLightBumpFrontRightSignal"<<std::endl;
#endif
    return halfWord;
}

uint16_t interpreter::getLightBumpRightSignal()
{
#ifdef fulldebug
    std::cout<<"start function getLightBumpRightSignal"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::lightBumpRightSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getLightBumpRightSignal"<<std::endl;
#endif
    return halfWord;
}

int16_t interpreter::getLeftMotorCurrent()
{
#ifdef fulldebug
    std::cout<<"start function getLeftMotorCurrent"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::leftMotorCurrent);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getLeftMotorCurrent"<<std::endl;
#endif
    return halfWord;
}

int16_t interpreter::getRightMotorCurrent()
{
#ifdef fulldebug
    std::cout<<"start function getRightMotorCurrent"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::rightMotorCurrent);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getRightMotorCurrent"<<std::endl;
#endif
    return halfWord;
}

int16_t interpreter::getMainBrushMotorCurrent()
{
#ifdef fulldebug
    std::cout<<"start function getMainBrushMotorCurrent"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::mainBrushMotorCurrent);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getMainBrushMotorCurrent"<<std::endl;
#endif
    return halfWord;
}

int16_t interpreter::getSideBrushMotorCurrent()
{
#ifdef fulldebug
    std::cout<<"start function getSideBrushMotorCurrent"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::sideBrushMotorCurrent);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getSideBrushMotorCurrent"<<std::endl;
#endif
    return halfWord;
}

uint8_t interpreter::getStatis()
{
#ifdef fulldebug
    std::cout<<"start function getStatis"<<std::endl;
#endif
    uart->sendUart(0x95);
    uart->sendUart(0x01);
    uart->sendUart(roomba::statis);
    uint8_t tmp = uart->receiveUart();
#ifdef fulldebug
    std::cout<<"end function getStatis"<<std::endl;
#endif
    return tmp;
}


/***********************************************************/
bool interpreter::getBumpRight()
{

    uart->sendUart(roomba::bumpAndWheel);
    bool tmp = (uart->receiveUart() & 0b00000001) == 0b00000001 ? 1 : 0;

    return tmp;
}

bool interpreter::getBumpLeft()
{

    uart->sendUart(roomba::bumpAndWheel);
    bool tmp = (uart->receiveUart() & 0b00000010) == 0b00000010 ? 1 : 0;

    return tmp;
}

bool interpreter::getWheelDropRight()
{

    uart->sendUart(roomba::bumpAndWheel);
    bool tmp = (uart->receiveUart() & 0b00000100) == 0b00000100 ? 1 : 0;

    return tmp;
}

bool interpreter::getWheelDropLeft()
{

    uart->sendUart(roomba::bumpAndWheel);
    bool tmp = (uart->receiveUart() & 0b00001000) == 0b00001000 ? 1 : 0;

    return tmp;
}

bool interpreter::getSideBrushOvercurrent()
{

    uart->sendUart(roomba::wheelOvercurrents);
    bool tmp = (uart->receiveUart() & 0b00000001) == 0b00000001 ? 1 : 0;

    return tmp;
}

bool interpreter::getMainBrushOvercurrent()
{

    uart->sendUart(roomba::wheelOvercurrents);
    bool tmp = (uart->receiveUart() & 0b00000100) == 0b00000100 ? 1 : 0;

    return tmp;
}

bool interpreter::getRightWheelOvercurrent()
{

    uart->sendUart(roomba::wheelOvercurrents);
    bool tmp = (uart->receiveUart() & 0b00001000) == 0b00001000 ? 1 : 0;

    return tmp;
}

bool interpreter::getLeftWheelOvercurrent()
{

    uart->sendUart(roomba::wheelOvercurrents);
    bool tmp = (uart->receiveUart() & 0b00010000) == 0b00010000 ? 1 : 0;

    return tmp;

}

void interpreter::startAutoMode()
{
    //AUTO = std::thread(&interpreter::autoMode);
    //AUTO.detach();
}

void interpreter::autoMode()
{
    uint8_t received;
    interpreter::autoRunning = true;

    while(autoRunning)
    {
        // bump and wheel functions
        uart->sendUart(0x95);
        uart->sendUart(0x01);
        uart->sendUart(roomba::bumpAndWheel);
        received = uart->receiveUart();
        this->Bumps.bRight      = received && 0b00000001 == 0b00000001 ? true : false;
        this->Bumps.bLeft       = received && 0b00000010 == 0b00000010 ? true : false;
        this->WheelDrops.bRight = received && 0b00000100 == 0b00000100 ? true : false;
        this->WheelDrops.bLeft  = received && 0b00001000 == 0b00001000 ? true : false;

        // overcurrent functions
        uart->sendUart(0x95);
        uart->sendUart(0x01);
        uart->sendUart(roomba::wheelOvercurrents);
        received = uart->receiveUart();
        this->OverCurrent.bSideBrush  = received && 0b00000001 == 0b00000001 ? true : false;
        this->OverCurrent.bMainBrush  = received && 0b00000100 == 0b00000100 ? true : false;
        this->OverCurrent.bWheelRight = received && 0b00001000 == 0b00001000 ? true : false;
        this->OverCurrent.bWheelLeft  = received && 0b00010000 == 0b00010000 ? true : false;

        // cliff functions
        uart->sendUart(0x95);
        uart->sendUart(0x01);
        uart->sendUart(roomba::cliffLeft);
        this->Cliff.bLeft = uart->receiveUart() ? true : false;
        uart->sendUart(roomba::cliffRight);
        this->Cliff.bRight = uart->receiveUart() ? true : false;
        uart->sendUart(roomba::cliffFrontLeft);
        this->Cliff.bFrontLeft = uart->receiveUart() ? true : false;
        uart->sendUart(roomba::cliffFrontRight);
        this->Cliff.bFrontRight = uart->receiveUart() ? true : false;

        // infrared functions
        uart->sendUart(0x95);
        uart->sendUart(0x01);
        uart->sendUart(roomba::irReceiver);
        switch (uart->receiveUart()) {
        case roomba::charger::Red:
            this->InfraRed.bLeft  = true;
            this->InfraRed.bRight = false;
            this->InfraRed.bClose = false;
            break;
        case roomba::charger::Green:
            this->InfraRed.bLeft  = false;
            this->InfraRed.bRight = true;
            this->InfraRed.bClose = false;
            break;
        case roomba::charger::RedAndGreen:
            this->InfraRed.bLeft  = true;
            this->InfraRed.bRight = true;
            this->InfraRed.bClose = false;
            break;
        case roomba::charger::RedAndForceField:
            this->InfraRed.bLeft  = true;
            this->InfraRed.bRight = false;
            this->InfraRed.bClose = true;
            break;
        case roomba::charger::GreenAndForField:
            this->InfraRed.bLeft  = false;
            this->InfraRed.bRight = true;
            this->InfraRed.bClose = true;
            break;
        case roomba::charger::RedGreenAndForceField:
            this->InfraRed.bLeft  = true;
            this->InfraRed.bRight = true;
            this->InfraRed.bClose = true;
            break;
        default:
            this->InfraRed.bLeft  = false;
            this->InfraRed.bRight = false;
            this->InfraRed.bClose = false;
            break;
        }
        // wall signal functions
        uart->sendUart(0x95);
        uart->sendUart(0x01);
        uart->sendUart(roomba::lightBumper);
        received = uart->receiveUart();
        this->Wall.bLeft        = received && 0b00000001 == 0b00000001 ? true : false;
        this->Wall.bFrontLeft   = received && 0b00000010 == 0b00000010 ? true : false;
        this->Wall.bCenterLeft  = received && 0b00000100 == 0b00000100 ? true : false;
        this->Wall.bCenterRight = received && 0b00001000 == 0b00001000 ? true : false;
        this->Wall.bFrontRight  = received && 0b00010000 == 0b00010000 ? true : false;
        this->Wall.bRight       = received && 0b00100000 == 0b00100000 ? true : false;

        system("clear");
        std::cout << "Left Wheel drop:          " << this->WheelDrops.bLeft << std::endl;
        std::cout << "Right Wheel drop:         " << this->WheelDrops.bRight << std::endl;
        std::cout << "Left Wheel overcurrent:   " << this->OverCurrent.bWheelLeft << std::endl;
        std::cout << "Right Wheel overcurrent:  " << this->OverCurrent.bWheelRight << std::endl;
        std::cout << "Main brush overcurrent:   " << this->OverCurrent.bMainBrush << std::endl;
        std::cout << "Side brush overcurrent:   " << this->OverCurrent.bSideBrush << std::endl;
        std::cout << "Left Bumper:              " << this->Bumps.bLeft << std::endl;
        std::cout << "Right Bumper:             " << this->Bumps.bLeft << std::endl;
    }

}

void interpreter::stopFailSaveThread()
{
    stopFailSave = true;
}

