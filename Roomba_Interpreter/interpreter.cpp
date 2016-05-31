#include "interpreter.h"

interpreter::interpreter()
{
#ifdef fulldebug
    std::cout<<"\033[32m start function interpreter (constructor) \033[0m"<<std::endl;
#endif

    uart = new UARTClass("/dev/ttyUSB0");

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
    uart->sendUart(roomba::modes::safeMode);
    //uart->sendUart(roomba::cleanModes::Clean);

#ifdef fulldebug
    std::cout<<"\033[31m end function startRoomba\033[0m"<<std::endl;
#endif

}

void interpreter::stopRoomba()
{
    uart->sendUart(roomba::Stop);
}

void interpreter::brushes(int brush)
{
#ifdef fulldebug
    std::cout<<"start function brushes"<<std::endl;
#endif
    switch (brush) {
    case roomba::brush::NOBRUSH: // no brush

        uart->sendUart(roomba::brushes);
        uart->sendUart(roomba::brush::NOBRUSH);
        break;
    case roomba::brush::SIDEBRUSH: // side brush

        uart->sendUart(roomba::brushes);
        uart->sendUart(roomba::brush::SIDEBRUSH);
        break;
    case roomba::brush::MAINBRUSH: // main brush

        uart->sendUart(roomba::brushes);
        uart->sendUart(roomba::brush::MAINBRUSH);
        break;
    case roomba::brush::BOTH: // side and main brush

        uart->sendUart(roomba::brushes);
        uart->sendUart(roomba::brush::BOTH);
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
    case roomba::speed::SLOW: //slow
        uart->sendUart(0x00); // Velocity high byte
        uart->sendUart(0x7F); // Velocity low  byte
        uart->sendUart(0x80); // Radius high byte
        uart->sendUart(0x00); // Radius low  byte
        break;
    case roomba::speed::CRUISE: //middle
        uart->sendUart(0x08); // Velocity high byte
        uart->sendUart(0x00); // Velocity low  byte
        uart->sendUart(0x80); // Radius high byte
        uart->sendUart(0x00); // Radius low  byte
        break;
    case roomba::speed::FAST: // /////////schaal lager zetten
        uart->sendUart(0x7F); // Velocity high byte
        uart->sendUart(0xFF); // Velocity low  byte
        uart->sendUart(0x80); // Radius high byte
        uart->sendUart(0x00); // Radius low  byte
        break;
    case roomba::speed::STOP: // stop
        uart->sendUart(0x00);
        uart->sendUart(0x00);
        uart->sendUart(0x00);
        uart->sendUart(0x00);
    case roomba::speed::BACKWARDS: // backwards
        uart->sendUart(0xFF);
        uart->sendUart(0x81);
        uart->sendUart(0x80);
        uart->sendUart(0x00);
    }
#ifdef fulldebug
    std::cout<<"end function drives"<<std::endl;
#endif
}
void interpreter::turnAndDrive(int speed, int radius) // define in header file, make enums for switches
{
    uart->sendUart(roomba::drive);
    switch(speed){
        case roomba::speed::SLOW: //slow
        uart->sendUart(0x00);
        uart->sendUart(0x7F);
        break;
        case roomba::speed::CRUISE: //middle
        uart->sendUart(0x08);
        uart->sendUart(0x00);
        break;
        case roomba::speed::FAST: //fast
        uart->sendUart(0x7F);
        uart->sendUart(0xFF);
        break;
        case roomba::speed::BACKWARDS: // backwards
        uart->sendUart(0xFF);
        uart->sendUart(0x81);
        break;
    }

    switch(radius){ // ************************Waardes aanpassen
        case roomba::radius::SMALL_LEFT:
        uart->sendUart(0x00);
        uart->sendUart(0x81);
        break;
        case roomba::radius::BIG_LEFT:
        uart->sendUart(0x08);
        uart->sendUart(0x60);
        break;
        case roomba::radius::SMALL_RIGHT:
        uart->sendUart(0x80);
        uart->sendUart(0x7F);
        break;
        case roomba::radius::BIG_RIGHT:
        uart->sendUart(0xF7);
        uart->sendUart(0xA0);
        break;
    }
}


void interpreter::turnRoomba(uint16_t angle)/*******************************************************************/
{
#ifdef fulldebug
    std::cout<<"start function turnRoomba"<<std::endl;
#endif

    bool error = false;
    (void) getAngle();          // reset angle

    uint16_t currentAngle = 0x0000;
    uart->sendUart(roomba::drive);

    if((angle >= 0x8000)&&(angle <= 0xFFFF)) // counter clockwise
    {

		#ifdef fulldebug
		    std::cout<<"counter clockwise"<<std::endl;
		#endif

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

			#ifdef fulldebug
			std::cout<<std::hex;
		    std::cout<<"Angle is: "<<currentAngle<<std::endl;
			#endif
        }
        while((currentAngle > angle)||(currentAngle == 0));

        drives(roomba::speed::STOP);
    }
    else
    {
        if(angle >= 0x0000 && angle < 0x8000) // clockwise
        {

		    #ifdef fulldebug
		        std::cout<<"clockwise"<<std::endl;
		    #endif
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
            	//currentAngle += getAngle();
			
			#ifdef fulldebug
			std::cout<<std::hex;
		    std::cout<<"Angle is: "<<currentAngle<<std::endl;
			#endif
                //currentAngle = getAngle();
            }
            while(currentAngle < angle);
            drives(roomba::speed::STOP);
        }
        else error = true;
    }

    if(error == true) std::cerr<<"\033[31m ERROR: wrong angle!\033[0m"<<std::endl;

