#ifndef DOCK_H
#define DOCK_H
#include "basicclean.h"

class Dock : public Basicclean
{
public:
	Dock(interpreter& interpreterreference):Basicclean(interpreterreference){}
    ~Dock();
	void clean(void){}
};

#endif // DOCK_H