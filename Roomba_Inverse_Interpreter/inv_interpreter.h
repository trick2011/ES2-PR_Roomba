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
    sendBumpAndWheel();
    sendWall();
    sendCliff();
    sendDistance();
    sendAngle();
    sendWallSignal();
    sendCliffSignal();
    sendLightBumper();


    typedef enum{SLOW,CRUISE,FAST}speed;



private:
    std::array<uint16_t,58> sensorWaarden;
    Uart *uart;

};

#endif // inv_INTERPRETER_H
