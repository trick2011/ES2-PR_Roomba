#include <iostream>


#include "../../Pipehandler/check_class.h"

using namespace std;

int main(void){
	cin.get();
	interpreter inter;
	inter.startRoomba();
	//inter.startAutoMode();
	//inter.drives(roomba::speed::SLOW);
	Roombacontroller room(room);
	check_class checker(room,inter);
	checker.pipe_checker();


	cin.get();
}
