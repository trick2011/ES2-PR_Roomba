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

#include "../roombacontroller.h"
#include "../../Roomba_Interpreter/interpreter.h"
#include "macros.h"

#include "com_class.h"
#include "pipe_filler.h"

using namespace std;

//#define DRY_DEBUG // define DRY_DEBUG when not debugging with the roomba
#define VERBOSE

class check_class : public com_class{
private:
//	bool Auto_clean_Flag;
//	bool Man_clean_Flag;
//	bool Dock_roomba_Flag;
	


	Basicclean* Cleaningprogramc;
	interpreter& inter;
	Roombacontroller& roomref;
public:
	//check_class();
	check_class(Roombacontroller& roomref,interpreter& inter);


	void operator()();

	void pipe_checker();
	void easter(void);
	
};
#endif
