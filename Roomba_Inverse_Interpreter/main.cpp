#include <iostream>
#include "inv_interpreter.h"
#include "opcodes.h"

using namespace std;

int main(void)
{
    string UartTemp;
    char HByte1;
    char LByte1;
    char HByte2;
    char LByte2;

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
                case 7:
                    sendBumpAndWheel();
                    break;
                case 8:
                    sendWall();
                    break;
                case 9:
                    sendCliffLeft();
                    break;
                case 10:
                    sendCliffFrontLeft();
                    break;
                case 11:
                    sendCliffFrontRight();
                    break;
                case 12:
                    sendCliffRight();
                    break;
                   case 19:
                    sendDistance();
                    break;
                case 20:
                    sendAngle();
                    break;
                case 27:
                    sendWallSignal();
                    //2 bytes
                    break;
                case 28:
                    sendCliffLeftSignal();
                    break;
                case 29:
                    sendCliffFrontLeftSignal();
                    break;
                case 30:
                    sendCliffFrontSignal();
                    break;
                case 31:
                    sendCliffRightSignal();
                    break;
                case 45:
                    sendLightBumper();
                    break;
                case 46:
                    sendLightBumpLeftSignal();
                    break;
                case 47:
                    sendLightBumpFrontLeftSignal();
                    break;
                case 48:
                    sendLightBumpCenterLeftSignal();
                    break;
                case 49:
                    sendLightBumpCenterRightSignal();
                    break;
                case 50:
                    sendLightBumpFrontRightSignal();
                    break;
                case 51:
                    sendLightBumpRightSignal();
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
