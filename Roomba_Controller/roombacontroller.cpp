#include "roombacontroller.h"


void Roombacontroller::SetCleaningProgram(Basicclean* input)
{

	if(CleaningProgram != NULL){ // if Cleaningprogram is pointing to another program
		Basicclean::DisableCleaning(); // this is a static function so there is in this instance no object needed
		delete CleaningProgram; // delete the other program
	}

	CleaningProgram = input; // install new program
	//input->clean(); // execute new program

	//typeid(CleaningProgram).

	//thread* tmp;

//	this works // so with type deduction will work
//	AutoClean* tmpa;
//	tmpa  = dynamic_cast<AutoClean*>(CleaningProgram);
//	tmp = new thread(*tmpa);

	//tmp = new thread(dynamic_cast<AutoClean*>(CleaningProgram));

	if(typeid(*CleaningProgram).hash_code() == typeid(AutoClean).hash_code()){
		AutoClean* clean = dynamic_cast<AutoClean*>(CleaningProgram);
		CleaningThread = new thread(*clean);
	}

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
