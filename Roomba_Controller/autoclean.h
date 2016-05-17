#ifndef AUTOCLEAN_H
#define AUTOCLEAN_H
#include "basicclean.h"

class Autoclean : public Basicclean
{
public:
    Autoclean(interpreter& interpreterreference):Basicclean(interpreterreference){};
    ~Autoclean();

    void clean(void);
};

#endif // AUTOCLEAN_H


