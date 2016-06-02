//#define debug
//#define fulldebug

#include <iostream>
#include "interpreter.h"
#include "opcodes.h"
#include "../Roomba_UART/uart.h"

using namespace std;

int main(int argc, char *argv[])
{
    interpreter *Peter;
    Peter = new interpreter;
    while(1)
    {
    system("clear");
    cout << "Welcome to Roomba Interpreter" << endl << endl;

    cout << "Options:"                                  << endl <<
            "1. Start Roomba"                           << endl <<
            "2. Drive roomba"                           << endl <<
            "3. turn Roomba"                            << endl <<
            "4. Start automode - receives from sensors" << endl <<
            "       (exit with ctrl-c)"                 << endl <<
            "5. Stop Roomba"                            << endl <<
            "6. Brushes"                                << endl;

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
            cout<<"45 degrees left or right? (l/r): ";
            char a;
            cin>>a;
            if(a == 'l')Peter->turnLeft(); // -90 graden
            if(a == 'r')Peter->turnRight(); //90 graden
            break;
        case 4:
            Peter->startAutoMode();
            break;
        case 5:
            Peter->stopRoomba();
            break;
        case 6:
        {
            //Peter->brushes(1);
            cout<<"Which brush do you want?"    << endl <<
                  "0 - no brush"                << endl <<
                  "1 - side brush"              << endl <<
                  "2 - main brush"              << endl <<
                  "3 - both"                    << endl;
            int i;
            cin>>i;
            Peter->brushes(i);

            break;
        }
        case 7:
            Peter->printTest();
        case 8:
        {
            std::cout<<"case 8"<<std::endl;
            Peter->startAutoMode();
            int i = 0;
            while(1)
            {
                std::cout<<"case 8"<<std::endl;
                do
                {
                    Peter->drives(0);
                    while(  !Peter->getLightBumper()|| !Peter->Cliff.bLeft || !Peter->Cliff.bFrontLeft || 
                            !Peter->Cliff.bFrontRight || !Peter->Cliff.bRight || !Peter->Bumps.bLeft ||
                            !Peter->Bumps.bRight )
                        {;
                    }
                }while( Peter->slowTillStop());

                Peter->drives(4);
                usleep(100);
                switch(i)
                {
                    case 0:
                        Peter->turnRight();
                        Peter->drives(0);
                        for(unsigned int i = 0 ; i < 100 ; i += Peter->getDistance())
                        {
                            if(Peter->Cliff.bLeft || Peter->Cliff.bFrontLeft || 
                            Peter->Cliff.bFrontRight || Peter->Cliff.bRight || Peter->Bumps.bLeft ||
                            Peter->Bumps.bRight )
                            {
                                Peter->drives(3);
                                Peter->drives(4);
                                usleep(100);
                                break;
                            }
                        }
                        Peter->turnRight();
                        i = 1;
                        break;
                    case 1:
                        
                        Peter->turnLeft();
                        Peter->drives(0);
                        for(unsigned int i = 0 ; i < 100 ; i += Peter->getDistance())
                        {
                            if(Peter->Cliff.bLeft || Peter->Cliff.bFrontLeft || 
                            Peter->Cliff.bFrontRight || Peter->Cliff.bRight || Peter->Bumps.bLeft ||
                            Peter->Bumps.bRight  )
                            {
                                Peter->drives(3);
                                Peter->drives(4);
                                usleep(100);
                                break;
                            }
                            
                        }
                        Peter->turnLeft();
                        i = 0;
                        break;
                    default:
                        i=0;
                        break;
                }
                

            }
            break;
        }
        case 9:
        {
            int i = 0;
            while(1)
            {
                do
                {
                    Peter->drives(0);
                    while(!Peter->getLightBumper()|| !(Peter->getBumpLeft() || Peter->getBumpRight() ||
                        Peter->getCliffLeftSignal() || Peter->getCliffFrontLeftSignal() || Peter->getCliffFrontRightSignal() ||
                        Peter->getCliffRightSignal()))
                        {;
                    }
                }while( Peter->slowTillStop());

                Peter->drives(4);
                usleep(100);
                switch(i)
                {
                    case 0:
                        Peter->turnRight();
                        Peter->drives(0);
                        for(unsigned int i = 0 ; i < 30 ; i += Peter->getDistance())
                        {
                            if(Peter->getBumpLeft() || Peter->getBumpRight() ||
                        Peter->getCliffLeftSignal() || Peter->getCliffFrontLeftSignal() || Peter->getCliffFrontRightSignal() ||
                        Peter->getCliffRightSignal() )
                            {
                                Peter->drives(3);
                                Peter->drives(4);
                                usleep(100);
                                break;
                            }
                        }
                        Peter->turnRight();
                        i = 1;
                        break;
                    case 1:
                        
                        Peter->turnLeft();
                        Peter->drives(0);
                        for(unsigned int i = 0 ; i < 30 ; i += Peter->getDistance())
                        {
                            if(Peter->getBumpLeft() || Peter->getBumpRight() ||
                        Peter->getCliffLeftSignal() || Peter->getCliffFrontLeftSignal() || Peter->getCliffFrontRightSignal() ||
                        Peter->getCliffRightSignal() )
                            {
                                Peter->drives(3);
                                Peter->drives(4);
                                usleep(100);
                                break;
                            }
                            
                        }
                        Peter->turnLeft();
                        i = 0;
                        break;
                    default:
                        i=0;
                        break;
                }
            }
            break;
        }
        default:
            break;
		
        }
    }

    return 0;
}

/****************************************/
/*              TO DO:                  */
/*   - turn functie casting             */
/*   - drive functie controleren        */
/*   - 8 bits functies correct maken    */
/*   - functies contoleren op juiste    */
/*      waardes                         */
/*                                      */
/****************************************/
