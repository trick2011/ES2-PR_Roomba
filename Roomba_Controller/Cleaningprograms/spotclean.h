#ifndef SPOTCLEAN_H
#define SPOTCLEAN_H

#include "basicclean.h"

class Spotclean : public Basicclean
{
public:

    Spotclean(interpreter& interpreterreference);
    ~Spotclean();

	void clean(void);
};


#endif // SPOTCLEAN_H
