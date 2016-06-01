

#include <iostream>
#include "uart.h"

using namespace std;
//INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    // Load configuration from file
    //el::Configurations conf("./my-conf.conf");
    // Reconfigure single logger
    //el::Loggers::reconfigureLogger("default", conf);
    // Actually reconfigure all loggers instead
    //el::Loggers::reconfigureAllLoggers(conf);
    // Now all the loggers will use configuration from file
    UARTClass aurt("/dev/tty1");
    aurt.sendstring("fagggg");
    aurt.sendUart(0x30);
    //UART::sendUart(1);

    return 0;
}

