#include <iostream>
#include "uart.h"

using namespace std;

int main(int argc, char *argv[])
{
    UARTClass aurt("/dev/tty1");
    aurt.sendstring("fagggg");
    aurt.sendUart(0x30);
    //UART::sendUart(1);
    return 0;
}

