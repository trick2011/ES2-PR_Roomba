#include "roombacontroller.h"

Roombacontroller::~Roombacontroller(){
	Basicclean::DisableCleaning();
}

void Roombacontroller::SetCleaningProgram(Basicclean* input)
{


	if(CleaningProgram != NULL){ // if Cleaningprogram is pointing to another program
		Basicclean::DisableCleaning(); // this is a static function so there is in this instance no object needed

		// test if really stopped runnning
		//while(Basicclean::getProcessPID() != 0){}

		//cout << CleaningThread->joinable() << endl;
		CleaningThread->join();
		//std::terminate()
		//CleaningThread->abo
//		CleaningThread->join();

		delete CleaningThread;
		delete CleaningProgram; // delete the other program
		//terminate();
		CleaningThread = NULL;
		CleaningProgram = NULL;
		//pipefillerthread = new thread(ref(*filler));
	}

	Basicclean::EnableCleaning();
	CleaningProgram = input; // install new program

	CleaningThread = new thread(ref(*CleaningProgram) ); // reference wrapper // start thread
//	CleaningThread->detach();
	//CleaningProgram->TheThread = CleaningThread;
}

void Roombacontroller::EnableCleaning(){
	Basicclean::EnableCleaning();// this is a static function so there is in this instance no object needed
}

void Roombacontroller::DisableCleaning(){
	Basicclean::DisableCleaning();// this is a static function so there is in this instance no object needed
	if(CleaningProgram != NULL){
		if(CleaningThread != NULL){
			CleaningThread->join();
			//CleaningThread->detach();
			delete CleaningThread;
			delete CleaningProgram;
			//terminate();
			CleaningThread = NULL;
			CleaningProgram = NULL;
			//pipefillerthread = new thread(ref(*filler));
		}
	}
}
