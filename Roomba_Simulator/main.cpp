#include <iostream>
//#include <iomanip> // setw() setfill()
#include <string>
#include <fstream>

#include "file.h"

using namespace std;

/*****************************************************//*
 * This is test code and as such won't be commented on
 * any further.
 *******************************************************/

int main(){
    ofstream ofp("output.txt");


    roomclass room;

    cout << room.roomba->iPosHor << " " << room.roomba->iPosVer << endl;
    room.roomba->setangle(-135/*135+180*/);
    room.roomba->setspeed(1);
#ifndef TIMER_DEBUG
    while(1){
        cout << *room.roomba;
        cout << *room.sensors;

        ofp << *room.roomba;
        ofp << *room.sensors;

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

        ofp << *room.roomba;
        ofp << *room.sensors;
        room.roomba->drive();
    }
#endif
    return 0;
}

