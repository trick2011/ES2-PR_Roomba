#include <iostream>
#include <thread>

#define fulldebug
#include "roombacontroller.h"
#include "Pipehandler/check_class.h"
//INITIALIZE_EASYLOGGINGPP
using namespace std;

int main(void){
	interpreter inter;
	Roombacontroller RoombaController(inter);
//    check_class check(RoombaController,inter);
//    check.pipe_checker();

	inter.stopRoomba();
	cin.get();

	RoombaController.DisableCleaning();
	cin.get();
	inter.startRoomba();
	cout << "init done" << endl;
	cin.get();

	AutoClean cleaningobject(inter);
	//Walltrace cleaningobject(inter);
	RoombaController.EnableCleaning();

//	inter.drives(roomba::speed::SLOW);
//	cleaningobject.clean(); // direct cleaning
//	RoombaController.LoadCleaningProgram(cleaningobject); // normal cleaning
	RoombaController.SetCleaningProgram(&cleaningobject); // thread cleaning



	cout << "running" << endl;

	cin.get();

	inter.stopRoomba();

//	pipe ding (&interpreter,&roombacontroller)
//	Basicclean* basic = new Autoclean();
//	Basicclean* basic;
//	Spotclean* autoo;
//	//autoo = new Autoclean;
//	RoombaController.CleaningProgram = basic;
//	RoombaController.CleaningProgram->clean();
}
