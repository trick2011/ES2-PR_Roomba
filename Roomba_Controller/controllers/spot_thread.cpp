#include <iostream>


#include "../Pipehandler/check_class.h"

using namespace std;

int main(void){
	interpreter inter;
	inter.startRoomba();
	Roombacontroller room(room);
	inter.startRoomba();
	Spotclean autoc(inter);
	room.SetCleaningProgram(&autoc);
	
	return(0);
}
