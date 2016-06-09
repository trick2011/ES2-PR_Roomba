#include <iostream>


#include "../Pipehandler/check_class.h"

using namespace std;

int main(void){
	interpreter inter;
	inter.startRoomba();
	Roombacontroller room(room);
	Walltrace autoc(inter);
	room.SetCleaningProgram(&autoc);
	
	
	return(0);
}
