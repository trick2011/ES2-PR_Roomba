#include <iostream>
#include <thread>

#include "roombacontroller.h"
#include "spotclean.h"
#include "autoclean.h"

using namespace std;


int main(void){
	interpreter inter;
	Roombacontroller RoombaController(inter);
    Basicclean* basic = new Autoclean(inter);
    RoombaController.CleaningProgram = basic;
	RoombaController.CleaningProgram->clean();
        
        
        
        
}
