#ifndef CELL_H
#define CELL_H
#include "basicclean.h"

class Cell : public Basicclean
{
public:
	Cell(interpreter& interpreterreference):Basicclean(interpreterreference){}
    ~Cell();
	void clean(void){}
};

#endif // CELL_H
