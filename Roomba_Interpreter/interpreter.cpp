#include "interpreter.h"

bool interpreter::runThread;

interpreter::interpreter()
{
	interpreter::runThread = true;
    LOGsettings::file = "interpreter.log";

    LOG(DEBUG)<<"Start interpreter";
    uart = new UARTClass("/dev/ttyUSB0");
}

interpreter::~interpreter()
{
    stopFailSaveThread();
    delete uart;
    LOG(DEBUG)<<"End interpreter (destructor)";
}

void interpreter::startRoomba()
{

    //sendTex->lock();
    uart->sendUart(roomba::Start);
    uart->sendUart(roomba::modes::fullMode);
    LOG(INFO)<<"Roomba started in fullMode";
	usleep(200);
    brushes(roomba::brush::BOTH);
    //sendTex->unlock();
    

}

void interpreter::stopRoomba()
{
    //sendTex->lock();
    uart->sendUart(roomba::Stop);
    //sendTex->unlock();
    LOG(INFO)<<"Rooma stopped";
}

void interpreter::brushes(int brush)
{
    //sendTex->lock();
    switch (brush) {
    case roomba::brush::NOBRUSH: // no brush
        LOG(INFO) << "Brushes are turned off";
        uart->sendUart(roomba::brushes);
        uart->sendUart(roomba::brush::NOBRUSH);
        break;
    case roomba::brush::SIDEBRUSH: // side brush
        LOG(INFO) << "Sidebrush is activated";
        uart->sendUart(roomba::brushes);
        uart->sendUart(roomba::brush::SIDEBRUSH);
        break;
    case roomba::brush::MAINBRUSH: // main brush
        LOG(INFO) << "Mainbrush is activated";
        uart->sendUart(roomba::brushes);
        uart->sendUart(roomba::brush::MAINBRUSH);
        break;
    case roomba::brush::BOTH: // side and main brush
        LOG(INFO) << "Both brushes activated";
        uart->sendUart(roomba::brushes);
		usleep(10);
        uart->sendUart(roomba::brush::BOTH);
        break;
    default:
        break;
    }
    //sendTex->unlock();
} // werkt perfect


void interpreter::drives(int s)
{
    //sendTex->lock();
    uart->sendUart(roomba::drive);
    switch (s) {
    case roomba::speed::SLOW: //slow
        uart->sendUart(0x00); // Velocity high byte
        uart->sendUart(0x7F); // Velocity low  byte
        uart->sendUart(0x80); // Radius high byte
        uart->sendUart(0x00); // Radius low  byte
        LOG(INFO) << "Sent drive slow";
        break;
    case roomba::speed::CRUISE: //middle
        uart->sendUart(0x05); // Velocity high byte
        uart->sendUart(0x00); // Velocity low  byte
        uart->sendUart(0x80); // Radius high byte
        uart->sendUart(0x00); // Radius low  byte
        LOG(INFO) << "Sent drive cruise";
        break;
    case roomba::speed::FAST: // /////////schaal lager zetten
        uart->sendUart(0x7F); // Velocity high byte
        uart->sendUart(0xFF); // Velocity low  byte
        uart->sendUart(0x80); // Radius high byte
        uart->sendUart(0x00); // Radius low  byte
        LOG(WARN) << "Sent drive fast";
        break;
    case roomba::speed::STOP: // stop
        uart->sendUart(0x00);
        uart->sendUart(0x00);
        uart->sendUart(0x00);
        uart->sendUart(0x00);
        LOG(INFO) << "Sent drive stop";
        break;
    case roomba::speed::BACKWARDS: // backwards
        uart->sendUart(0xFF);
        uart->sendUart(0x81);
        uart->sendUart(0x80);
        uart->sendUart(0x00);
        LOG(INFO) << "Sent drive rearward";
        break;
    }
    //sendTex->unlock();
}
void interpreter::turnAndDrive(int speed, int radius) // define in header file, make enums for switches
{
    //sendTex->lock();
    uart->sendUart(roomba::drive);
    switch(speed){
        case roomba::speed::SLOW: //slow
        uart->sendUart(0x00);
        uart->sendUart(0x7F);
        LOG(INFO) << "Sent drive slow";
        break;
        case roomba::speed::CRUISE: //middle
        uart->sendUart(0x08);
        uart->sendUart(0x00);
        LOG(INFO) << "Sent drive cruise";
        break;
        case roomba::speed::FAST: //fast
        uart->sendUart(0x7F);
        uart->sendUart(0xFF);
        LOG(WARN) << "Sent drive fast";
        break;
        case roomba::speed::BACKWARDS: // backwards
        uart->sendUart(0xFF);
        uart->sendUart(0x81);
        LOG(INFO) << "Sent drive rearward";
        break;
    }

    switch(radius){ // ************************Waardes aanpassen
        case roomba::radius::SMALL_LEFT:
        uart->sendUart(0x00);
        uart->sendUart(0x81);
        LOG(INFO)<<" ^^ With radius small left";
        break;
        case roomba::radius::BIG_LEFT:
        uart->sendUart(0x08);
        uart->sendUart(0x60);
        LOG(INFO)<<" ^^ With radius big left";
        break;
        case roomba::radius::SMALL_RIGHT:
        uart->sendUart(0x80);
        uart->sendUart(0x7F);
        LOG(INFO)<<" ^^ With radius small right";
        break;
        case roomba::radius::BIG_RIGHT:
        uart->sendUart(0xF7);
        uart->sendUart(0xA0);
        LOG(INFO)<<" ^^ With radius big right";
        break;
    }
    //sendTex->unlock();
}


