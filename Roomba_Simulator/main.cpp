#include <iostream>
//#include <iomanip> // setw() setfill()
#include <string>

#include "file.h"

using namespace std;

/*****************************************************//*
 * This is test code and as such won't be commented on
 * any further.
 *******************************************************/

int main()
{

    //roomobjectclass *roomba;
    //roomba = new roombaclass(null);
    //delete roomba;
    roomclass room;

    cout << room.roomba->iPosHor << " " << room.roomba->iPosVer << endl;
    room.roomba->setangle(135+180);
    room.roomba->setspeed(1);
//    for(int i=0;i<12;i++){
//        room.roomba->drive();
//        cout << room.roomba->iPosHor << "   " << room.roomba->iPosVer << "      " << room.sensors->getbBumpLeft() << "      " << room.sensors->getbBumpRight() << endl;
//        //cout << "---------------------" << endl;
//    }
//    cout << room.roomba->iPosHor << "   " << room.roomba->iPosVer << "      " << room.sensors->getbBumpLeft() << "      " << room.sensors->getbBumpRight() << endl;

//    //cout << room.roomba->iPosHor << " " << room.roomba->iPosVer << endl;
//    room.roomba->setangle(180);
//    room.roomba->setspeed(1);
//    for(int i=0;i<14;i++){
//        room.roomba->drive();
//        cout << room.roomba->iPosHor << "   " << room.roomba->iPosVer << "      " << room.sensors->getbBumpLeft() << "      " << room.sensors->getbBumpRight() << endl;
//        //cout << "---------------------" << endl;
//    }
    room.roomba->drive();
    while(1){
        cout << room.roomba->iPosHor << "   " << room.roomba->iPosVer << "      " << room.sensors->getbBumpLeft() << "      " << room.sensors->getbBumpRight() << endl;
    }
    return 0;
}

