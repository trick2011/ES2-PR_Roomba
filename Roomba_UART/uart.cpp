#include "uart.h"

UARTClass::~UARTClass(){
    if(ofp.is_open())
        ofp.close();
}

#ifdef __linux
UARTClass::UARTClass(){
    iUARTFileStream = -1;
    iUARTFileStream = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

    if (iUARTFileStream == -1){
		//LOG(ERROR) << "Cannot start UART.";
    }

    struct termios options;
    tcgetattr(iUARTFileStream, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;		// Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(iUARTFileStream, TCIFLUSH);
    tcsetattr(iUARTFileStream, TCSANOW, &options);
}

UARTClass::UARTClass(string sTTY){
    iUARTFileStream = -1;

    iUARTFileStream = open(sTTY.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

    if (iUARTFileStream == -1){
	   // LOG(ERROR) << "Cannot start UART.";
    }
    struct termios options;
    tcgetattr(iUARTFileStream, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(iUARTFileStream, TCIFLUSH);
    tcsetattr(iUARTFileStream, TCSANOW, &options);
}

bool UARTClass::sendUart(uint8_t code){
    if (iUARTFileStream != -1){
        int count = write(iUARTFileStream,&code,1);

        if (count < 0){
//            LOG(WARN) << "Count is < 0 in sendUART.";
            return(false);
        }

        else{
//            LOG(DEBUG) << "Sending code: " << code;
            return(true);
        }
    }

    else{
//        LOG(ERROR) << "Cannot open UART in sendUart.";
    }
    return(false);
}

bool UARTClass::sendstring(string sInput){
    int count = -1;
    if(iUARTFileStream != -1){
        count = write(iUARTFileStream,sInput.c_str(),sInput.size());	

        if (count < 0){
//            LOG(WARN) << "Count is < 0 in sendstring.";
            return(false);
        }

        else{
//			LOG(DEBUG) << "Sending string: " << sInput;
            return(true);
        }
    }

    else
    {
//        LOG(ERROR) << "Cannot open UART in sendstring.";
    }
    return(false);
}

bool UARTClass::receiveUart(double ReceiveDelay){ // geef een string terug want das makkelijker als rx_buffer vervanger
    bReceive = true;
    unsigned char rx_buffer[256] = "\0";
    if (iUARTFileStream != -1)
    {
        int ReadSize =0;
        do
            ReadSize = read(iUARTFileStream, &rx_buffer, 255);
        while( ReadSize <= 0 && bReceive);

//        LOG(DEBUG) << "First read... ReadSize in receiveUart: " << ReadSize;

        for(int i=0;i<ReadSize;i++)
        {
            ReceiveQueue.push(rx_buffer[i]);
//            LOG(DEBUG) << "In receiveUart buffer at " << i << " is " << rx_buffer[i];
        }
        
        chrono::time_point<chrono::system_clock> start,end;
        start = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds;

        while(true){
            end = chrono::system_clock::now();
            elapsed_seconds = end - start;

			if(elapsed_seconds.count() >= ReceiveDelay)
            {
                break;
            }

        }
        //second read
        memset(&rx_buffer,0x00,255);

        ReadSize = read(iUARTFileStream, &rx_buffer, 255);

//        LOG(DEBUG) << "Second read... ReadSize in receiveUart: " << ReadSize;

        for(int i=0;i<ReadSize;i++){
            ReceiveQueue.push(rx_buffer[i]);
//            LOG(DEBUG) << "In receiveUart buffer at " << i << " is " << rx_buffer[i];
        }

        if(bReceive)
            return(true);
        else
            return(false);

    }
    else
//        LOG(ERROR) << "Cannot open UART in receiveUart.";
    return(false);
}

uint8_t UARTClass::getElement(){
    unsigned char ucElement = 0;

	//LOG(INFO) << "Getting Queue Element...";

    if(!ReceiveQueue.empty()){
        ucElement = ReceiveQueue.front();
        ReceiveQueue.pop();

		//LOG(DEBUG) << "Queue Element: " << ucElement;
    }

    else
        throw 1;

    return(ucElement);
}

int UARTClass::getQueSize(){
//    LOG(INFO) << "Receiving QueueSize...";
    return(ReceiveQueue.size());
}

void UARTClass::flushQueue(){
//    LOG(INFO) << "Emptying Queue...";

    while(!ReceiveQueue.empty()){
        ReceiveQueue.pop();
    }

//    LOG(INFO) << "Queue is empty.";
}
#endif

#ifdef _WIN32 //just filler implementation for windows
UARTClass::UARTClass(){}
UARTClass::UARTClass(string sTTY){sTTY = sTTY;}
bool UARTClass::sendUart(uint8_t code){return(false && code);}
bool UARTClass::sendstring(string sInput){return(false && sInput.size());}
bool UARTClass::receiveUart(){return(false);}
uint8_t UARTClass::getElement(){return(0x00);}
int UARTClass::getQueSize(){return(0);}
void UARTClass::flushQueue(){}
string UARTClass::receiveString(void){return("\0");}
#endif
