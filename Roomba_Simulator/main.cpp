#include <iostream>
//#include <iomanip> // setw() setfill()
#include <string>

#include "file.h"

using namespace std;

int main()
{

    //roomobjectclass *roomba;
    //roomba = new roombaclass(null);
    //delete roomba;
    roomclass room;

    cout << room.roomba->iPosHor << " " << room.roomba->iPosVer << endl;
    room.roomba->setangle(-45);
    room.roomba->setspeed(1);
    for(int i=0;i<12;i++){
        room.roomba->drive();
        cout << room.roomba->iPosHor << "   " << room.roomba->iPosVer << "      " << room.sensors->getbBumpLeft() << "      " << room.sensors->getbBumpRight() << endl;
        //cout << "---------------------" << endl;
    }
    cout << room.roomba->iPosHor << "   " << room.roomba->iPosVer << "      " << room.sensors->getbBumpLeft() << "      " << room.sensors->getbBumpRight() << endl;

    //cout << room.roomba->iPosHor << " " << room.roomba->iPosVer << endl;
    room.roomba->setangle(-225);
    room.roomba->setspeed(1);
    for(int i=0;i<16;i++){
        room.roomba->drive();
        cout << room.roomba->iPosHor << "   " << room.roomba->iPosVer << "      " << room.sensors->getbBumpLeft() << "      " << room.sensors->getbBumpRight() << endl;
        //cout << "---------------------" << endl;
    }
    return 0;
}