void interpreter::turnRoomba(uint16_t angle)/*******************************************************************/
{

    bool error = false;
    (void) getAngle();          // reset angle

    uint16_t currentAngle = 0x0000;
    //sendTex->lock();
    uart->sendUart(roomba::drive);

    if((angle >= 0x8000)&&(angle <= 0xFFFF)) // counter clockwise
    {

        LOG(INFO) << "Turn roomba counter clockwise with angle" << angle;
        uart->sendUart(0x00); // Velocity high byte
        uart->sendUart(0x7F); // Velocity low  byte
        //uart->sendUart(0x10);
        uart->sendUart(0x00); // Radius high byte
        uart->sendUart(0x01); // Radius low  byte

        do /*********************/
        {
            usleep(100);
            /*uint16_t temp = ~getAngle();
                temp += 0x0001;
            currentAngle -= temp; // testen!!*/
            currentAngle -= getAngle();

            LOG(DEBUG) << "Current angle is: " << currentAngle;
        }
		while(((currentAngle > angle)||(currentAngle == 0))&&(interpreter::runThread));
        //sendTex->unlock();
        drives(roomba::speed::STOP);
    }
    else
    {
        if(angle >= 0x0000 && angle < 0x8000) // clockwise
        {
            LOG(INFO) << "Turn roomba clockwise with angle" << angle;
            uart->sendUart(0x00); // Velocity high byte
            uart->sendUart(0x7F); // Velocity low  byte
            uart->sendUart(0xFF); // Radius high byte
            uart->sendUart(0xFF); // Radius low  byte

            do /*********************/
            {
                usleep(100);
                uint16_t temp = ~getAngle();
                temp += 0x0001;
                currentAngle += temp;
                LOG(DEBUG) << "Current angle is: " << currentAngle;
            }
			while((currentAngle < angle)&& interpreter::runThread);
            //sendTex->unlock();
            drives(roomba::speed::STOP);
        }
        else error = true;
    }

    if(error == true) LOG(ERROR) << "Wrong angle in turnRoomba method";

}/*******************************************************************/

bool interpreter::slowTillStop()
{
    bool stop = false;
    for(uint8_t speed = 0x7F; speed > 0x30 ; speed=speed*0.75)
    {
        //if(getBumpLeft() || getBumpRight())
        if(Bumps.bLeft || Bumps.bRight)
        {
            drives(roomba::speed::STOP);
            stop = true;
        }
        else
        {
            //sendTex->lock();
            uart->sendUart(roomba::drive);
            uart->sendUart(0x00); // Velocity high byte
            uart->sendUart(speed); // Velocity low  byte
            uart->sendUart(0x80); // Radius high byte
            uart->sendUart(0x00); // Radius low  byte
            //sendTex->unlock();
        }
        
    }
    while(1) {
        //if(getBumpRight() || getBumpLeft() || stop)
        if(Bumps.bLeft || Bumps.bRight || stop)
        {
            drives(roomba::speed::STOP);
            return 0;
        }
        if (!getLightBumper())
            return 1;
    }
    
    
    
}

bool interpreter::getBumpAndWheel()
{
    bool tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::bumpAndWheel);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = (uart->getElement() ? 1 : 0);
                LOG(INFO) << "Bump or wheel detected: " << tmp;
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        uart->flushQueue();
        uart->sendUart(roomba::requestType::individual);
        uart->sendUart(roomba::sensors::bumpAndWheel);
        uart->receiveUart();
        try
        {
            for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
            {
                switch (i) {
                case 1:
                    tmp = (uart->getElement() ? 1 : 0);
                    LOG(INFO) << "Bump or wheel detected: " << tmp;
                    break;
                default:
                    (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                    break;
                }
            }
        }
        catch(int i)
        {
            LOG(ERROR) << "UART isn't working";
            exit(-1);
        }
    }
    //sendTex->unlock();
    return tmp;
}

uint8_t interpreter::getWall()
{
    uint8_t tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::wall);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = uart->getElement();
                LOG(INFO) << "Wall detected: " << tmp;
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    return tmp;
}

bool interpreter::getCliffLeft()
{
    uint8_t tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::cliffLeft);
    uart->receiveUart();
    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = uart->getElement();
                LOG(INFO) << "Cliff Left detected: " << tmp;
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    return (bool)tmp;
}

bool interpreter::getCliffFrontLeft()
{
    uint8_t tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::cliffFrontLeft);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = uart->getElement();
                LOG(INFO) << "Cliff Front Left detected: " << tmp;
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    return (bool)tmp;
}

bool interpreter::getCliffFrontRight()
{
    uint8_t tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::cliffFrontRight);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = uart->getElement();
                LOG(INFO) << "Cliff Front Right detected: " << tmp;
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    return (bool)tmp;
}

bool interpreter::getCliffRight()
{
    uint8_t tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::cliffRight);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = uart->getElement();
                LOG(INFO) << "Cliff Right detected: " << tmp;
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    return (bool)tmp;
}



uint8_t interpreter::getVirtualWall()
{
    uint8_t tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::virtualWall);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = uart->getElement();
                LOG(INFO) << "Virtual wall signal: " << tmp;
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    return tmp;
}

