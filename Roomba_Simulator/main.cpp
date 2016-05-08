#include <iostream>
#include <string>
#include <fstream>
//#include <iomanip> // setw() setfill()

#include "file.h"

//using namespace std;

/*****************************************************//*
 * This is test code and as such won't be commented on
 * any further.
 *******************************************************/
#define INTERPERTER_TEST

void testinit(Roomclass& room);

int main(){

#ifndef INTERPERTER_TEST
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
#endif
    return 0;
}

void testinit(Roomclass& room){
	Roomobjectclass object(-5,-5,0,10,Roomobjectclass::drop);
    room.roomobjects.push_back(object);
	Roomobjectclass objectb(5,-5,0,10,Roomobjectclass::drop);
    room.roomobjects.push_back(objectb);
	Roomobjectclass objectc(-5,-5,10,0,Roomobjectclass::drop);
    room.roomobjects.push_back(objectc);
	Roomobjectclass objectd(-5,5,10,0,Roomobjectclass::drop);
    room.roomobjects.push_back(objectd);
}
