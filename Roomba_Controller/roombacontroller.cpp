#include "roombacontroller.h"


void Roombacontroller::SetCleaningProgram(Basicclean* input)
{

	if(CleaningProgram != NULL) // if Cleaningprogram is pointing to another program // also the brackets {} are implied in single line code
		delete CleaningProgram; // delete the other program

	CleaningProgram = input; // install new program
	input->clean(); // execute new program

	thread tmp;

//	Timerclass timer(*this,0.5);
//    thread tTimerThread(timer);
//    tTimerThread.detach();
	//Moet gethread
}

void Roombacontroller::Enablesetter()
{
//	CleaningProgram->EnableCleaning();
	//cln::bEnableCleaning = true;
}

void Roombacontroller::Disablesetter()
{
//	CleaningProgram->DisableCleaning();
	//cln::bEnableCleaning = false;
}
