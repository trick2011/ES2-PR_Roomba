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
    check_class check(RoombaController,inter);
    check.pipe_checker();

//	RoombaController.DisableCleaning();
//	cin.get();
//	inter.startRoomba();
//	cout << "init done" << endl;
//	cin.get();

//	AutoClean cleaningobject(inter);
//	RoombaController.EnableCleaning();

////	inter.drives(roomba::speed::SLOW);
////	cleaningobject.clean(); // direct cleaning
////	RoombaController.LoadCleaningProgram(); // normal cleaning
//	RoombaController.SetCleaningProgram(&cleaningobject); // thread cleaning


//	cout << "running" << endl;
//	cin.get();

    // pipe ding (&interpreter,&roombacontroller)
//    Basicclean* basic = new Autoclean();
//    Basicclean* basic;
//    Spotclean* autoo;
//    //autoo = new Autoclean;
//    RoombaController.CleaningProgram = basic;
//	RoombaController.CleaningProgram->clean();
}
