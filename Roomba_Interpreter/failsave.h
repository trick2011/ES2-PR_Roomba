#ifndef FAILSAVE_H
#define FAILSAVE_H

#include <unistd.h>
#include "opcodes.h"
#include "UART/uart.h"

class opcodes;

class failsave
{
public:
    failsave();
    ~failsave();

    void stopFailsave();

private:
    void checkCodes();
    bool checkRunning();

    bool stop;

    opcodes *Opcodes;
    UART *uart;
};

#endif // FAILSAVE_H
