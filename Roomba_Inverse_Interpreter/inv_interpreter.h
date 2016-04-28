#ifndef inv_INTERPRETER_H
#define inv_INTERPRETER_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

#include "opcodes.h"
#include "../Roomba_Interpreter/UART/uart.h"

//std::chrono::milliseconds interval(500);

class inv_interpreter
{
public:
    interpreter();
    ~interpreter();
    drive();
    sendBumpAndWheel();
    sendWall();
    sendCliff();
    sendCliff();
    sendCliff();
    sendCliff();
    sendDistance();
    sendAngle();
    sendWallSignal();
    sendCliffSignal();
    sendCliffSignal();
    sendCliffSignal();
    sendCliffSignal();
    sendLightBumper();
    sendLightBump();
    sendLightBump();
    sendLightBump();
    sendLightBump();
    sendLightBump();
    sendLightBump();


    typedef enum{SLOW,CRUISE,FAST}speed;



private:
    std::array<uint16_t,58> sensorWaarden;
    Uart *uart;
    char UartTemp;
    char HByte1;
    char LByte1;
    char HByte2;
    char LByte2;

};

#endif // inv_INTERPRETER_H
