#include <iostream>
#include <thread>

#include "roombacontroller.h"
//#include "Cleaningprograms/spotclean.h"
//#include "Cleaningprograms/autoclean.h"

using namespace std;


int main(void){
	interpreter inter;
	Roombacontroller RoombaController(inter);
    // pipe ding (&interpreter,&roombacontroller)
//    Basicclean* basic = new Autoclean();
//    Basicclean* basic;
//    Spotclean* autoo;
//    //autoo = new Autoclean;
//    RoombaController.CleaningProgram = basic;
//	RoombaController.CleaningProgram->clean();
}
