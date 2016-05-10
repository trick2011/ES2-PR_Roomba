#ifndef FAIL_ERROR_H
#define FAIL_ERROR_H

#include <exception>

class UartReceiveBufferEmpty: public std::exception
{
    virtual const char* what() const throw()
    {
        return "bufferEmpty";
    }
};

#endif // FAIL_ERROR_H
