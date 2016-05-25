#include <iostream>
#include <thread>

#define fulldebug
#include "roombacontroller.h"
using namespace std;

int main(void){
	interpreter inter;
	Roombacontroller RoombaController(inter);
	RoombaController.DisableCleaning();
	cin.get();
	inter.startRoomba();
	cout << "init done" << endl;
	cin.get();

	AutoClean cleaningobject(inter);
	RoombaController.EnableCleaning();

//	inter.drives(roomba::speed::SLOW);
	cleaningobject.clean(); // direct cleaning
//	RoombaController.LoadCleaningProgram(); // normal cleaning
//	RoombaController.LoadCleaningProgram(); // thread cleaning


	cout << "running" << endl;
	cin.get();

    // pipe ding (&interpreter,&roombacontroller)
//    Basicclean* basic = new Autoclean();
//    Basicclean* basic;
//    Spotclean* autoo;
//    //autoo = new Autoclean;
//    RoombaController.CleaningProgram = basic;
//	RoombaController.CleaningProgram->clean();
}
