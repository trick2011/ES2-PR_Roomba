#include "check_class.h"
//constructor
check_class::check_class(Roombacontroller& roomref,interpreter& inter):com_class(),inter{inter},roomref{roomref}{
	filler = new pipe_filler(inter,*this);
	pipefillerthread = new thread(ref(*filler));
}

void check_class::operator ()(){
	pipe_checker();
}

#ifndef DRY_DEBUG // actual implementation
void check_class::pipe_checker(){
	char PipeCommand = 0x00;
	while(1){
		PipeCommand = 0;
		PipeCommand = readFIFO();
		if(PipeCommand == pipeempty)
			continue;

		switch(PipeCommand){
		case 'e':	//AutoClean
	//		Autotmp* a;
			inter.drives(roomba::speed::SLOW);
			Cleaningprogram = new AutoClean(inter);
//			//Cleaningprogram->clean();
//			roomref.EnableCleaning();
			roomref.SetCleaningProgram(Cleaningprogram);
			//while(1){}
			Cleaningprogram = NULL;
#ifdef VERBOSE
			cout<<"AutoClean ON"<<endl;
#endif
			break;
		case 'f':	//CellClean
//			Cleaningprogram = new Cell(inter);
//			roomref.LoadCleaningProgram(Cleaningprogram);
//			Cleaningprogram = NULL;
#ifdef VERBOSE
			cout<<"CellClean ON"<<endl;
#endif
			break;
		case 'g':	//Walltrace
			Cleaningprogram = new Walltrace(inter);
			roomref.LoadCleaningProgram(Cleaningprogram);
			Cleaningprogram = NULL;
#ifdef VERBOSE
			cout<<"Walltrace ON"<<endl;
#endif
			break;
		case 'h':	//Spotclean
			Cleaningprogram = new Spotclean(inter);
			roomref.LoadCleaningProgram(Cleaningprogram);
			Cleaningprogram = NULL;
#ifdef VERBOSE
			cout<<"Spotclean ON"<<endl;
#endif
			break;
		case 'i':	//manclean
			//Manclean* manclean_object = new Manclean();
			//roomref.stelcleaningin(manclean_object);
#ifdef VERBOSE
			cout<<"ManClean ON"<<endl;
#endif
			break;
		case 'j':	//Stop Clean
			//roomref.stop();
			roomref.DisableCleaning();
#ifdef VERBOSE
			cout<<"Stopped all Clean programs"<<endl;
#endif
			break;
		case 'k':	//Dock
			//roomref.dock();
#ifdef VERBOSE
			cout<<"Dock Roomba"<<endl;
#endif
			break;
		default :
			break;
		}
        sleep(1);
	}
//	char cRcommand;
//	cRcommand = readFIFO();
//	function_type_checker(cRcommand);

//	if(cRcommand == 'o'){
//		cout<<"pipe empty"<<endl;
//	}
//	else{
//		function_type_checker(cRcommand);
//	}
}
#endif
#ifdef DRY_DEBUG // terminal testing
void check_class::pipe_checker(){
    char PipeCommand = 0x00;
    while(1){
        PipeCommand = 0;
        PipeCommand = readFIFO();
        if(PipeCommand == pipeempty)
            continue;

        switch(PipeCommand){
        case 'e':	//AutoClean
    //		Autotmp* a;
            cout<<"AutoClean ON"<<endl;
            break;
        case 'f':	//CellClean

            cout<<"CellClean ON"<<endl;
            break;
        case 'h':	//Walltrace

            cout<<"Walltrace ON"<<endl;
            break;
        case 'g':	//Spotclean

            cout<<"Spotclean ON"<<endl;
            break;
        case 'i':	//manclean
            //Manclean* manclean_object = new Manclean();
            //roomref.stelcleaningin(manclean_object);
            cout<<"ManClean ON"<<endl;
            break;
        case 'j':	//Stop Clean
            //roomref.stop();
            cout<<"Stopped all Clean programs"<<endl;
            break;
        case 'k':	//Dock
            //roomref.dock();
            cout<<"Dock Roomba"<<endl;
            break;
        default :
            break;
        }
        //cout.flush();
    }
//	char cRcommand;
//	cRcommand = readFIFO();
//	function_type_checker(cRcommand);

//	if(cRcommand == 'o'){
//		cout<<"pipe empty"<<endl;
//	}
//	else{
//		function_type_checker(cRcommand);
//	}
}