bool interpreter::getWheelOvercurrents()
{
    bool tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::wheelOvercurrents);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = (uart->getElement() ? 1 : 0);
                LOG(INFO) << "Wheel OverCurrent: " << tmp;
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    return tmp;
}

uint8_t interpreter::getDirtDetect()
{
    uint8_t tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::dirtDetect);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = uart->getElement();
                LOG(INFO) << "Dirt detect signal: " << tmp;
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    return tmp;
}

uint8_t interpreter::getIrReceiver()
{
    uint8_t tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::irReceiver);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = uart->getElement();
                LOG(INFO) << "IR receiver signal: " << tmp;
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    return tmp;
}

int16_t interpreter::getDistance()
{
    #ifdef fulldebug
        std::cout<<"Start function getDistance"<<std::endl;
    #endif
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::distance);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;

    LOG(INFO) << "Driven distance since last pull: " << halfWord;
    //sendTex->unlock();
    return halfWord;
}

uint16_t interpreter::getAngle() /*******************************************************************/
{
    uint16_t halfWord = 0x0000;
    uint8_t  highByte = 0x00;
    uint8_t  lowByte  = 0x00;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::angle);
    //usleep(microseconds);
	uart->receiveUart(0.1);

    try
    {
        usleep(10);
        //std::cout<<uart->getQueSize()<<std::endl;
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            //std::cout<<"I is: "<<i<<std::endl;
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    halfWord = highByte << 8;
    halfWord |= lowByte;
    LOG(INFO) << "Turned angle since last pull is: " << halfWord;
    //sendTex->unlock();
    return halfWord;
}/***************************************************************************************************/

uint8_t interpreter::getChargingState()
{

    uint8_t tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::chargingState);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = uart->getElement();
                LOG(INFO) << "Charging state is: " << tmp;
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    return tmp;
}

uint16_t interpreter::getBatteryVoltage()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::batteryVoltage);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Battery voltage is: " << halfWord;
    //sendTex->unlock();
    this->Battery.uiVoltage = halfWord;
    return halfWord;
}

int16_t interpreter::getBatteryCurrent()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::batteryCurrent);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Battery current is: " << halfWord;
    //sendTex->unlock();
    this->Battery.uiCurrent = halfWord;
    return halfWord;
}

int8_t interpreter::getBatteryTemperature()
{
    int8_t tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::batteryTemperature);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = uart->getElement();
                LOG(INFO) << "Battery Temperature is: "<<tmp;
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    this->Battery.iTemperature = tmp;
    return tmp;
}

uint16_t interpreter::getBatteryCharge()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::batteryCharge);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) <<"Battery Charge is: " << halfWord;
    //sendTex->unlock();
    this->Battery.uiCharge = halfWord;
    return halfWord;
}

uint16_t interpreter::getBatteryCapacity()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::batteryCapacity);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Battery Capacity is: " << halfWord;
    //sendTex->unlock();
    this->Battery.uiCapacity = halfWord;
    return halfWord;
}

uint16_t interpreter::getWallSignal()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::wallSignal);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Virtual wall signal is: " << halfWord;
    //sendTex->unlock();
    return halfWord;
}

uint16_t interpreter::getCliffLeftSignal()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::cliffLeftSignal);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Cliff left signal is: " << halfWord;
    //sendTex->unlock();
    this->CliffDepth.uiLeft = halfWord;
    return halfWord;
}

uint16_t interpreter::getCliffFrontLeftSignal()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::cliffFrontLeftSignal);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Cliff front left signal is: " << halfWord;
    //sendTex->unlock();
    this->CliffDepth.uiFrontLeft = halfWord;
    return halfWord;
}

uint16_t interpreter::getCliffFrontRightSignal()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::cliffFrontRightSignal);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Cliff front right signal is: " << halfWord;
    //sendTex->unlock();
    this->CliffDepth.uiFrontRight = halfWord;
    return halfWord;
}

uint16_t interpreter::getCliffRightSignal()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::cliffRightSignal);

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Cliff right signal is: " << halfWord;
    //sendTex->unlock();
    this->CliffDepth.uiRight = halfWord;
    return halfWord;
}

uint8_t interpreter::getChargingSource()
{
    uint8_t tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::chargingSource);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = uart->getElement();
                LOG(INFO) << "Charging source is: "<<tmp;
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    return tmp;
}

uint8_t interpreter::getOiMode()
{
    uint8_t tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::oiMode);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = uart->getElement();
                LOG(INFO) << "OI mode is: " << tmp;
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    return tmp;
}

uint8_t interpreter::getSongNumber()
{
    uint8_t tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::songNumber);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = uart->getElement();
                LOG(INFO) << "Song number is: " << tmp;
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    return tmp;
}

uint8_t interpreter::getSongPlaying()
{
    uint8_t tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::songPlaying);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = uart->getElement();
                LOG(INFO) << "Song playing is: " << tmp;
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    return tmp;
}

int16_t interpreter::getRequestedVelocity()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::requestedVelocity);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Requested Velocity is: " << halfWord;
    //sendTex->unlock();
    return halfWord;
}

int16_t interpreter::getRequestedRadius()
{
    uint8_t lowByte;
    uint8_t highByte;
    int16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::requestedRadius);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Requested Radius is: "<<halfWord;
    //sendTex->unlock();
    return halfWord;
}

