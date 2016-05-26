#include "uart.h"
//queue<int> UARTClass::ReceiveQueue;
//bool UARTClass::bReceive;
UARTClass::~UARTClass(){
	if(ofp.is_open())
		ofp.close();
}
#ifdef __linux
UARTClass::UARTClass(){
    /* code voor opstarten uart
-------------------------
----- SETUP USART 0 -----
-------------------------
At bootup, pins 8 and 10 are already set to UART0_TXD, UART0_RXD (ie the alt0 function) respectively*/

    iUARTFileStream = -1;
    /*OPEN THE UART
    The flags (defined in fcntl.h):
        Access modes (use 1 of these):
            O_RDONLY - Open for reading only.
            O_RDWR - Open for reading and writing.
            O_WRONLY - Open for writing only.

    O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
                                            if there is no input immediately available (instead of blocking). Likewise, write requests can also return
                                            immediately with a failure status if the output can't be written immediately.

    O_NOCTTY - When set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process.*/
	iUARTFileStream = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode

    if (iUARTFileStream == -1)
        //ERROR - CAN'T OPEN SERIAL PORT
        printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");

    /*CONFIGURE THE UART
    The flags (defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
        Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
        CSIZE:- CS5, CS6, CS7, CS8
        CLOCAL - Ignore modem status lines
        CREAD - Enable receiver
        IGNPAR = Ignore characters with parity errors
        ICRNL - Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters - don't use for bianry comms!)
        PARENB - Parity enable
        PARODD - Odd parity (else even)*/
    struct termios options;
    tcgetattr(iUARTFileStream, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;		//<Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(iUARTFileStream, TCIFLUSH);
    tcsetattr(iUARTFileStream, TCSANOW, &options);
}
UARTClass::UARTClass(string sTTY){
    iUARTFileStream = -1;
    
    iUARTFileStream = open(sTTY.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

    if (iUARTFileStream == -1)
        printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");

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
    //----- TX BYTES -----
    if (iUARTFileStream != -1){
        int count = write(iUARTFileStream,&code,1);		//Filestream, bytes to write, number of bytes to write
        if (count < 0)
            return(false);
        else
            return(true);
    }
    return(false);
}
bool UARTClass::sendstring(string sInput){
    int count = -1;
    if(iUARTFileStream != -1)
        count = write(iUARTFileStream,sInput.c_str(),sInput.size());		//Filestream, bytes to write, number of bytes to write

    if (count < 0)
        return(false);
    else
        return(true);
}

bool UARTClass::receiveUart(){ // geef een string terug want das makkelijker als rx_buffer vervanger
	bReceive = true;
	unsigned char rx_buffer[256] = "\0";
	if (iUARTFileStream != -1){
		//int rx_length = read(iUARTFileStream, &rx_buffer, 255);		//Filestream, buffer to store in, number of bytes to read (max) // maak een creatieve manier om (void*)rx_buffer om te zetten in de string

		int ReadSize =0;
		do
			ReadSize = read(iUARTFileStream, &rx_buffer, 255);
		while( ReadSize <= 0 && bReceive);

		stringstream ss;
		for(int i=0;i<ReadSize;i++){
			ReceiveQueue.push(rx_buffer[i]);
			ss << rx_buffer[i] << "|";
		}

		chrono::time_point<chrono::system_clock> start,end;
		start = chrono::system_clock::now();
		chrono::duration<double> elapsed_seconds;
		while(true){
			end = chrono::system_clock::now();
			elapsed_seconds = end - start;
			if(elapsed_seconds.count() >= 0.10){
				break;
			}

		}
		//second read
		memset(&rx_buffer,0x00,255);

		ReadSize = read(iUARTFileStream, &rx_buffer, 255);

		for(int i=0;i<ReadSize;i++){
			ReceiveQueue.push(rx_buffer[i]);
			ss << rx_buffer[i] << "|";
		}

		ofp << ss.str();
		ofp << endl;

		if(bReceive)
			return(true);
		else
			return(false);
	}
	return(false);
}

void UARTClass::operator()(){
//	receiveUartContinuous();
}


uint8_t UARTClass::getElement(){
	unsigned char ucElement = 0;
	if(!ReceiveQueue.empty())
	{
		ucElement = ReceiveQueue.front();
    	ReceiveQueue.pop();
	}
	else
		throw 1;
    
    return(ucElement);
}

int UARTClass::getQueSize(){
    return(ReceiveQueue.size());
}

void UARTClass::flushQueue()
{
	while(!ReceiveQueue.empty())
	{
		ReceiveQueue.pop();
	}
}

string UARTClass::receiveString(void){
    bReceive = true;
    if(iUARTFileStream != -1){
        char rx_buffer[256];
        //        int rx_length = read(iUARTFileStream, &rx_buffer, 255);
        while(read(iUARTFileStream, &rx_buffer, 255) <= 0 && bReceive){;}
        
        if(bReceive){
            string returnvalue(rx_buffer);
            return(returnvalue);
        }
        else
            return("\0");
    }
    return("\0");
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
