#ifndef FAILSAVE_H
#define FAILSAVE_H

#include "opcodes.h"
#include <mutex>
#include <unistd.h>

class failsave
{
public:
    failsave(std::mutex &tex);
    ~failsave();

    void stopFailsave();

private:
    void checkCodes();
    bool checkRunning();

    bool stop;
    std::mutex tex;

    opcodes *Opcodesa;
};

#endif // FAILSAVE_H
