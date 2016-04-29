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
    inv_interpreter();
    ~inv_interpreter();
    drive();
    sendBumpAndWheel();
    sendWall();
    sendCliffL();
    sendCliffFL();
    sendCliffFR();
    sendCliffR();
    sendDistance();
    sendAngle();
    sendWallSignal();
    sendCliffL_Signal();
    sendCliffFL_Signal();
    sendCliffFR_Signal();
    sendCliffR_Signal();
    sendLightBumper();
    sendLightBumpL_Signal();
    sendLightBumpFL_Signal();
    sendLightBumpCL_Signal();
    sendLightBumpCR_Signal();
    sendLightBumpFR_Signal();
    sendLightBumpR_Signal();

    uint8_t UartTemp;
    uint8_t HByte1;
    uint8_t LByte1;
    uint8_t HByte2;
    uint8_t LByte2;
    int iCurrentSpeed;
    int iCurrentRadius;

private:
    std::array<uint16_t,58> sensorWaarden;

};

#endif // inv_INTERPRETER_H