int16_t interpreter::getRequestedRightVelocity()
{
    uint8_t lowByte;
    uint8_t highByte;
    int16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::requestedRightVelocity);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;

    LOG(INFO) << "Requested Right wheel Velocity is: " << halfWord;
    //sendTex->unlock();
    return halfWord;
}

int16_t interpreter::getRequestedLeftVelocity()
{
    uint8_t lowByte;
    uint8_t highByte;
    int16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::requestedLeftVelocity);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Requested Left wheel Velocity is: " << halfWord;
    //sendTex->unlock();
    return halfWord;
}

uint16_t interpreter::getLeftEncoderCount()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::leftEncoderCount);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Left encoder count is: " << halfWord;
    //sendTex->unlock();
    return halfWord;
}

uint16_t interpreter::getRightEncoderCount()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::rightEncoderCount);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Right encoder count is: " << halfWord;
    //sendTex->unlock();
    return halfWord;
}

bool interpreter::getLightBumper()
{
    bool tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::lightBumper);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = (uart->getElement() ? 1 : 0);
                LOG(INFO) << "Lightbumper detected: " << tmp;
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    this->Wall.bInsight = tmp;
    return tmp;
}

uint16_t interpreter::getLightBumpLeftSignal()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::lightBumpLeftSignal);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Left Lightbump signal: " << halfWord;
    //sendTex->unlock();
    this->WallDistance.bLeft = halfWord;
    return halfWord;
}

uint16_t interpreter::getLightBumpFrontLeftSignal()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::lightBumpFrontLeftSignal);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Front Left Lightbump signal: " << halfWord;
    //sendTex->unlock();
    this->WallDistance.bFrontLeft = halfWord;
    return halfWord;
}

uint16_t interpreter::getLightBumpCenterLeftSignal()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::lightBumpCenterLeftSignal);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Center Left Lightbump signal: " << halfWord;
    //sendTex->unlock();
    this->WallDistance.bCenterLeft = halfWord;
    return halfWord;
}

uint16_t interpreter::getLightBumpCenterRightSignal()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::lightBumpCenterRightSignal);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Center Right Lightbump signal: " << halfWord;
    //sendTex->unlock();
    this->WallDistance.bCenterRight = halfWord;
    return halfWord;
}

uint16_t interpreter::getLightBumpFrontRightSignal()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::lightBumpFrontRightSignal);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Center Right Lightbump signal: " << halfWord;
    //sendTex->unlock();
    this->WallDistance.bFrontRight = halfWord;    
    return halfWord;
}

uint16_t interpreter::getLightBumpRightSignal()
{
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::lightBumpRightSignal);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Right Lightbump signal: " << halfWord;
    //sendTex->unlock();
    this->WallDistance.bRight = halfWord;
    return halfWord;
}

int16_t interpreter::getLeftMotorCurrent()
{
    uint8_t lowByte;
    uint8_t highByte;
    int16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::leftMotorCurrent);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Left motor current" << halfWord;
    //sendTex->unlock();
    return halfWord;
}

int16_t interpreter::getRightMotorCurrent()
{
    uint8_t lowByte;
    uint8_t highByte;
    int16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::rightMotorCurrent);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Right motor current is: " << halfWord;
    //sendTex->unlock();
    return halfWord;
}

int16_t interpreter::getMainBrushMotorCurrent()
{
    uint8_t lowByte;
    uint8_t highByte;
    int16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::mainBrushMotorCurrent);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Main brush current is: " << halfWord;
    //sendTex->unlock();
    return halfWord;
}

int16_t interpreter::getSideBrushMotorCurrent()
{
    uint8_t lowByte;
    uint8_t highByte;
    int16_t halfWord;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::sideBrushMotorCurrent);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                lowByte = uart->getElement();
                break;
            case 2:
                highByte = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    halfWord = lowByte << 8;
    halfWord |= highByte;
    LOG(INFO) << "Side brush Current" << halfWord;
    //sendTex->unlock();
    return halfWord;
}

uint8_t interpreter::getStatis()
{
    uint8_t tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::statis);
    uart->receiveUart();

    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i) {
            case 1:
                tmp = uart->getElement();
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    return tmp;
}


/***********************************************************/
bool interpreter::getBumpRight()
{
    bool tmp = false;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::bumpAndWheel);
    uart->receiveUart();
    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i){
            case 1:
                tmp = (uart->getElement() & 0b00000001) == 0b00000001 ? 1 : 0;
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    LOG(INFO) << "Right bump is: " <<tmp;
    this->Bumps.bRight = tmp;
    return tmp;
}

bool interpreter::getBumpLeft()
{
    bool tmp = false;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::bumpAndWheel);
    uart->receiveUart();
    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i){
            case 1:
                tmp = (uart->getElement() & 0b00000010) == 0b00000010 ? 1 : 0;
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    LOG(INFO) << "Left bump is: " <<tmp;
    this->Bumps.bLeft = tmp;
    return tmp;
}

bool interpreter::getWheelDropRight()
{
    bool tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::bumpAndWheel);
    uart->receiveUart();
    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i){
            case 1:
                tmp = (uart->getElement() & 0b00000100) == 0b00000100 ? 1 : 0;
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    this->WheelDrops.bRight = tmp;
    LOG(INFO) << "Right wheeldrop is: " <<tmp;
    return tmp;
}

