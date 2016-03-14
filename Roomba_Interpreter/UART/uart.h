#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <vector>
#include <mutex>
#include <thread>

class UART
{
public:
    UART();
    void uartSend(uint8_t code);
    void failSaveSend(uint8_t code);
    uint8_t receiveUart();

private:
    void send(uint8_t code);
    void threadSend();

private:
    std::vector<uint8_t> sendBuffer;
    std::mutex mTex;
};

#endif // UART_H