#ifdef fulldebug
    std::cout<<"end function turnRoomba"<<std::endl;
#endif
}/*******************************************************************/

void interpreter::failSave()
{
    while(1)
    {
        if(stopFailSave)break;


        /* check critical individual and intervene if neccesary */

        uart->sendUart(roomba::sensors::bumpAndWheel);
        if(uart->getElement())
        {
            uart->sendUart(roomba::Stop);
        }

        uart->sendUart(roomba::sensors::cliffLeftSignal);
        if(uart->getElement() > 2048)
        {
            uart->sendUart(roomba::Stop);
        }

        uart->sendUart(roomba::sensors::cliffFrontLeftSignal);
        if(uart->getElement() > 2048)
        {
            uart->sendUart(roomba::Stop);
        }

        uart->sendUart(roomba::sensors::cliffFrontRightSignal);
        if(uart->getElement() > 2048)
        {
            uart->sendUart(roomba::Stop);
        }

        uart->sendUart(roomba::sensors::cliffRightSignal);
        if(uart->getElement() > 2048)
        {
            uart->sendUart(roomba::Stop);
        }

        uart->sendUart(roomba::sensors::wheelOvercurrents);
        if(uart->getElement())
        {
            uart->sendUart(roomba::Stop);
        }

        uart->sendUart(roomba::sensors::batteryCapacity);
        uint16_t cap = uart->getElement();
        uart->sendUart(roomba::sensors::batteryCharge);
        uint16_t charg = uart->getElement();
        if((cap/charg*100) < 10)
        {
            uart->sendUart(roomba::Stop); // stop roomba when battery is under 10%
        }



        //std::this_thread::sleep_for(interval);
    }

}

bool interpreter::getBumpAndWheel()
{
#ifdef fulldebug
    std::cout<<"start function getBumpAndWheel"<<std::endl;
#endif
    bool tmp;

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
                break;
            default:
                (void) uart->getElement();
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
	                break;
	            default:
	                (void) uart->getElement();
	                break;
	            }
	        }
	    }
	    catch(int i)
	    {
	    	std::cout<<"No uart"<<std::endl;
	    	exit(-1);
	    }
    }

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
    uint8_t tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

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
    uint8_t tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

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
    uint8_t tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
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
    uint8_t tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
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
    uint8_t tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

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
    uint8_t tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

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
    bool tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
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
    uint8_t tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

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
    uint8_t tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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

#ifdef fulldebug
    std::cout<<"end function getDistance"<<std::endl;
#endif
    return halfWord;
}

uint16_t interpreter::getAngle() /*******************************************************************/
{
	#ifdef fulldebug
	    std::cout<<"\033[32m start function getAngle\033[0m"<<std::endl;
	#endif

    uint16_t halfWord = 0x0000;
    uint8_t  highByte = 0x00;
    uint8_t  lowByte  = 0x00;

    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::angle);
    //usleep(microseconds);
    uart->receiveUart();

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
				#ifdef fulldebug
				    std::cout<<"In function getAngle, highByte is: "<<std::hex<<highByte<<std::endl;
				#endif
                break;
            case 2:
                highByte = uart->getElement();
				#ifdef fulldebug
				    std::cout<<"In function getAngle, lowByte is: "<<std::hex<<lowByte<<std::endl;
				#endif
				break;
            default:
                (void) uart->getElement();
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

	#ifdef fulldebug
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
    uint8_t tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    int8_t tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

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
    uint8_t tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

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
    uint8_t tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

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
    uint8_t tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    int16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    int16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    int16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    bool tmp;

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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    uint16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    int16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    int16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    int16_t halfWord;

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
    uint8_t lowByte;
    uint8_t highByte;
    int16_t halfWord;

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
    uint8_t tmp;

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
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

#ifdef fulldebug
    std::cout<<"end function getStatis"<<std::endl;
#endif
    return tmp;
}


/***********************************************************/
bool interpreter::getBumpRight()
{
    bool tmp = false;
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
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    return tmp;
}

bool interpreter::getBumpLeft()
{
    bool tmp = false;
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
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    

    return tmp;
}

bool interpreter::getWheelDropRight()
{
    bool tmp;
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
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }

    return tmp;
}

bool interpreter::getWheelDropLeft()
{
    bool tmp;
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
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    return tmp;
}

