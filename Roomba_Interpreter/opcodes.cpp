#include "opcodes.h"

opcodes::opcodes()
{
    for(unsigned int i = 0; i < 58 ; ++i)
    {
        sensorWaarden[i]=0;
    }
    sensorWaarden[wheelOvercurrents] = 12;
}

void opcodes::print()
{
    for(unsigned int i = 0; i < 58 ; ++i)
    {

        std::cout<<"Senson no"<<i<<": "<< sensorWaarden[i]<<std::endl;
    }
}

void opcodes::startRoomba()
{
    sentUart(Start);
    sentUart(safeMode);
    sentUart(brushes);
}

void opcodes::receiveUart()
{
    while(blablaUart() != 19){}

    uint8_t nPackets = blablaUart();
    uint8_t checksum = 0;
    for(unsigned int i = nPackets ; i > 0 ; --i)
    {
        uint8_t code = blablaUart();
        checksum += code;
        std::vector<uint8_t> databytes;
        uint8_t data = 0;
        for(unsigned int i = howManyDatabytes(code) ; i > 0 ; --i)
        {
            uint8_t databyte = blablaUart();
            checksum += databyte;
            databytes.push_back(databyte);
        }
        checksum += blablaUart();
        if(checksum != 0)std::cout<<"error"<<std::endl;
        for(unsigned int i = 0; i < databytes.size(); i++)
        {
            data += databytes[i];
        }
        sensorWaarden[code] = data;
    }
}

uint8_t opcodes::getBumpAndWheel()
{
    /*if(sensorWaarden[bumpAndWheel] != 0) return 1;
    else return 0;*/
    return (sensorWaarden[bumpAndWheel] ? 1 : 0);
}

uint8_t opcodes::getWall()
{
    return sensorWaarden[wall];
}

uint8_t opcodes::getCliffLeft()
{
    return sensorWaarden[cliffLeft];
}

uint8_t opcodes::getCliffFrontLeft()
{
    return sensorWaarden[cliffFrontLeft];
}

uint8_t opcodes::getCliffFrontRight()
{
    return sensorWaarden[cliffFrontRight];
}

uint8_t opcodes::getCliffRight()
{
    return sensorWaarden[cliffRight];
}

uint8_t opcodes::getVirtualWall()
{
    return sensorWaarden[virtualWall];
}

uint8_t opcodes::getWheelOvercurrents()
{
    return (sensorWaarden[wheelOvercurrents] ? 1 : 0);
}

uint8_t opcodes::getDirtDetect()
{
    return sensorWaarden[dirtDetect];
}

uint8_t opcodes::getUnusedByte()
{
    return sensorWaarden[unusedByte];
}

uint8_t opcodes::getIrReceiver()
{
    return sensorWaarden[irReceiver];
}

uint8_t opcodes::getDistance()
{
    return sensorWaarden[distance];
}

uint8_t opcodes::getAngle()
{
    return sensorWaarden[angle];
}

uint8_t opcodes::getChargingState()
{
    return sensorWaarden[chargingState];
}

uint8_t opcodes::getBatteryVoltage()
{
    return sensorWaarden[batteryVoltage];
}

uint8_t opcodes::getBatteryCurrent()
{
    return sensorWaarden[batteryCurrent];
}

uint8_t opcodes::getBatteryTemperature()
{
    return sensorWaarden[batteryTemperature];
}

uint8_t opcodes::getBatteryCharge()
{
    return sensorWaarden[batteryCharge];
}

uint8_t opcodes::getBatteryCapacity()
{
    return sensorWaarden[batteryCapacity];
}

uint8_t opcodes::getWallSignal()
{
    return sensorWaarden[wallSignal];
}

uint8_t opcodes::getCliffLeftSignal()
{
    return sensorWaarden[cliffFrontLeftSignal];
}

uint8_t opcodes::getCliffFrontLeftSignal()
{
    return sensorWaarden[cliffFrontLeftSignal];
}

uint8_t opcodes::getCliffFrontRightSignal()
{
    return sensorWaarden[cliffFrontRightSignal];
}

uint8_t opcodes::getCliffRightSignal()
{
    return sensorWaarden[cliffRightSignal];
}

uint8_t opcodes::getChargingSource()
{
    return sensorWaarden[chargingSource];
}

uint8_t opcodes::getOiMode()
{
    return sensorWaarden[oiMode];
}

uint8_t opcodes::getSongNumber()
{
    return sensorWaarden[songNumber];
}

uint8_t opcodes::getSongPlaying()
{
    return sensorWaarden[songPlaying];
}

uint8_t opcodes::getNumberOfPackets()
{
    return sensorWaarden[numberOfPackets];
}

uint8_t opcodes::getRequestedVelocity()
{
    return sensorWaarden[requestedVelocity];
}

uint8_t opcodes::getRequestedRadius()
{
    return sensorWaarden[requestedRadius];
}

uint8_t opcodes::getRequestedRightVelocity()
{
    return sensorWaarden[requestedRightVelocity];
}

uint8_t opcodes::getRequestedLeftVelocity()
{
    return sensorWaarden[requestedLeftVelocity];
}

uint8_t opcodes::getLeftEncoderCount()
{
    return sensorWaarden[leftEncoderCount];
}

uint8_t opcodes::getRightEncoderCount()
{
    return sensorWaarden[rightEncoderCount];
}

uint8_t opcodes::getLightBumper()
{
    //return sensorWaarden[lightBumper] ? 1 : 0;
    return sensorWaarden[lightBumper];
}

