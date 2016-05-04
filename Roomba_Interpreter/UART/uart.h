#ifndef UART_H
#define UART_H

//#include <stdio.h> /**< jelmer dit is c++ oftwele we gebruiken <iostream> en niet <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART

#ifdef __linux__  // Linux Includes Here
#include <termios.h>		        //Used for UART on linux and builds with the native header
#endif

#ifdef _WIN32 || _WIN64  // Windows Includes Here
#include "../../Roomba_Interpreter/UART/termios.h"		        //Used for UART on windows and builds with a copied version of the native header
#endif


//#include <errno.h>  /**< als includes niet nodig zijn moet je ze niet includen **/
//#include <sys/stat.h>  /**< als includes niet nodig zijn moet je ze niet includen **/
#include <sys/types.h> //JEROEN IS HIER VERANTOWOORDELIJK VOOR
#include <sys/stat.h> //JEROEN IS HIER VERANTOWOORDELIJK VOOR

#include <stdint.h>
#include <vector>
#include <thread>
#include <queue>

#include <string>
#include <iostream>

using namespace std;

class UARTClass  /**< hier mag eigenlijk ook een betere naam voor gekozen worden want Uart voelt gewoon raar en kan beter benoemt worden **/
            /**< uberhaupt moeten variabelen beter benoemt worden **/
{
private: 
    int iUARTFileStream; /**< geen globale variabelen maken maar het netjes in een classe opnemen, dit is een belangrijk onderdeel van C++ **/
    bool bReceive;
    queue<int> ReceiveQueue;
public:
    UARTClass();
    UARTClass(string sTTY);
    
	bool receiveUart();
    uint8_t getElement();
    string receiveString(void);
    int getQueSize();
    void flushQueue();
    
	bool sendUart(uint8_t code);
    bool sendstring(string sInput);
    
    void breakreceive(void) {bReceive = false;}
};


#endif // UART_H
