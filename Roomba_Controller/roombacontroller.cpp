#include "roombacontroller.h"


void Roombacontroller::SetCleaningProgram(Basicclean* input)
{

	if(CleaningProgram != NULL){ // if Cleaningprogram is pointing to another program
		Basicclean::DisableCleaning(); // this is a static function so there is in this instance no object needed

		// test if really stopped runnning
		while(Basicclean::getProcessPID() != 0){}

		delete CleaningProgram; // delete the other program
	}

	CleaningProgram = input; // install new program

	CleaningThread = new thread(ref(*CleaningProgram) ); // reference wrapper // start thread

	//// this is not a clean solution but we are unable to find a way to dyanmically define the derived type //<< fixed with std::ref
//	if(typeid(*CleaningProgram).hash_code() == typeid(AutoClean).hash_code()){
//		AutoClean* clean = dynamic_cast<AutoClean*>(CleaningProgram);
//		CleaningThread = new thread(*clean);
//	}
//	if(typeid(*CleaningProgram).hash_code() == typeid(Cell).hash_code()){
//		Cell* clean = dynamic_cast<Cell*>(CleaningProgram);
//		CleaningThread = new thread(*clean);
//	}
//	if(typeid(*CleaningProgram).hash_code() == typeid(Dock).hash_code()){
//		Dock* clean = dynamic_cast<Dock*>(CleaningProgram);
//		CleaningThread = new thread(*clean);
//	}
//	if(typeid(*CleaningProgram).hash_code() == typeid(Spotclean).hash_code()){
//		Spotclean* clean = dynamic_cast<Spotclean*>(CleaningProgram);
//		CleaningThread = new thread(*clean);
//	}
//	if(typeid(*CleaningProgram).hash_code() == typeid(Walltrace).hash_code()){
//		Walltrace* clean = dynamic_cast<Walltrace*>(CleaningProgram);
//		CleaningThread = new thread(*clean);
//	}

	//CleaningThread


//	Timerclass timer(*this,0.5);
//    thread tTimerThread(timer);
//    tTimerThread.detach();
	//Moet gethread
}

void Roombacontroller::EnableCleaning(){
	Basicclean::EnableCleaning();// this is a static function so there is in this instance no object needed
}

void Roombacontroller::DisableCleaning(){
	Basicclean::DisableCleaning();// this is a static function so there is in this instance no object needed
}
