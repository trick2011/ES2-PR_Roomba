#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <linux/stat.h>
#include "macros.h"
#include "com_class.h"
#include "check_class.h"
#include "roombacontroller.h"
#include "interpreter.h"

using namespace std;

//main for testing purpeses, in combination with pipe_writer.c
int main()
{
	check_class check_object;
	check_object.makeFIFO();

	while(1){
		check_object.pipe_checker();
		cout<<"test ";
		sleep(1);}
	
return 0;
}


//constructor
	check_class::check_clas(roombacontroller& roomref,interpreter& inter):inter{inter},roomref{roomref};

//pipe checker
	void check_class::pipe_checker(){
	char cRcommand;
	check_class pipe_object;
	cRcommand = pipe_object.readFIFO();
	pipe_object.function_type_checker(cRcommand);
	
	if(cRcommand == 'o'){cout<<"pipe empty"<<endl;}
	else{pipe_object.function_type_checker(cRcommand);}

	}

//function devider
	int check_class::function_type_checker(char cCommand){
	check_class functiondevider_object;	
	
	//static function
	if(cCommand >= 'e' && cCommand <= 'k')
		{functiondevider_object.function_activator_static(cCommand);}

	//volitail function
	else if(cCommand >= 'a' && cCommand <= 'd')
	{
		int check = functiondevider_object.function_activator_volitail(cCommand);
		if(check == -1)
			{return -1;}
		else
			{return 0;}
	}

	//error
	else
	{
		return -1;
	}	
	}
//static function selector
	int check_class::function_activator_static(char cCommand){
	switch(cCommand){
		case 'e':	//AutoClean
			Autoclean* autoclean_object = new Autoclean();
    			roomref.stelcleaningin(autoclean_object); 
			cout<<"AutoClean ON"<<endl;
			break;
		case 'f':	//CellClean
			Cellclean* cellclean_object = new Cellclean();
    			roomref.stelcleaningin(cellclean_object); 
			cout<<"CellClean ON"<<endl;
			break;
		case 'g':	//Walltrace
			Walltrace* walltrace_object = new Walltrace();
    			roomref.stelcleaningin(walltrace_object);
			cout<<"Walltrace ON"<<endl;
			break;
		case 'h':	//Spotclean
			Spotclean* spotcleanobj = new Spotclean();
    			roomref.stelcleaningin(spotcleanobj);
			cout<<"Spotclean ON"<<endl;
			break;
		case 'i':	//manclean
			Manclean* manclean_object = new Manclean();
    			roomref.stelcleaningin(manclean_object);
			cout<<"ManClean ON"<<endl;
			break;
		case 'j':	//Stop Clean
			roomref.stop();
			cout<<"Stopped all Clean programs"<<endl;
			break;
		case 'k':	//Dock
			roomref.dock();
			cout<<"Dock Roomba"<<endl;
			break;
		default :
			return -1;
			break;}
	}

	int check_class::function_activator_volitail(char cCommand){
	//cout<<"volitail func"<<endl;
	switch(cCommand){
		case 'a':
			//execute function here
			//inter.rijd(1); //ga rechtdoor
			cout<<"case 1"<<endl;
			break;
		case 'b':
			//execute function here
			//inter.rijd(1); //ga achteruit
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
			break;}
	}



