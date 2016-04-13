#include <iostream>
#include "interpreter.h"
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

        case sensorstreamrequest:
            //verzend gevraagde sensor info
            //welke sensor info is gevraagd?
            //meer ontvangen
            UartTemp = Uart::receiveUart();
            switch(UartTemp){
                case 1:
                    //send bumpAndWheel
                    break;
                case 2:
                    //send wall
                    break;
                case 3:
                    //send Cliff
                        //cliffLeft
                        //cliffFrontLeft
                        //cliffFrontRight
                        //cliffRight
                    break;
                case 4:
                    //send distance
                    break;
                case 5:
                    //send angle
                    //reset angle
                    break;
                case 6:
                    //send wallSignal
                    break;
                case 7:
                    //send Cliff Signal
                        //cliffLeftSignal
                        //cliffFrontLeftSignal
                        //cliffFrontRightSignal
                        //cliffRightSignal
                    break;
                case 8:
                    //send lightBumper
                        //lightBumper
                        //lightBumpLeftSignal
                        //lightBumpFrontLeftSignal
                        //lightBumpCenterLeftSignal
                        //lightBumpCenterRightSignal
                        //lightBumpFrontRightSignal
                        //lightBumpRightSignal
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
