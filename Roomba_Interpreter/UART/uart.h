#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <vector>
#include <thread>

class Uart
{
public:
    Uart();
    uint8_t receiveUart();
    void sendUart(uint8_t code);
};

#endif // UART_H
