#include <iostream>
#include "uart.h"

using namespace std;

int main(int argc, char *argv[])
{
    UART aurt;
    aurt.sendUart(8);
    //UART::sendUart(1);
    return 0;
}

