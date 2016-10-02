#include <iostream>

#define VERBOSE

#include "Pipehandler/check_class.h"

using namespace std;

int main(void){
	//cin.get();
	interpreter inter;
	inter.startRoomba();
	//inter.startAutoMode();
	//inter.drives(roomba::speed::SLOW);
	Roombacontroller room(inter);
	check_class checker(&room,&inter);
	checker();
	
	inter.brushes(roomba::brush::NOBRUSH);
	inter.stopRoomba();
	
	return(0);
}
