#include <iostream>
#include "inv_interpreter.h"
#include "opcodes.h"

using namespace std;

int main(void)
{
    string UartTemp;
    string HByte1;
    string LByte1;
    string HByte2;
    string LByte2;

    cout << "Hello World!" << endl;

    while(true)
    {
        //receive opcode
        UartTemp = Uart::receiveUart();
        switch(UartTemp){
        case power:
            //uitzetten?
            break;
        case Start:
            //?
            break;
        case Stop:
            //Stop driving and everything
            break;

        case drive:
            //meer ontvangen
            HByte1 = Uart::receiveUart();
            LByte1 = Uart::receiveUart();
            HByte2 = Uart::receiveUart();
            LByte2 = Uart::receiveUart();
            break;

        case sensors:
            //verzend gevraagde sensor info
            //welke sensor info is gevraagd?
            //meer ontvangen
            UartTemp = Uart::receiveUart();
            switch(UartTemp){
                case 1:
                    sendBumpAndWheel();
                    break;
                case 2:
                    sendWall();
                    break;
                case 3:
                    sendCliff();
                    break;
                case 4:
                    sendDistance();
                    break;
                case 5:
                    sendAngle();
                    break;
                case 6:
                    sendWallSignal();
                    break;
                case 7:
                    sendCliffSignal();
                    break;
                case 8:
                    sendLightBumper();
                    break;
                case 9:
                    //send ?
                    break;
                case 10:
                    //send ?
                    break;
                default:
                    //do nothing
                    break;
            }

            break;
        default:
            //do nothing
            break;
        }
    }



    return 0;
}

/****************************************/
/*              TO DO:                  */
