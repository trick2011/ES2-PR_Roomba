#ifndef WALLTRACE_H
#define WALLTRACE_H

#include "basicclean.h"

/** lonneke implementeer deze klasse maar **/
/** wat ik hier heb gedaan is ik heb een klasse genaamt cleaning program aangemaakt waaruit ik wallclean afleidt **/
/** wall clean heeft via een overerfde sensors reference toegang tot de sensoren die de roomba heeft en kan daarmee aktie's bepalen **/


class Walltrace : public Basicclean
{
public:
	Walltrace(interpreter& interpreterreference):Basicclean(interpreterreference){}
    ~Walltrace();
	void clean(void){}
};

#endif // WALLTRACE_H