bool interpreter::getWheelDropLeft()
{
    bool tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::bumpAndWheel);
    uart->receiveUart();
    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i){
            case 1:
                tmp = (uart->getElement() & 0b00001000) == 0b00001000 ? 1 : 0;
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    this->WheelDrops.bLeft = tmp;
    LOG(INFO) << "Left wheeldrop is: " <<tmp;
    return tmp;
}

bool interpreter::getSideBrushOvercurrent()
{
    bool tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::wheelOvercurrents);
    uart->receiveUart();
    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i){
            case 1:
                tmp = (uart->getElement() & 0b00000001) == 0b00000001 ? 1 : 0;
                LOG(INFO) << "Side brush overcurrent: " << tmp;
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    this->OverCurrent.bSideBrush = tmp;
    return tmp;
}

bool interpreter::getMainBrushOvercurrent()
{
    bool tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::wheelOvercurrents);
    uart->receiveUart();
    tmp = (uart->getElement() & 0b00000100) == 0b00000100 ? 1 : 0;
    //sendTex->unlock();
    this->OverCurrent.bMainBrush = tmp;
    return tmp;
}

bool interpreter::getRightWheelOvercurrent()
{
    bool tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::wheelOvercurrents);
    uart->receiveUart();
    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i){
            case 1:
                tmp = (uart->getElement() & 0b00001000) == 0b00001000 ? 1 : 0;
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    this->OverCurrent.bWheelRight = tmp;
    return tmp;
}

