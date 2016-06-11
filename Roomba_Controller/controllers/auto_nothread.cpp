#include <iostream>
#include <thread>


#include "../Cleaningprograms/basicclean.h"
#include "../Cleaningprograms/autoclean.h"
#include "../../Roomba_Interpreter/interpreter.h"
using namespace std;

int main(void){
	interpreter inter;
	inter.startRoomba();
	//Roombacontroller room(room);
	inter.startRoomba();
	//usleep(100);
	inter.startRoomba();

	AutoClean autoc(inter);
	
	autoc.clean();
	
	cin.get();
	return(0);
}
