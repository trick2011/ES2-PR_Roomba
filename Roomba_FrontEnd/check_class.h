#ifndef check_class_h
#define check_class_h 

#include "com_class.h"

class check_class : public Communicate{
private:
	bool Auto_clean_Flag;
	bool Man_clean_Flag;
	bool Dock_roomba_Flag;
public:
	void pipe_checker();
	int function_type_checker(char cCommand);
	int function_activator_static(char cCommand);
	int function_activator_volitail(char cCommand);
};
#endif
