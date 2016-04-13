#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

#include "opcodes.h"
#include "./UART/uart.h"

//std::chrono::milliseconds interval(500);

class interpreter
{
public:
    interpreter();
    ~interpreter();

    typedef enum{SLOW,CRUISE,FAST}speed;



private:
    std::array<uint16_t,58> sensorWaarden;
    Uart *uart;

};

#endif // INTERPRETER_H
