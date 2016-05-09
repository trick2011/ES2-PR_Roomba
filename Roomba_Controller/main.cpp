#include <iostream>
#include <thread>

#include "roombacontroller.h"
#include "spotclean.h"

using namespace std;


int main(void){
	interpreter inter;
	Roombacontroller RoombaController(inter);
	Spotclean* spot = new Spotclean(inter);
	RoombaController.CleaningProgram = spot;
	RoombaController.CleaningProgram->clean();
        
        
        
        
}
