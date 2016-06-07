#ifndef WALLTRACE_H
#define WALLTRACE_H
#include "basicclean.h"

class Walltrace : public Basicclean
{
public:
	Walltrace(interpreter& interpreterreference):Basicclean(interpreterreference){}
    ~Walltrace();
    void clean(void);
private:
    int iState = 0;
};

#endif // WALLTRACE_H
