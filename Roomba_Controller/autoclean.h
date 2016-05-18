#ifdef AUTOCLEAN_H
#define AUTOCLEAN_H

#include "basicclean.h"

class Autoclean : public Basicclean
{
public:
    Autoclean(interpreter& interpreterreference):Basicclean(interpreterreference){}
    ~Autoclean() = 0;
    Autoclean();
    void clean(void);
private:

};

#endif // AUTOCLEAN_H