bool interpreter::getSideBrushOvercurrent()
{
    bool tmp;
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
                break;
            default:
                (void) uart->getElement();
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    return tmp;
}

bool interpreter::getMainBrushOvercurrent()
{
    bool tmp;
    uart->sendUart(roomba::requestType::individual);
    uart->sendUart(roomba::sensors::wheelOvercurrents);
    uart->receiveUart();
    tmp = (uart->getElement() & 0b00000100) == 0b00000100 ? 1 : 0;

    return tmp;
}

bool interpreter::getRightWheelOvercurrent()
{
    bool tmp;
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
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
    return tmp;
}

bool interpreter::getLeftWheelOvercurrent()
{
    bool tmp;
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
                break;
            }
        }
    }
    catch(int)
    {
        // NOG TE IMPLEMENTERER
    }
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
        uart->flushQueue();
        // bump and wheel functions
        uart->sendUart(roomba::requestType::individual);
        uart->sendUart(roomba::sensors::bumpAndWheel);
        uart->receiveUart();
        received = uart->getElement();
        uint8_t temp = received;
        this->Bumps.bRight      = (received & 0b00000001) == 0b00000001 ? true : false;
        this->Bumps.bLeft       = (received & 0b00000010) == 0b00000010 ? true : false;
        this->WheelDrops.bRight = (received & 0b00000100) == 0b00000100 ? true : false;
        this->WheelDrops.bLeft  = (received & 0b00001000) == 0b00001000 ? true : false;

        // overcurrent functions
        uart->sendUart(roomba::requestType::individual);
        uart->sendUart(roomba::sensors::wheelOvercurrents);
        uart->receiveUart();
        received = uart->getElement();
        this->OverCurrent.bSideBrush  = (received & 0b00000001) == 0b00000001 ? true : false;
        this->OverCurrent.bMainBrush  = (received & 0b00000100) == 0b00000100 ? true : false;
        this->OverCurrent.bWheelRight = (received & 0b00001000) == 0b00001000 ? true : false;
        this->OverCurrent.bWheelLeft  = (received & 0b00010000) == 0b00010000 ? true : false;

        // cliff functions
        uart->sendUart(roomba::requestType::individual);
        uart->sendUart(roomba::sensors::cliffLeft);
        uart->receiveUart();
        this->Cliff.bLeft = uart->getElement() ? true : false;
        uart->sendUart(roomba::sensors::cliffRight);
        this->Cliff.bRight = uart->getElement() ? true : false;
        uart->sendUart(roomba::sensors::cliffFrontLeft);
        this->Cliff.bFrontLeft = uart->getElement() ? true : false;
        uart->sendUart(roomba::sensors::cliffFrontRight);
        this->Cliff.bFrontRight = uart->getElement() ? true : false;

        // infrared functions
        uart->sendUart(roomba::requestType::individual);
        uart->sendUart(roomba::sensors::irReceiver);
        uart->receiveUart();
        switch (uart->getElement()) {
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
        received = uart->getElement();
        this->Wall.bLeft        = (received & 0b00000001) == 0b00000001 ? true : false;
        this->Wall.bFrontLeft   = (received & 0b00000010) == 0b00000010 ? true : false;
        this->Wall.bCenterLeft  = (received & 0b00000100) == 0b00000100 ? true : false;
        this->Wall.bCenterRight = (received & 0b00001000) == 0b00001000 ? true : false;
        this->Wall.bFrontRight  = (received & 0b00010000) == 0b00010000 ? true : false;
        this->Wall.bRight       = (received & 0b00100000) == 0b00100000 ? true : false;

        system("clear");
        temp = static_cast<int>(temp);
        std::cout<< std::endl << "Bump value: " <<std::dec<<temp<<std::endl;
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
    usleep(100);
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

void interpreter::turnRight()
{
    uint16_t currentAngle = 0x0000;
    try
    {
        (void) getAngle(); 
        uart->sendUart(roomba::drive);

        uart->sendUart(0x00); // Velocity high byte
        uart->sendUart(0x7F); // Velocity low  byte
        uart->sendUart(0xFF); // Radius high byte
        uart->sendUart(0xFF); // Radius low  byte

        do
        {
            usleep(100);
            uint16_t temp = ~getAngle();
            temp += 0x0001;
            currentAngle += temp;
                
        }
        while(currentAngle < 0x0019);
        drives(roomba::speed::STOP);
    }
    catch(int)
    {

    }
}

void interpreter::turnLeft()
{
    uint16_t currentAngle = 0x0000;
    try
    {
        (void) getAngle(); 
        uart->sendUart(roomba::drive);

        uart->sendUart(0x00); // Velocity high byte
        uart->sendUart(0x7F); // Velocity low  byte
        uart->sendUart(0x00); // Radius high byte
        uart->sendUart(0x01); // Radius low  byte

        do
        {
            usleep(100);
            currentAngle -= getAngle();
        }
        while((currentAngle > 0xFFE8)||(currentAngle == 0));
        drives(roomba::speed::STOP);
    }
    catch(int)
    {

    }
}