#include "check_class.h"
//constructor
#define VERBOSE

server* check_class::print_serverptr = NULL;

Basicclean* check_class::Cleaningprogramc = NULL;
interpreter* check_class::inter = NULL;
Roombacontroller* check_class::roomref = NULL;

check_class::check_class(Roombacontroller* roomref,interpreter* inter,int port){
	check_class::inter = inter;
	check_class::roomref = roomref;
#ifdef DRY_DEBUG
	cout << "DRY DEBUG, just so you know" <<endl;
#endif
	check_class::print_serverptr = &print_server;
	print_server.set_message_handler(&check_class::on_message);

	try{
		//print_server.set_access_channels(websocketpp::log::alevel::all);
        print_server.clear_access_channels(websocketpp::log::alevel::all);//websocketpp::log::alevel::frame_payload);
		print_server.init_asio();
		print_server.listen(port);
		print_server.start_accept();
	}
	catch(websocketpp::exception){
		cerr << "failed to open the websocket" << endl;
		
//		check_class::print_serverptr->stop_listening();
		//print_serverstop_listening()
		//print_server.stop_listening();
	};
}

void check_class::on_message(websocketpp::connection_hdl hdl, server::message_ptr msg) {
#ifdef DRY_DEBUG
//	print_server.send(" ");
	switch((int)msg->get_payload()[0]){
		case site_opcodes::MoveForward: // boven
			cout << "Forward" << endl;
			break;
		case site_opcodes::MoveRight: // rechts
			cout << "MoveRight" << endl;
			break;
		case site_opcodes::MoveLeft: // links
			cout << "MoveLeft" << endl;
			break;
		case site_opcodes::MoveBackword: // onder
			cout << "MoveBackword" << endl;
			break;
		
		case site_opcodes::AutoClean:	//AutoClean
			cout<<"AutoClean ON"<<endl;
			break;
		case site_opcodes::SpotClean:	//Spotclean
			cout<<"Spotclean ON"<<endl;
			break;
		case site_opcodes::WallTrace:	//Walltrace

			cout<<"Walltrace ON"<<endl;
			break;
		case site_opcodes::Dock:	//Dock
			cout<<"Dock Roomba"<<endl;
			break;
		case site_opcodes::StopRoomba:	//Stop Roomba Cleaning
			cout<<"Stopped all Clean programs"<<endl;
			break;
		
		case site_opcodes::Start: // hard start controller
			cout << "Roomba Hard Start" << endl;
			break;
		case site_opcodes::Stop: // hard stop roomba
			cout << "Roomba Hard Stop" << endl;
			break;
		
		case site_opcodes::StopController: // stop controller
			cout << "QUIT" << endl;
			break;
		case site_opcodes::easter: // easter egg
			easter();
			break;
		
		default :
			break;
	}
#endif
//#ifndef DRY_DEBUG
	switch((int)msg->get_payload()[0]){
		case site_opcodes::MoveForward: // boven
			#ifdef VERBOSE
			cout << "Forward" << endl;
			#endif
			Basicclean::DisableCleaning(); // this is a static function so there is in this instance no object needed
			while(Basicclean::getProcessPID() != 0){}// test if really stopped runnning
			check_class::inter->drives(roomba::speed::CRUISE);
			
			break;
		case site_opcodes::MoveRight: // rechts
			#ifdef VERBOSE
			cout << "MoveRight" << endl;
			#endif
			Basicclean::DisableCleaning(); // this is a static function so there is in this instance no object needed
			while(Basicclean::getProcessPID() != 0){}// test if really stopped runnning
			check_class::inter->drives(roomba::speed::STOP);
			check_class::inter->turnRight();
			break;
		case site_opcodes::MoveLeft: // links
			#ifdef VERBOSE
			cout << "MoveLeft" << endl;
			#endif
			Basicclean::DisableCleaning(); // this is a static function so there is in this instance no object needed
			while(Basicclean::getProcessPID() != 0){}// test if really stopped runnning
			check_class::inter->drives(roomba::speed::STOP);
			check_class::inter->turnLeft();
			break;
		case site_opcodes::MoveBackword: // onder
			#ifdef VERBOSE
			cout << "MoveBackword" << endl;
			#endif
			Basicclean::DisableCleaning(); // this is a static function so there is in this instance no object needed
			while(Basicclean::getProcessPID() != 0){}// test if really stopped runnning
			check_class::inter->drives(roomba::speed::BACKWARDS);
			break;
		
		case site_opcodes::AutoClean:	//AutoClean
			Basicclean::DisableCleaning();
			check_class::Cleaningprogramc = new AutoClean(*check_class::inter);
			check_class::roomref->SetCleaningProgram(check_class::Cleaningprogramc);
			check_class::Cleaningprogramc = NULL;
			#ifdef VERBOSE
			cout<<"AutoClean ON"<<endl;
			#endif
			
			break;
		case site_opcodes::SpotClean:	//Spotclean
			#ifdef VERBOSE
			cout<<"Spotclean ON"<<endl;
			#endif
			check_class::Cleaningprogramc = new Spotclean(*check_class::inter);
			check_class::roomref->SetCleaningProgram(check_class::Cleaningprogramc);
			check_class::Cleaningprogramc = NULL;
			break;
		case site_opcodes::WallTrace:	//Walltrace
			#ifdef VERBOSE
			cout<<"Walltrace ON"<<endl;
			#endif
			check_class::Cleaningprogramc = new Walltrace(*check_class::inter);
			check_class::roomref->SetCleaningProgram(check_class::Cleaningprogramc);
			check_class::Cleaningprogramc = NULL;
			break;
		case site_opcodes::Dock:	//Dock
			#ifdef VERBOSE
			cout<<"Dock Roomba"<<endl;
			#endif
			
			break;
		case site_opcodes::StopRoomba:	//Stop Roomba Cleaning
			#ifdef VERBOSE
			cout<<"Stopped all Clean programs"<<endl;
			#endif
			check_class::roomref->DisableCleaning();
			check_class::inter->drives(roomba::speed::STOP);
			break;
		
		case site_opcodes::Start: // hard start controller
			#ifdef VERBOSE
			cout << "Roomba Hard Start" << endl;
			#endif
			check_class::inter->startRoomba();
			break;
		case site_opcodes::Stop: // hard stop roomba
			#ifdef VERBOSE
			cout << "Roomba Hard Stop" << endl;
			#endif
			Basicclean::DisableCleaning();
			check_class::inter->brushes(roomba::brush::NOBRUSH);
			check_class::inter->stopRoomba();
			break;
			
		case site_opcodes::StopController: // stop controller
			#ifdef VERBOSE
			cout << "QUIT" << endl;
			#endif
			check_class::roomref->DisableCleaning();
			check_class::inter->drives(roomba::speed::STOP);
			check_class::inter->brushes(roomba::brush::NOBRUSH);
			check_class::inter->stopRoomba();
			
			check_class::print_serverptr->stop_listening();
			break;
		case site_opcodes::easter: // easter egg
			easter();
			break;
		
		default :
			break;
	}
//#endif
}

void check_class::operator ()(){
	//pipe_checker();
	try{
		print_server.run();
	}
		catch(websocketpp::exception){
			cout << "error" << endl;
	};
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

/*
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
*/