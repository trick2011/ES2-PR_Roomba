#include <iostream>
#include <thread>


#include "../Cleaningprograms/basicclean.h"
#include "../Cleaningprograms/spotclean.h"
#include "../../Roomba_Interpreter/interpreter.h"
using namespace std;

int main(void){
	interpreter inter;
	inter.startRoomba();
	//Roombacontroller room(room);
	Spotclean autoc(inter);
	
	autoc.clean();
	
	cin.get();
	return(0);
}