uint8_t opcodes::getLightBumpLeftSignal()
{
    return sensorWaarden[lightBumpLeftSignal];
}

uint8_t opcodes::getLightBumpFrontLeftSignal()
{
    return sensorWaarden[lightBumpFrontLeftSignal];
}

uint8_t opcodes::getLightBumpCenterLeftSignal()
{
    return sensorWaarden[lightBumpCenterLeftSignal];
}

uint8_t opcodes::getLightBumpCenterRightSignal()
{
    return sensorWaarden[lightBumpCenterRightSignal];
}

uint8_t opcodes::getLightBumpFrontRightSignal()
{
    return  sensorWaarden[lightBumpFrontRightSignal];
}

uint8_t opcodes::getLightBumperRightSignal()
{
    return sensorWaarden[lightBumperRightSignal];
}

uint8_t opcodes::getLeftMotorCurrent()
{
    return sensorWaarden[leftMotorCurrent];
}

uint8_t opcodes::getRightMotorCurrent()
{
    return sensorWaarden[rightMotorCurrent];
}

uint8_t opcodes::getMainBrushMotorCurrent()
{
    return sensorWaarden[mainBrushMotorCurrent];
}

uint8_t opcodes::getSideBrushMotorCurrent()
{
    return sensorWaarden[sideBrushMotorCurrent];
}

uint8_t opcodes::getStatis()
{
    return sensorWaarden[statis];
}

uint8_t opcodes::getBumpRight()
{
    return (sensorWaarden[bumpAndWheel] & 0b00000001) == 0b00000001 ? 1 : 0;
}

uint8_t opcodes::getBumpLeft()
{
    return (sensorWaarden[bumpAndWheel] & 0b00000010) == 0b00000010 ? 1 : 0;
}

uint8_t opcodes::getWheelDropRight()
{
    return (sensorWaarden[bumpAndWheel] & 0b00000100) == 0b00000100 ? 1 : 0;
}

uint8_t opcodes::getWheelDropLeft()
{
    return (sensorWaarden[bumpAndWheel] & 0b00001000) == 0b00001000 ? 1 : 0;
}

uint8_t opcodes::getSideBrushOvercurrent()
{
    return (sensorWaarden[wheelOvercurrents] & 0b00000001) == 0b00000001 ? 1 : 0;
}

uint8_t opcodes::getMainBrushOvercurrent()
{
    return (sensorWaarden[wheelOvercurrents] & 0b00000100) == 0b00000100 ? 1 : 0;
}

uint8_t opcodes::getRightWheelOvercurrent()
{
    return (sensorWaarden[wheelOvercurrents] & 0b00001000) == 0b00001000 ? 1 : 0;
}

uint8_t opcodes::getLeftWheelOvercurrent()
{
    return (sensorWaarden[wheelOvercurrents] & 0b00010000) == 0b00010000 ? 1 : 0;
}

void opcodes::sentUart(uint8_t)
{

}

void opcodes::startUart()
{
    /*
    //-------------------------
    //----- SETUP USART 0 -----
    //-------------------------
    //At bootup, pins 8 and 10 are already set to UART0_TXD, UART0_RXD (ie the alt0 function) respectively
    int uart0_filestream = -1;

    //OPEN THE UART
    //The flags (defined in fcntl.h):
    //	Access modes (use 1 of these):
    //		O_RDONLY - Open for reading only.
    //		O_RDWR - Open for reading and writing.
    //		O_WRONLY - Open for writing only.
    //
    //	O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
    //											if there is no input immediately available (instead of blocking). Likewise, write requests can also return
    //											immediately with a failure status if the output can't be written immediately.
    //
    //	O_NOCTTY - When set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process.
    uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode
    if (uart0_filestream == -1)
    {
        //ERROR - CAN'T OPEN SERIAL PORT
        printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
    }

    //CONFIGURE THE UART
    //The flags (defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
    //	Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
    //	CSIZE:- CS5, CS6, CS7, CS8
    //	CLOCAL - Ignore modem status lines
    //	CREAD - Enable receiver
    //	IGNPAR = Ignore characters with parity errors
    //	ICRNL - Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters - don't use for bianry comms!)
    //	PARENB - Parity enable
    //	PARODD - Odd parity (else even)
    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;		//<Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);*/

    /*std::thread uart(receiveUart);
    uart.detach();*/
}

uint8_t opcodes::howManyDatabytes(uint8_t code)
{
    switch(code)
    {
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 21:
        case 24:
        case 32:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 45:
        case 52:
        case 53:
        case 58:
            return 1;
            break;
        default:
            return 2;
        break;
    }
}

uint8_t opcodes::blablaUart()
{
    /******************************************/
    /* dit bootst een stream van de roomba na */
    /******************************************/
    switch(c)
    {
        case 0:
            return 19;
            c++;
            break;
        case 1:
            return 7; // n-bytes
            c++;
            break;
        case 2:
            return 8; // wall sensor
            c++;
            break;
        case 3:
            return 0; // no wall
            c++;
            break;
        case 4:
            return 12; // cliff right
            c++;
            break;
        case 5:
            return 1; // cliff right detected
            c++;
            break;
        case 6:
            return 48; // light bump left
            c++;
            break;
        case 7:
            return 30; // lightbump lowbyte
            c++;
            break;
        case 8:
            return 160; // lightbump highbyte
            c++;
            break;
        case 9:
            return -266; // checksum
            c = 0;
        default:
            c = 0;
    }
}
