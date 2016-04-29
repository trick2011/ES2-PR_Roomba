#include <iostream>
#include "inv_interpreter.h"
#include "opcodes.h"

using namespace std;
using namespace roomba;

int main(void)
{
    cout << "Hello World!" << endl;

    inv_interpreter inv_interpreter_OBJECT;
    UARTClass UARTClass_OBJECT;
    while(true)
    {
        //receive opcode
		//receiveUart(); geeft niks meer terug en moet los aangeroepen worden
        UARTClass_OBJECT.receiveUart();
        inv_interpreter_OBJECT.UartTemp = UARTClass_OBJECT.getElement(); // dit werkt niet meer en moet getElement() worden
        switch(inv_interpreter_OBJECT.UartTemp){
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
            inv_interpreter_OBJECT.drive();
            break;

        case sensors:
            //verzend gevraagde sensor info
            //welke sensor info is gevraagd?
            //meer ontvangen
            UARTClass_OBJECT.receiveUart();
            inv_interpreter_OBJECT.UartTemp = UARTClass_OBJECT.getElement();
            switch(inv_interpreter_OBJECT.UartTemp){
                case 7:
                    inv_interpreter_OBJECT.sendBumpAndWheel();
                    break;
                case 8:
                    inv_interpreter_OBJECT.sendWall();
                    break;
                case 9:
                    inv_interpreter_OBJECT.sendCliffL();
                    break;
                case 10:
                    inv_interpreter_OBJECT.sendCliffFL();
                    break;
                case 11:
                    inv_interpreter_OBJECT.sendCliffFR();
                    break;
                case 12:
                    inv_interpreter_OBJECT.sendCliffR();
                    break;
                   case 19:
                    inv_interpreter_OBJECT.sendDistance();
                    break;
                case 20:
                    inv_interpreter_OBJECT.sendAngle();
                    break;
                case 27:
                    inv_interpreter_OBJECT.sendWallSignal();
                    //2 bytes
                    break;
                case 28:
                    inv_interpreter_OBJECT.sendCliffL_Signal();
                    break;
                case 29:
                    inv_interpreter_OBJECT.sendCliffFL_Signal();
                    break;
                case 30:
                    inv_interpreter_OBJECT.sendCliffFR_Signal();
                    break;
                case 31:
                    inv_interpreter_OBJECT.sendCliffR_Signal();
                    break;
                case 45:
                    inv_interpreter_OBJECT.sendLightBumper();
                    break;
                case 46:
                    inv_interpreter_OBJECT.sendLightBumpL_Signal();
                    break;
                case 47:
                    inv_interpreter_OBJECT.sendLightBumpFL_Signal();
                    break;
                case 48:
                    inv_interpreter_OBJECT.sendLightBumpCL_Signal();
                    break;
                case 49:
                    inv_interpreter_OBJECT.sendLightBumpCR_Signal();
                    break;
                case 50:
                    inv_interpreter_OBJECT.sendLightBumpFR_Signal();
                    break;
                case 51:
                    inv_interpreter_OBJECT.sendLightBumpR_Signal();
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
