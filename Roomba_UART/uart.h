#ifndef UART_H
#define UART_H

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "../Roomba_Logger/log.h"

#include <cstring>
#include <stdint.h>

#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART

#ifdef __linux__            // Linux Includes Here
#include <termios.h>		//Used for UART on linux and builds with the native header
#endif

#ifdef _WIN32               //|| _WIN64  // Windows Includes Here
#include "termios.h"		//Used for UART on windows and builds with a copied version of the native header
#endif

using namespace std;

class UARTClass  
{
private:
    int iUARTFileStream; 
    bool bReceive;
    queue<int> ReceiveQueue;
    ofstream ofp;

public:
    UARTClass();
    UARTClass(string sTTY);
    ~UARTClass();

    bool receiveUart();
    uint8_t getElement();
    int getQueSize();
    void flushQueue();

    bool sendUart(uint8_t code);
    bool sendstring(string sInput);

    void breakreceive(void) {bReceive = false;}
};

#endif // UART_H
