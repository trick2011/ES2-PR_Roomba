#include <iostream>
#include "inv_interpreter.h"
#include "opcodes.h"

using namespace std;

int main(void)
{
    cout << "Hello World!" << endl;

    while(true)
    {
        //receive opcode
		//receiveUart(); geeft niks meer terug en moet los aangeroepen worden
        UARTClass::receiveUart();
        UartTemp = UARTClass::getElement(); // dit werkt niet meer en moet getElement() worden
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





            break;

        case sensors:
            //verzend gevraagde sensor info
            //welke sensor info is gevraagd?
            //meer ontvangen
            UARTClass::receiveUart();
            UartTemp = UARTClass::getElement();
            switch(UartTemp){
                case 7:
                    sendBumpAndWheel();
                    break;
                case 8:
                    sendWall();
                    break;
                case 9:
                    sendCliffL();
                    break;
                case 10:
                    sendCliffFL();
                    break;
                case 11:
                    sendCliffFR();
                    break;
                case 12:
                    sendCliffR();
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
                    sendCliffL_Signal();
                    break;
                case 29:
                    sendCliffFL_Signal();
                    break;
                case 30:
                    sendCliffFR_Signal();
                    break;
                case 31:
                    sendCliffR_Signal();
                    break;
                case 45:
                    sendLightBumper();
                    break;
                case 46:
                    sendLightBumpL_Signal();
                    break;
                case 47:
                    sendLightBumpFL_Signal();
                    break;
                case 48:
                    sendLightBumpCL_Signal();
                    break;
                case 49:
                    sendLightBumpCR_Signal();
                    break;
                case 50:
                    sendLightBumpFR_Signal();
                    break;
                case 51:
                    sendLightBumpR_Signal();
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
	//}



    return 0;
}

/****************************************/
/*              TO DO:                  */
