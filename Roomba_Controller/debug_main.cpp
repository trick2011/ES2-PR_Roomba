#include <iostream>

#define VERBOSE

#include "Pipehandler/check_class.h"

using namespace std;

int main(void){
	cin.get();
	interpreter inter;
	inter.startRoomba();
	//inter.startAutoMode();
	//inter.drives(roomba::speed::SLOW);
	Roombacontroller room(inter); // kom op jongens heeft echt NIEMAND de code nagelezen? Hier declareerde ik een roombacontroller object met een INTERPRETER reference naar een ROOMBACONTROLLER object dat ik net declareer!
	check_class checker(room,inter);
	checker.pipe_checker();

}
