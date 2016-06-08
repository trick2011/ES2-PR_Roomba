#include "roombacontroller.h"


void Roombacontroller::SetCleaningProgram(Basicclean* input)
{


	if(!CleaningProgram){ // if Cleaningprogram is pointing to another program
		Basicclean::DisableCleaning(); // this is a static function so there is in this instance no object needed

		// test if really stopped runnning
		while(Basicclean::getProcessPID() != 0){}

		//cout << CleaningThread->joinable() << endl;
//		CleaningThread->join();
		//std::terminate()
		//CleaningThread->abo


		delete CleaningThread;
		delete CleaningProgram; // delete the other program
	}

	Basicclean::EnableCleaning();
	CleaningProgram = input; // install new program

	CleaningThread = new thread(ref(*CleaningProgram) ); // reference wrapper // start thread
}

void Roombacontroller::EnableCleaning(){
	Basicclean::EnableCleaning();// this is a static function so there is in this instance no object needed
}

void Roombacontroller::DisableCleaning(){
	Basicclean::DisableCleaning();// this is a static function so there is in this instance no object needed

	while(Basicclean::getEnableCleaning() != false);

	if(CleaningProgram != 0x00){
		cout << endl;
	}
//	CleaningThread->join();

//	delete CleaningThread;
//	delete CleaningProgram;
}
