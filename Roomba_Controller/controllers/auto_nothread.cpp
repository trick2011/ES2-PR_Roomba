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
	AutoClean autoc(inter);
	
	autoc.clean();
	
	cin.get();
	return(0);
}
