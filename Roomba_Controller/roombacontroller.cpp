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
//		CleaningThread->join();
		//std::terminate()
		//CleaningThread->abo
		CleaningThread->join();

		delete CleaningThread;
		delete CleaningProgram; // delete the other program
		CleaningThread = NULL;
		CleaningProgram = NULL;
	}

	Basicclean::EnableCleaning();
	CleaningProgram = input; // install new program

	CleaningThread = new thread(ref(*CleaningProgram) ); // reference wrapper // start thread
}

void Roombacontroller::EnableCleaning(){
	Basicclean::EnableCleaning();// this is a static function so there is in this instance no object needed
}

void Roombacontroller::DisableCleaning(){
	cerr << "1.1" << endl;
	Basicclean::DisableCleaning();// this is a static function so there is in this instance no object needed
	cerr << "1.2" << endl;
	if(CleaningProgram != NULL){
		if(CleaningThread != NULL){
			cerr << "1.3" << endl;
			CleaningThread->join();
			cerr << "1.4" << endl;
			delete CleaningThread;
			cerr << "1.5" << endl;
			delete CleaningProgram;
			cerr << "1.6" << endl;
			CleaningThread = NULL;
			cerr << "1.7" << endl;
			CleaningProgram = NULL;
			cerr << "1.8" << endl;
		}
	}
	cerr << "1.9" << endl;


}
