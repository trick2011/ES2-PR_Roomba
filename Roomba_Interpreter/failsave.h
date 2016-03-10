#ifndef FAILSAVE_H
#define FAILSAVE_H

#include <mutex>

class failsave
{
public:
    failsave(std::mutex *newTex);

private:
    std::mutex tex;
    void checkCodes();
};

#endif // FAILSAVE_H
