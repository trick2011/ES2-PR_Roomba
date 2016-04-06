#include <iostream>
#include "interpreter.h"
#include "opcodes.h"
#include "../Roomba_Interpreter/UART/uart.h"

#define debug
using namespace std;

int main(int argc, char *argv[])
{
    //if(argc == 2)
    //{

    interpreter *Peter;
    Peter = new interpreter;
    while(1)
    {
#ifndef debug
    system("clear");
#endif
    cout << "Welcome to Roomba Interpreter" << endl << endl;

    cout << "Options:" << endl <<
            "1. Start Roomba" << endl <<
            "2. Drive roomba" << endl <<
            "3. turn Roomba" << endl <<
            "4. Start automode - receives from sensors" << endl <<
            "       (exit with ctrl-c)"<< endl <<
	    "5. Stop Roomba" << endl <<
        "6. Brushes"<<endl;

        int i = 0;
        cout << "choice: ";
        cin>>i;
        switch (i) {
        case 1:
            Peter->startRoomba();
            break;
        case 2:
            cout << "give speed 0,1 or 2: ";
            int s;
            cin>>s;
            cout<<endl;
            Peter->drives(s);
            break;
        case 3:
            cout<<"give angle: ";
            int16_t a;
            cin>>a;
            cout<<endl;
            Peter->turnRoomba(a);
            break;
        case 4:
            Peter->autoMode();
            break;
        case 5:
            Peter->stopRoomba();
            break;
        case 6:
            //Peter->brushes(1);
            cout<<"Which brush do you want?" << endl<<
                  "0 - no brush"<<endl<<
                  "1 - side brush"<<endl<<
                  "2 - main brush"<<endl<<
                  "3 - both"<<endl;
            int i;
            cin>>i;
            Peter->brushes(i);

            break;
        default:
            break;
		
        }
    }
    //}
    //else
    /*{
        UARTClass *u = new UARTClass("/dev/ttyAMA0");

        u->sendUart(122);
        cout<<u->receiveUart()<<endl;
    }*/




    return 0;
}

/****************************************/
/*              TO DO:                  */
/*   - turn functie casting             */
/*   - drive functie controleren        */
/*   - evt liedje functie               */
/*   - 8 bits functies correct maken    */
/*   - functies contoleren op juiste    */
/*      waardes                         */
/*                                      */
/****************************************/
