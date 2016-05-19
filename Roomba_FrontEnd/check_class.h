#ifndef check_class_h
#define check_class_h

//#include <iostream>
//#include <string>
//#include <sys/stat.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <string.h>
//#include <linux/stat.h>
//#include "macros.h"

#include "../Roomba_Controller/roombacontroller.h"
#include "../Interpreter_NoThread/interpreter.h"

#include "com_class.h"

using namespace std;

class check_class : public com_class{
private:
	bool Auto_clean_Flag;
	bool Man_clean_Flag;
	bool Dock_roomba_Flag;
	
	Basicclean* Cleaningprogram;
	interpreter& inter;
	Roombacontroller& roomref;
public:
	//check_class();
	check_class(Roombacontroller& roomref,interpreter& inter);

	void pipe_checker();
	int function_type_checker(char cCommand);
	int function_activator_static(char cCommand);
	int function_activator_volitail(char cCommand);
	
	
};
#endif
