#include "opcodes.h"


opcodes::opcodes()
{
    FailSave = new failsave;
    uart = new Uart;
}

opcodes::~opcodes()
{
    FailSave->stopFailsave();
    delete FailSave;
    delete uart;
}

void opcodes::startRoomba()
{
    uart->sendUart(Start);
    uart->sendUart(safeMode);
    uart->sendUart(brushes);
}

void opcodes::drives(speed s)
{
    uart->sendUart(drive);
    switch (s) {
    case SLOW:
        uart->sendUart(0x10); // Velocity high byte
        uart->sendUart(0x00); // Velocity low  byte
        uart->sendUart(0x80); // Radius high byte
        uart->sendUart(0x00); // Radius low  byte
        break;
    case CRUISE:
        uart->sendUart(0x08); // Velocity high byte
        uart->sendUart(0x00); // Velocity low  byte
        uart->sendUart(0x80); // Radius high byte
        uart->sendUart(0x00); // Radius low  byte
        break;
    case FAST: //2's complement is a bitch
        uart->sendUart(0x0F); // Velocity high byte
        uart->sendUart(0xFF); // Velocity low  byte
        uart->sendUart(0x80); // Radius high byte
        uart->sendUart(0x00); // Radius low  byte
        break;
    }
}

void opcodes::turnRoomba(angles a)
{
    uint8_t currentAngle = getAngle();
    uart->sendUart(drive);
    switch (a) {
    case RIGHT:
        uart->sendUart(0x00); // Velocity high byte
        uart->sendUart(0x00); // Velocity low  byte
        uart->sendUart(0xFF); // Radius high byte
        uart->sendUart(0xFF); // Radius low  byte

        while(1)
        {
            currentAngle += getAngle();
            if(currentAngle == RIGHT)
            {
                uart->sendUart(Stop);
                break;
            }
        }

        break;
    case LEFT:
        uart->sendUart(0x00); // Velocity high byte
        uart->sendUart(0x00); // Velocity low  byte
        uart->sendUart(0x00); // Radius high byte
        uart->sendUart(0x01); // Radius low  byte

        while(1)
        {
            currentAngle += getAngle();
            if(currentAngle == LEFT)
            {
                uart->sendUart(Stop);
                break;
            }
        }

        break;
    }


}

bool opcodes::getBumpAndWheel()
{
    uart->sendUart(bumpAndWheel);
    return (uart->receiveUart() ? 1 : 0);
}

uint8_t opcodes::getWall()
{
    uart->sendUart(wall);
    return uart->receiveUart();
}

uint8_t opcodes::getCliffLeft()
{
    uart->sendUart(cliffLeft);
    return uart->receiveUart();
}

uint8_t opcodes::getCliffFrontLeft()
{
    uart->sendUart(cliffFrontLeft);
    return uart->receiveUart();
}

uint8_t opcodes::getCliffFrontRight()
{
    uart->sendUart(cliffFrontRight);
    return uart->receiveUart();
}

uint8_t opcodes::getCliffRight()
{
    uart->sendUart(cliffRight);
    return uart->receiveUart();
}

uint8_t opcodes::getVirtualWall()
{
    uart->sendUart(virtualWall);
    return uart->receiveUart();
}

bool opcodes::getWheelOvercurrents()
{
    uart->sendUart(wheelOvercurrents);
    return (uart->receiveUart() ? 1 : 0);
}

uint8_t opcodes::getDirtDetect()
{
    uart->sendUart(dirtDetect);
    return uart->receiveUart();
}

uint8_t opcodes::getIrReceiver()
{
    uart->sendUart(irReceiver);
    return uart->receiveUart();
}

