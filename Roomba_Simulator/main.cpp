#include <iostream>
//#include <iomanip> // setw() setfill()
#include <string>
#include <fstream>

#include "file.h"

//using namespace std;

/*****************************************************//*
 * This is test code and as such won't be commented on
 * any further.
 *******************************************************/

void testinit(roomclass& room);

int main(){

    roomclass room;
    testinit(room);

    cout << room.roomba->iPosHor << " " << room.roomba->iPosVer << endl;
    room.roomba->setangle(-135/*135+180*/);
    room.roomba->setspeed(1);
#ifndef TIMER_DEBUG
    while(1){
        cout << *room.roomba;
        cout << *room.sensors;

//        cout << room.roomba->iPosHor << "   " << room.roomba->iPosVer << "   " << room.sensors->getbBumpLeft() << room.sensors->getbBumpRight();

//        cout << "   " << room.sensors->getbBumpLeft() << room.sensors->getbBumpRight();
//        cout << room.sensors->getCliffLeft() << room.sensors->getCliffFrontLeft() << room.sensors->getCliffFrontRight();
//        cout << room.sensors->getCliffRight() << endl;
    }
#endif
#ifdef TIMER_DEBUG
    for(unsigned int i=0;i<8;++i){
        cout << *room.roomba;
        cout << *room.sensors;
        room.roomba->drive();
    }
#endif
    return 0;
}

void testinit(roomclass& room){
    roomobjectclass object(-5,-5,0,10,roomobjectclass::drop);
    room.roomobjects.push_back(object);
    roomobjectclass objectb(5,-5,0,10,roomobjectclass::drop);
    room.roomobjects.push_back(objectb);
    roomobjectclass objectc(-5,-5,10,0,roomobjectclass::drop);
    room.roomobjects.push_back(objectc);
    roomobjectclass objectd(-5,5,10,0,roomobjectclass::drop);
    room.roomobjects.push_back(objectd);
}
