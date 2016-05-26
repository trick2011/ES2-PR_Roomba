#include <iostream>
#include <string>
#include <fstream>
#include <thread>
//#include <iomanip> // setw() setfill()

#include "file.h"
#include "inv_interpreter.h"

//using namespace std;

/*****************************************************//*
 * This is test code and as such won't be commented on
 * any further.
 *******************************************************/
//#define INTERPERTER_TEST

void testinit(Roomclass& room);
void testinitBIG(Roomclass& room);

void timerrun(Roomclass* room){
	cout << room->roomba->iPosHor << " " << room->roomba->iPosVer << endl;
	int counter=0;
	while(1){
		cout << *room->roomba;
		cout << *room->sensors;
		sleep(1);
		cout << counter++ << endl;
	}
}
#define INTERPERTER_TEST

int main(){
#ifdef INTERPERTER_TEST
	Roomclass room;
	Inv_interpreter interpeter(room);
	testinitBIG(room);

	thread a(timerrun,&room);
	interpeter.mainroutine();

	while (1) {}
#endif

#ifndef INTERPERTER_TEST
	Roomclass room;
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

void testinitBIG(Roomclass& room){
	Roomobjectclass object(-20,-20,0,40,Roomobjectclass::wall);
	room.roomobjects.push_back(object);
	Roomobjectclass objectb(20,-20,0,40,Roomobjectclass::wall);
	room.roomobjects.push_back(objectb);
	Roomobjectclass objectc(-20,-20,40,0,Roomobjectclass::wall);
	room.roomobjects.push_back(objectc);
	Roomobjectclass objectd(-20,20,40,0,Roomobjectclass::wall);
	room.roomobjects.push_back(objectd);
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