#endif

//pipe checker // old
//void check_class::pipe_checker(){
//	char cRcommand;
//	cRcommand = readFIFO();
//	function_type_checker(cRcommand);

//	if(cRcommand == 'o'){
//		cout<<"pipe empty"<<endl;
//	}
//	else{
//		function_type_checker(cRcommand);
//	}

//}

//function devider
int check_class::function_type_checker(char cCommand){
	//static function
	if(cCommand >= 'e' && cCommand <= 'k'){
		function_activator_static(cCommand);
	}

	//volitail function
	else 
		if(cCommand >= 'a' && cCommand <= 'd'){
			int check = function_activator_volitail(cCommand);
			if(check == -1){
				return -1;
			}
			else{
				return 0;
			}
		}

	//error
	else{
		return -1;
	}
	return(0);
}
//static function selector
int check_class::function_activator_static(char cCommand){
	if(Cleaningprogram != NULL)
		Cleaningprogram = NULL;

	switch(cCommand){
	case 'e':	//AutoClean
//		Autotmp* a;
		Cleaningprogram = new AutoClean(inter);
		roomref.LoadCleaningProgram(Cleaningprogram);
		Cleaningprogram = NULL;
		cout<<"AutoClean ON"<<endl;
		break;
	case 'f':	//CellClean
//		Cleaningprogram = new Cell(inter);
//		roomref.LoadCleaningProgram(Cleaningprogram);
//		Cleaningprogram = NULL;
		cout<<"CellClean ON"<<endl;
		break;
	case 'g':	//Walltrace
		Cleaningprogram = new Walltrace(inter);
		roomref.LoadCleaningProgram(Cleaningprogram);
		Cleaningprogram = NULL;
		cout<<"Walltrace ON"<<endl;
		break;
	case 'h':	//Spotclean
		Cleaningprogram = new Spotclean(inter);
		roomref.LoadCleaningProgram(Cleaningprogram);
		Cleaningprogram = NULL;
		cout<<"Spotclean ON"<<endl;
		break;
	case 'i':	//manclean
		//Manclean* manclean_object = new Manclean();
		//roomref.stelcleaningin(manclean_object);
		cout<<"ManClean ON"<<endl;
		break;
	case 'j':	//Stop Clean
		//roomref.stop();
		cout<<"Stopped all Clean programs"<<endl;
		break;
	case 'k':	//Dock
		//roomref.dock();
		cout<<"Dock Roomba"<<endl;
		break;
	default :
		return -1;	
		break;
	}
	return(0);
}

int check_class::function_activator_volitail(char cCommand){
	//cout<<"volitail func"<<endl;
	switch(cCommand){
	case 'a':
		//execute function here
		//inter.rijd(1); //ga rechtdoor
		inter.drives(roomba::speed::CRUISE);
		cout<<"case 1"<<endl;
		break;
	case 'b':
		//execute function here
		//inter.rijd(1); //ga achteruit
		inter.drives(roomba::speed::BACKWARDS);
		cout<<"case 2"<<endl;
		break;
	case 'c':
		//execute function here
		//inter.rijd(1); //ga rechts
		cout<<"case 3"<<endl;
		break;
	case 'd':
		//execute function here
		//inter.rijd(1); //ga links
		cout<<"case 4"<<endl;
		break;
	default :
		return -1;
		break;
	}
	return(0);
}



