#include <iostream>
#include <thread>

#include "roombacontroller.h"
#include "spotclean.h"
#include "autoclean.h"

using namespace std;


int main(void){
	interpreter inter;
	Roombacontroller RoombaController(inter);
//    Basicclean* basic = new Autoclean();
    Basicclean* basic;
    Autoclean* autoo;
    autoo = new Autoclean;
    RoombaController.CleaningProgram = basic;
	RoombaController.CleaningProgram->clean();       
}