bool interpreter::getLeftWheelOvercurrent()
{
    bool tmp;
    //sendTex->lock();
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::wheelOvercurrents);
    uart->receiveUart();
    try
    {
        for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
        {
            switch (i){
            case 1:
                tmp = (uart->getElement() & 0b00010000) == 0b00010000 ? 1 : 0;
                break;
            default:
                (void) uart->getElement();
                LOG(WARN) << "Popped one byte to much from uart";
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    //sendTex->unlock();
    this->OverCurrent.bWheelLeft = tmp;
    return tmp;

}

//void interpreter::operator()(){
//    autoMode();
//}

void interpreter::startAutoMode()
{
//    AUTO = new std::thread(ref(*this));
//    AUTO->detach();
}

 void interpreter::stopAutoMode()
 {
    interpreter::autoRunning = false;
 }

void interpreter::autoMode()
{
   uint8_t received;
   interpreter::autoRunning = true;

   while(autoRunning)
   {
       try
       {
           uart->flushQueue();
           //sendTex->lock();
           // bump and wheel functions
           uart->sendUart(roomba::requestType::individual);
           uart->sendUart(roomba::sensors::bumpAndWheel);
           uart->receiveUart();
           for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
           {
               switch(i)
               {
                   case 1:
                       received = uart->getElement();
                       break;
                   default:
                       (void) uart->getElement();
                        LOG(WARN) << "Popped one byte to much from uart";
                       break;
               }
           }
           this->Bumps.bRight      = (received & 0b00000001) == 0b00000001 ? true : false;
           this->Bumps.bLeft       = (received & 0b00000010) == 0b00000010 ? true : false;
           this->WheelDrops.bRight = (received & 0b00000100) == 0b00000100 ? true : false;
           this->WheelDrops.bLeft  = (received & 0b00001000) == 0b00001000 ? true : false;

           //this->Bumps.bRight = getBumpRight();
           //this->Bumps.bLeft = getBumpLeft();

           // overcurrent functions
           uart->sendUart(roomba::requestType::individual);
           uart->sendUart(roomba::sensors::wheelOvercurrents);
           uart->receiveUart();
           for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
           {
               switch(i)
               {
                   case 1:
                       received = uart->getElement();
                       break;
                   default:
                       (void) uart->getElement();
                        LOG(WARN) << "Popped one byte to much from uart";
                       break;
               }
           }
           this->OverCurrent.bSideBrush  = (received & 0b00000001) == 0b00000001 ? true : false;
           this->OverCurrent.bMainBrush  = (received & 0b00000100) == 0b00000100 ? true : false;
           this->OverCurrent.bWheelRight = (received & 0b00001000) == 0b00001000 ? true : false;
           this->OverCurrent.bWheelLeft  = (received & 0b00010000) == 0b00010000 ? true : false;

           // cliff functions
           uart->sendUart(roomba::requestType::individual);
           uart->sendUart(roomba::sensors::cliffLeft);
           uart->receiveUart();
           for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
           {
               switch(i)
               {
                   case 1:
                       received = uart->getElement();
                       break;
                   default:
                       (void) uart->getElement();
                        LOG(WARN) << "Popped one byte to much from uart";
                       break;
               }
           }
           this->Cliff.bLeft = received ? true : false;
           uart->sendUart(roomba::requestType::individual);
           uart->sendUart(roomba::sensors::cliffRight);
           for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
           {
               switch(i)
               {
                   case 1:
                       received = uart->getElement();
                       break;
                   default:
                       (void) uart->getElement();
                        LOG(WARN) << "Popped one byte to much from uart";
                       break;
               }
           }
           this->Cliff.bRight = received ? true : false;
           uart->sendUart(roomba::requestType::individual);
           uart->sendUart(roomba::sensors::cliffFrontLeft);
           for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
           {
               switch(i)
               {
                   case 1:
                       received = uart->getElement();
                       break;
                   default:
                       (void) uart->getElement();
                        LOG(WARN) << "Popped one byte to much from uart";
                       break;
               }
           }
           this->Cliff.bFrontLeft = received ? true : false;
           uart->sendUart(roomba::requestType::individual);
           uart->sendUart(roomba::sensors::cliffFrontRight);
           for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
           {
               switch(i)
               {
                   case 1:
                       received = uart->getElement();
                       break;
                   default:
                       (void) uart->getElement();
                        LOG(WARN) << "Popped one byte to much from uart";
                       break;
               }
           }
           this->Cliff.bFrontRight = received ? true : false;

           // infrared functions
           uart->sendUart(roomba::requestType::individual);
           uart->sendUart(roomba::sensors::irReceiver);
           uart->receiveUart();
           for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
           {
               switch(i)
               {
                   case 1:
                       received = uart->getElement();
                       break;
                   default:
                       (void) uart->getElement();
                        LOG(WARN) << "Popped one byte to much from uart";
                       break;
               }
           }
           switch (received) {
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
           uart->sendUart(roomba::requestType::individual);
           uart->sendUart(roomba::sensors::lightBumper);
           uart->receiveUart();
           for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
           {
               switch(i)
               {
                   case 1:
                       received = uart->getElement();
                       break;
                   default:
                       (void) uart->getElement();
                        LOG(WARN) << "Popped one byte to much from uart";
                       break;
               }
           }
           this->Wall.bInsight     = received ? true : false;
           this->Wall.bLeft        = (received & 0b00000001) == 0b00000001 ? true : false;
           this->Wall.bFrontLeft   = (received & 0b00000010) == 0b00000010 ? true : false;
           this->Wall.bCenterLeft  = (received & 0b00000100) == 0b00000100 ? true : false;
           this->Wall.bCenterRight = (received & 0b00001000) == 0b00001000 ? true : false;
           this->Wall.bFrontRight  = (received & 0b00010000) == 0b00010000 ? true : false;
           this->Wall.bRight       = (received & 0b00100000) == 0b00100000 ? true : false;
       }
       catch(int)
       {

       }

//        //sendTex->unlock();

//        /*system("clear");
//        temp = static_cast<int>(temp);
//        std::cout<< std::endl << "Bump value: " <<std::dec<<temp<<std::endl;
//        std::cout << "Left Wheel drop:          " << this->WheelDrops.bLeft << std::endl;
//        std::cout << "Right Wheel drop:         " << this->WheelDrops.bRight << std::endl;
//        std::cout << "Left Wheel overcurrent:   " << this->OverCurrent.bWheelLeft << std::endl;
//        std::cout << "Right Wheel overcurrent:  " << this->OverCurrent.bWheelRight << std::endl;
//        std::cout << "Main brush overcurrent:   " << this->OverCurrent.bMainBrush << std::endl;
//        std::cout << "Side brush overcurrent:   " << this->OverCurrent.bSideBrush << std::endl;
//        std::cout << "Left Bumper:              " << this->Bumps.bLeft << std::endl;
//        std::cout << "Right Bumper:             " << this->Bumps.bLeft << std::endl;
//        std::cout << "Wall signal Left:         " << this->Wall.bLeft << std::endl;
//        std::cout << "Wall signal FrontLeft:    " << this->Wall.bFrontLeft << std::endl;
//        std::cout << "Wall signal CenterLeft:   " << this->Wall.bCenterLeft << std::endl;
//        std::cout << "Wall signal CenterRight:  " << this->Wall.bCenterRight << std::endl;
//        std::cout << "Wall signal FrontRight:   " << this->Wall.bFrontRight << std::endl;
//        std::cout << "Wall signal Right:        " << this->Wall.bRight << std::endl;*/

    }

}

void interpreter::stopFailSaveThread()
{
    stopFailSave = true;
}

void interpreter::testSensors()
{
    uint8_t received;

    while(1)
    {
        uart->flushQueue();
        // bump and wheel functions
        this->Bumps.bLeft = getBumpLeft();
        this->Bumps.bRight = getBumpRight();
        this->WheelDrops.bLeft = getWheelDropLeft();
        this->WheelDrops.bRight = getWheelDropRight();

        // overcurrent functions
        this->OverCurrent.bMainBrush = getMainBrushOvercurrent();
        this->OverCurrent.bSideBrush = getSideBrushOvercurrent();
        this->OverCurrent.bWheelLeft = getLeftWheelOvercurrent();
        this->OverCurrent.bWheelRight = getRightWheelOvercurrent();

        // cliff functions
        this->Cliff.bFrontLeft = getCliffFrontLeft() ? true : false;
        this->Cliff.bFrontRight = getCliffFrontRight() ? true : false;
        this->Cliff.bLeft = getCliffLeft() ? true : false;
        this->Cliff.bRight = getCliffRight() ? true : false;

        this->CliffDepth.uiFrontLeft = getCliffFrontLeftSignal();
        this->CliffDepth.uiFrontRight = getCliffFrontRightSignal();
        this->CliffDepth.uiLeft = getCliffLeftSignal();
        this->CliffDepth.uiRight = getCliffRightSignal();

        // infrared functions
        uart->sendUart(roomba::requestType::individual);
        uart->sendUart(roomba::sensors::irReceiver);
        uart->receiveUart();
        uint8_t irValue;
        try
        {
            for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
            {
                switch (i) {
                case 1:
                    irValue = uart->getElement();
                    break;
                default:
                    (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                    break;
                }
            }
        }
        catch(int)
        {
            // NOG TE IMPLEMENTERER
        }
        switch (irValue) {
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
        uart->sendUart(roomba::requestType::individual);
        uart->sendUart(roomba::sensors::lightBumper);
        uart->receiveUart();

        try
        {
            for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
            {
                switch (i) {
                case 1:
                    received = uart->getElement();
                    break;
                default:
                    (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                    break;
                }
            }
        }
        catch(int)
        {
            // NOG TE IMPLEMENTERER
        }

        this->Wall.bLeft        = (received & 0b00000001) == 0b00000001 ? true : false;
        this->Wall.bFrontLeft   = (received & 0b00000010) == 0b00000010 ? true : false;
        this->Wall.bCenterLeft  = (received & 0b00000100) == 0b00000100 ? true : false;
        this->Wall.bCenterRight = (received & 0b00001000) == 0b00001000 ? true : false;
        this->Wall.bFrontRight  = (received & 0b00010000) == 0b00010000 ? true : false;
        this->Wall.bRight       = (received & 0b00100000) == 0b00100000 ? true : false;


        uart->sendUart(roomba::requestType::individual);
        uart->sendUart(roomba::sensors::lightBumpCenterLeftSignal);
        uart->receiveUart();
        try
        {
            for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
            {
                switch (i) {
                case 1:
                    received = uart->getElement();
                    break;
                default:
                    (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                    break;
                }
            }
        }
        catch(int)
        {
            // NOG TE IMPLEMENTERER
        }
        this->WallDistance.bCenterLeft = received;

        uart->sendUart(roomba::requestType::individual);
        uart->sendUart(roomba::sensors::lightBumpCenterRightSignal);
        uart->receiveUart();
        try
        {
            for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
            {
                switch (i) {
                case 1:
                    received = uart->getElement();
                    break;
                default:
                    (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                    break;
                }
            }
        }
        catch(int)
        {
            // NOG TE IMPLEMENTERER
        }
        this->WallDistance.bCenterRight = received;

        uart->sendUart(roomba::requestType::individual);
        uart->sendUart(roomba::sensors::lightBumpFrontLeftSignal);
        uart->receiveUart();
        try
        {
            for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
            {
                switch (i) {
                case 1:
                    received = uart->getElement();
                    break;
                default:
                    (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                    break;
                }
            }
        }
        catch(int)
        {
            // NOG TE IMPLEMENTERER
        }
        this->WallDistance.bFrontLeft = received;

        uart->sendUart(roomba::requestType::individual);
        uart->sendUart(roomba::sensors::lightBumpFrontRightSignal);
        uart->receiveUart();
        try
        {
            for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
            {
                switch (i) {
                case 1:
                    received = uart->getElement();
                    break;
                default:
                    (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                    break;
                }
            }
        }
        catch(int)
        {
            // NOG TE IMPLEMENTERER
        }
        this->WallDistance.bFrontRight = received;

        uart->sendUart(roomba::requestType::individual);
        uart->sendUart(roomba::sensors::lightBumpLeftSignal);
        uart->receiveUart();
        try
        {
            for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
            {
                switch (i) {
                case 1:
                    received = uart->getElement();
                    break;
                default:
                    (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                    break;
                }
            }
        }
        catch(int)
        {
            // NOG TE IMPLEMENTERER
        }
        this->WallDistance.bLeft = received;

        uart->sendUart(roomba::requestType::individual);
        uart->sendUart(roomba::sensors::lightBumpRightSignal);
        uart->receiveUart();
        try
        {
            for(unsigned int i = uart->getQueSize(); i > 0 ; --i)
            {
                switch (i) {
                case 1:
                    received = uart->getElement();
                    break;
                default:
                    (void) uart->getElement();
LOG(WARN) << "Popped one byte to much from uart";
                    break;
                }
            }
        }
        catch(int)
        {
            // NOG TE IMPLEMENTERER
        }
        this->WallDistance.bRight = received;

        // battery signal functions
        this->Battery.iTemperature = getBatteryTemperature();
        this->Battery.uiCapacity = getBatteryCapacity();
        this->Battery.uiCharge = getBatteryCharge();
        this->Battery.uiCurrent = getBatteryCurrent();
        this->Battery.uiVoltage = getBatteryVoltage();

        system("clear");
        std::cout<<std::endl;
        std::cout<<"SPEED = " << getRequestedVelocity();
        std::cout<<std::endl;
        std::cout<<"Bumpers "<<std::endl;
        std::cout<<"  - Left  = " <<this->Bumps.bLeft<<std::endl;
        std::cout<<"  - Right = " <<this->Bumps.bRight<<std::endl;
        std::cout<<std::endl;
        std::cout<<"Wheeldrop"<<std::endl;
        std::cout<<"  - Left  = " <<this->WheelDrops.bLeft<<std::endl;
        std::cout<<"  - Right = " <<this->WheelDrops.bRight<<std::endl;
        std::cout<<std::endl;
        std::cout<<"Cliff"<<std::endl;
        std::cout<<"  - Left        = "<<this->Cliff.bLeft       << " - " << this->CliffDepth.uiLeft<<std::endl;
        std::cout<<"  - Front Left  = "<<this->Cliff.bFrontLeft  << " - " << this->CliffDepth.uiFrontLeft<<std::endl;
        std::cout<<"  - Front Right = "<<this->Cliff.bFrontRight << " - " << this->CliffDepth.uiFrontRight<<std::endl;
        std::cout<<"  - Right       = "<<this->Cliff.bRight      << " - " << this->CliffDepth.uiRight<<std::endl;
        std::cout<<std::endl;
        std::cout<<"LightBump"<<std::endl;
        std::cout<<"  - Left         = " << this->Wall.bLeft        <<  " - " << this->WallDistance.bLeft <<std::endl;
        std::cout<<"  - Front Left   = " << this->Wall.bFrontLeft   <<  " - " << this->WallDistance.bFrontLeft <<std::endl;
        std::cout<<"  - Center Left  = " << this->Wall.bCenterLeft  <<  " - " << this->WallDistance.bCenterLeft <<std::endl;
        std::cout<<"  - Center Right = " << this->Wall.bCenterRight <<  " - " << this->WallDistance.bCenterRight <<std::endl;
        std::cout<<"  - Front Right  = " << this->Wall.bFrontRight  <<  " - " << this->WallDistance.bFrontRight <<std::endl;
        std::cout<<"  - Right        = " << this->Wall.bRight       <<  " - " << this->WallDistance.bRight <<std::endl;
        std::cout<<std::endl;
        std::cout<<"Battery"<<std::endl;
        std::cout<<"  - Temperature = " << this->Battery.iTemperature << std::endl;
        std::cout<<"  - Capacity    = " << this->Battery.uiCapacity   << std::endl;
        std::cout<<"  - Charge      = " << this->Battery.uiCharge     << std::endl;
        std::cout<<"  - Current     = " << this->Battery.uiCurrent    << std::endl;
        std::cout<<"  - Voltage     = " << this->Battery.uiVoltage    << std::endl;
    }
}

void interpreter::printTest()
{
	while(1)
    {
        usleep(1000);
        system("clear");
        std::cout<<std::endl;
        std::cout << "Left Wheel drop:          " << this->WheelDrops.bLeft << std::endl;
        std::cout << "Right Wheel drop:         " << this->WheelDrops.bRight << std::endl;
        std::cout << "Left Wheel overcurrent:   " << this->OverCurrent.bWheelLeft << std::endl;
        std::cout << "Right Wheel overcurrent:  " << this->OverCurrent.bWheelRight << std::endl;
        std::cout << "Main brush overcurrent:   " << this->OverCurrent.bMainBrush << std::endl;
        std::cout << "Side brush overcurrent:   " << this->OverCurrent.bSideBrush << std::endl;
        std::cout << "Left Bumper:              " << this->Bumps.bLeft << std::endl;
        std::cout << "Right Bumper:             " << this->Bumps.bLeft << std::endl;
        std::cout << "Wall signal Left:         " << this->Wall.bLeft << std::endl;
        std::cout << "Wall signal FrontLeft:    " << this->Wall.bFrontLeft << std::endl;
        std::cout << "Wall signal CenterLeft:   " << this->Wall.bCenterLeft << std::endl;
        std::cout << "Wall signal CenterRight:  " << this->Wall.bCenterRight << std::endl;
        std::cout << "Wall signal FrontRight:   " << this->Wall.bFrontRight << std::endl;
        std::cout << "Wall signal Right:        " << this->Wall.bRight << std::endl;
    }
    
}

void interpreter::turnRight()
{
    uint16_t currentAngle = 0x0000;
    LOG(INFO) << "Turn roomba 90 degrees clockwise";
    try
    {
        (void) getAngle(); 
        //sendTex->lock();
        uart->sendUart(roomba::drive);

        uart->sendUart(0x00); // Velocity high byte
        uart->sendUart(0x7F); // Velocity low  byte
        uart->sendUart(0xFF); // Radius high byte
        uart->sendUart(0xFF); // Radius low  byte
        //sendTex->unlock();

        do
        {
            usleep(100);
            uint16_t temp = ~getAngle();
            temp += 0x0001;
            currentAngle += temp;
            LOG(DEBUG) << " ^^ Current angle is" << currentAngle;

                
        }
		while((currentAngle < 0x0019) && interpreter::runThread);
        drives(roomba::speed::STOP);
    }
    catch(int)
    {

    }
}

void interpreter::turnLeft()
{
    uint16_t currentAngle = 0x0000;
    LOG(INFO) << "Turn roomba 90 degrees counter clockwise";
    try
    {
        (void) getAngle();
        //sendTex->lock();
		usleep(500);
        uart->sendUart(roomba::drive);

        uart->sendUart(0x00); // Velocity high byte
        uart->sendUart(0x7F); // Velocity low  byte
        uart->sendUart(0x00); // Radius high byte
        uart->sendUart(0x01); // Radius low  byte
        //sendTex->unlock();

        do
        {
            usleep(100);
            currentAngle -= getAngle();
            LOG(DEBUG) << " ^^ Current angle is" << currentAngle;
        }
		while((((currentAngle > 0xFFE8)||(currentAngle == 0)) && (interpreter::runThread)));
        drives(roomba::speed::STOP);
    }
    catch(int)
    {

    }
}
