#include "check_class.h"
//constructor
#define VERBOSE

check_class::check_class(Roombacontroller& roomref,interpreter& inter):com_class(),inter{inter},roomref{roomref}{
#ifdef DRY_DEBUG
	cout << "DRY DEBUG, just so you know" <<endl;
#endif
}

void check_class::operator ()(){
	pipe_checker();
}
void check_class::easter(void){
	cout << "             \\ "<< endl <<
	"              \\ "<< endl <<
	"               \\\\ "<< endl <<
	"                \\\\ "<< endl <<
	"                 >\\/7"<< endl <<
	"             _.-(6'  \\ "<< endl <<
	"            (=___._/` \\ "<< endl <<
	"                 )  \\ |"<< endl <<
	"                /   / |"<< endl <<
	"               /    > /"<< endl <<
	"              j    < _\\ "<< endl <<
	"          _.-' :      ``."<< endl <<
	"          \\ r=._\\        `."<< endl <<
	"         <`\\\\_  \\         .`-."<< endl <<
	"          \\ r-7  `-. ._  ' .  `\\ "<< endl <<
	"           \\`,      `-.`7  7)   )"<< endl <<
	"            \\/         \\|  \\ '  / `-._"<< endl <<
	"                       ||    .'"<< endl <<
	"                        \\ \\  ("<< endl <<
	"                         >\\  >"<< endl <<
	"                      ,.-' >.'"<< endl <<
	"                    <.'_.''" << endl <<
	"                      <'" << endl;
}

#ifndef DRY_DEBUG // actual implementation
void check_class::pipe_checker(){
	char PipeCommand = 0x00;
	bool PipeCheckerEnabled = true;
	while(PipeCheckerEnabled){
		PipeCommand = 0;
		PipeCommand = readFIFO();

		if(PipeCommand == pipeempty)
			continue;

		switch(PipeCommand){
		case site_opcodes::MoveForward: // boven
			Basicclean::DisableCleaning(); // this is a static function so there is in this instance no object needed
			while(Basicclean::getProcessPID() != 0){}// test if really stopped runnning
			inter.drives(roomba::speed::CRUISE);
			break;
		case site_opcodes::MoveRight: // rechts
			Basicclean::DisableCleaning(); // this is a static function so there is in this instance no object needed
			while(Basicclean::getProcessPID() != 0){}// test if really stopped runnning
			inter.drives(roomba::speed::STOP);
			inter.turnRight();

			break;
		case site_opcodes::MoveLeft: // links
			Basicclean::DisableCleaning(); // this is a static function so there is in this instance no object needed
			while(Basicclean::getProcessPID() != 0){}// test if really stopped runnning
			inter.drives(roomba::speed::STOP);
			inter.turnLeft();

			break;
		case site_opcodes::MoveBackword: // onder
			Basicclean::DisableCleaning(); // this is a static function so there is in this instance no object needed
			while(Basicclean::getProcessPID() != 0){}// test if really stopped runnning
			inter.drives(roomba::speed::BACKWARDS);
			break;
		case site_opcodes::AutClean:	//AutoClean
			Basicclean::DisableCleaning();
			Cleaningprogramc = new AutoClean(inter);
			roomref.SetCleaningProgram(Cleaningprogramc);
			Cleaningprogramc = NULL;
#ifdef VERBOSE
			cout<<"AutoClean ON"<<endl;
#endif
			break;
		case site_opcodes::WallTrace:	//Walltrace
			Cleaningprogramc = new Walltrace(inter);
			roomref.SetCleaningProgram(Cleaningprogramc);
			Cleaningprogramc = NULL;
#ifdef VERBOSE
			cout<<"Walltrace ON"<<endl;
#endif
			break;
		case site_opcodes::SpotClean:	//Spotclean
			Cleaningprogramc = new Spotclean(inter);
			roomref.SetCleaningProgram(Cleaningprogramc);
			Cleaningprogramc = NULL;
#ifdef VERBOSE
			cout<<"Spotclean ON"<<endl;
#endif
			break;
		case site_opcodes::StopRoomba:	//Stop Clean
			//roomref.stop();
			roomref.DisableCleaning();
#ifdef VERBOSE
			cout<<"Stopped all Clean programs"<<endl;
#endif
			inter.drives(roomba::speed::STOP);
			break;
		case site_opcodes::Dock:	//Dock
#ifdef VERBOSE
			cout<<"Dock Roomba"<<endl;
#endif
			break;
		case site_opcodes::Start:
			inter.startRoomba();
			break;
		case site_opcodes::Stop:
			Basicclean::DisableCleaning();
			inter.stopRoomba();
			break;
		case site_opcodes::StopController:
			PipeCheckerEnabled = false;
			break;
		case site_opcodes::easter:
			easter();
			break;
		default :
			break;
		}
		//sleep(1);
	}
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
}

#endif
