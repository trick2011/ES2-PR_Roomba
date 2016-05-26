#include "test.h"

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
