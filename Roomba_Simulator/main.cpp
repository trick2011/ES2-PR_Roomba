#include "file.h"
#include "inv_interpreter.h"
#include "test.h"

/*****************************************************//*
 * This is test code and as such won't be commented on
 * any further.
 *******************************************************/
//#define INTERPERTER_TEST

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