int16_t opcodes::getDistance()
{
    uart->sendUart(distance);
    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

int16_t opcodes::getAngle()
{
    uart->sendUart(angle);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint8_t opcodes::getChargingState()
{
    uart->sendUart(chargingState);
    return uart->receiveUart();
}

uint16_t opcodes::getBatteryVoltage()
{
    uart->sendUart(batteryVoltage);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

int16_t opcodes::getBatteryCurrent()
{
   uart->sendUart(batteryCurrent);

   uint16_t halfWord = 0;
   halfWord = (uart->receiveUart() << 8);
   halfWord |= uart->receiveUart();
   return halfWord;
}

int8_t opcodes::getBatteryTemperature()
{
    uart->sendUart(batteryTemperature);
    return uart->receiveUart();
}

uint16_t opcodes::getBatteryCharge()
{
    uart->sendUart(batteryCharge);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint16_t opcodes::getBatteryCapacity()
{
    uart->sendUart(batteryCapacity);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint16_t opcodes::getWallSignal()
{
    uart->sendUart(wallSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint16_t opcodes::getCliffLeftSignal()
{
    uart->sendUart(cliffLeftSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint16_t opcodes::getCliffFrontLeftSignal()
{
    uart->sendUart(cliffFrontLeftSignal);

    uint16_t halfWord;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint16_t opcodes::getCliffFrontRightSignal()
{
    uart->sendUart(cliffFrontRightSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint16_t opcodes::getCliffRightSignal()
{
    uart->sendUart(cliffRightSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint8_t opcodes::getChargingSource()
{
    uart->sendUart(chargingSource);
    return uart->receiveUart();
}

uint8_t opcodes::getOiMode()
{
    uart->sendUart(oiMode);
    return uart->receiveUart();
}

uint8_t opcodes::getSongNumber()
{
    uart->sendUart(songNumber);
    return uart->receiveUart();
}

uint8_t opcodes::getSongPlaying()
{
    uart->sendUart(songPlaying);
    return uart->receiveUart();
}

int16_t opcodes::getRequestedVelocity()
{
    uart->sendUart(requestedVelocity);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

int16_t opcodes::getRequestedRadius()
{
    uart->sendUart(requestedRadius);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

int16_t opcodes::getRequestedRightVelocity()
{
    uart->sendUart(requestedRightVelocity);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

int16_t opcodes::getRequestedLeftVelocity()
{
    uart->sendUart(requestedLeftVelocity);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint16_t opcodes::getLeftEncoderCount()
{
    uart->sendUart(leftEncoderCount);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint16_t opcodes::getRightEncoderCount()
{
    uart->sendUart(rightEncoderCount);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint8_t opcodes::getLightBumper()
{
    uart->sendUart(lightBumper);
    return (uart->receiveUart() ? 1 : 0);
}

uint16_t opcodes::getLightBumpLeftSignal()
{
    uart->sendUart(lightBumpLeftSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint16_t opcodes::getLightBumpFrontLeftSignal()
{
    uart->sendUart(lightBumpFrontLeftSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint16_t opcodes::getLightBumpCenterLeftSignal()
{
    uart->sendUart(lightBumpCenterLeftSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint16_t opcodes::getLightBumpCenterRightSignal()
{
    uart->sendUart(lightBumpCenterRightSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint16_t opcodes::getLightBumpFrontRightSignal()
{
    uart->sendUart(lightBumpFrontRightSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint16_t opcodes::getLightBumpRightSignal()
{
    uart->sendUart(lightBumpRightSignal);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

int16_t opcodes::getLeftMotorCurrent()
{
    uart->sendUart(leftMotorCurrent);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

int16_t opcodes::getRightMotorCurrent()
{
    uart->sendUart(rightMotorCurrent);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

int16_t opcodes::getMainBrushMotorCurrent()
{
    uart->sendUart(mainBrushMotorCurrent);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

int16_t opcodes::getSideBrushMotorCurrent()
{
    uart->sendUart(sideBrushMotorCurrent);

    uint16_t halfWord = 0;
    halfWord = (uart->receiveUart() << 8);
    halfWord |= uart->receiveUart();
    return halfWord;
}

uint8_t opcodes::getStatis()
{
    uart->sendUart(statis);
    return uart->receiveUart();
}


/***********************************************************/
bool opcodes::getBumpRight()
{

    return (sensorWaarden[bumpAndWheel] & 0b00000001) == 0b00000001 ? 1 : 0;
}

bool opcodes::getBumpLeft()
{
    return (sensorWaarden[bumpAndWheel] & 0b00000010) == 0b00000010 ? 1 : 0;
}

bool opcodes::getWheelDropRight()
{
    return (sensorWaarden[bumpAndWheel] & 0b00000100) == 0b00000100 ? 1 : 0;
}

bool opcodes::getWheelDropLeft()
{
    return (sensorWaarden[bumpAndWheel] & 0b00001000) == 0b00001000 ? 1 : 0;
}

bool opcodes::getSideBrushOvercurrent()
{
    return (sensorWaarden[wheelOvercurrents] & 0b00000001) == 0b00000001 ? 1 : 0;
}

bool opcodes::getMainBrushOvercurrent()
{
    return (sensorWaarden[wheelOvercurrents] & 0b00000100) == 0b00000100 ? 1 : 0;
}

bool opcodes::getRightWheelOvercurrent()
{
    return (sensorWaarden[wheelOvercurrents] & 0b00001000) == 0b00001000 ? 1 : 0;
}

bool opcodes::getLeftWheelOvercurrent()
{
    return (sensorWaarden[wheelOvercurrents] & 0b00010000) == 0b00010000 ? 1 : 0;
}

void opcodes::lockMutex()
{
    sendTex.lock();
}

void opcodes::unlockMutex()
{
    sendTex.unlock();
}


