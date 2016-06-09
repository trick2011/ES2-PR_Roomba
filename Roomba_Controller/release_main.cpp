#include <iostream>


#include "Pipehandler/check_class.h"

using namespace std;

int main(void){
	interpreter inter;
	inter.startRoomba();
	Roombacontroller room(room);
	check_class checker(room,inter);
	checker.pipe_checker();
}
