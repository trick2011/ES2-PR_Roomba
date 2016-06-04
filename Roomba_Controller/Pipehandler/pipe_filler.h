#ifndef PIPE_FILLER_H
#define PIPE_FILLER_H

#include "../../Roomba_Interpreter/interpreter.h"
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
