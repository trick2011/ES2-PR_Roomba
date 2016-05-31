#ifndef WALLTRACE_H
#define WALLTRACE_H
#include "basicclean.h"

class Walltrace : public Basicclean
{
public:
	Walltrace(interpreter& interpreterreference):Basicclean(interpreterreference){}
    ~Walltrace();
    void clean(void);
};

#endif // WALLTRACE_H
