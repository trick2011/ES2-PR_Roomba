#ifndef PIPE_FILLER_H
#define PIPE_FILLER_H

#include <fstream>

#ifdef __linux
#include <sys/signal.h>
#endif

#include "../../Roomba_Interpreter/interpreter.h"
#include "../Cleaningprograms/basicclean.h"
#include "com_class.h"


class pipe_filler
{
private:
	interpreter& peter;
	com_class& comclass;
public:
	pipe_filler(interpreter& peter,com_class& comclass);
	void operator()();
};

#endif // PIPE_FILLER_H
