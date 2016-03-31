#ifndef UART_H
#define UART_H

//#include <stdio.h> /**< jelmer dit is c++ oftwele we gebruiken <iostream> en niet <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		        //Used for UART
//#include <errno.h>  /**< als includes niet nodig zijn moet je ze niet includen **/
//#include <fcntl.h>  /**< als includes niet nodig zijn moet je ze niet includen **/
//#include <sys/stat.h>  /**< als includes niet nodig zijn moet je ze niet includen **/


#include <stdint.h>
#include <vector>
#include <thread>

#include <string>
#include <iostream>

using namespace std;

class UARTClass  /**< hier mag eigenlijk ook een betere naam voor gekozen worden want Uart voelt gewoon raar en kan beter benoemt worden **/
            /**< uberhaupt moeten variabelen beter benoemt worden **/
{
private: 
    int iUARTFileStream; /**< geen globale variabelen maken maar het netjes in een classe opnemen, dit is een belangrijk onderdeel van C++ **/
    bool bReceive;
public:
    UARTClass();
    UARTClass(string sTTY);
    uint8_t receiveUart();
    bool sendUart(uint8_t code);
    
    bool sendstring(string sInput);
    string receiveString(void);
};

#endif // UART_H
