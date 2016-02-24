#ifndef HIGHLEVELSIMCLASS_H
#define HIGHLEVELSIMCLASS_H


//#include <vector>
//#include <iostream>
//#include <iomanip>

using namespace std;

class highlevelsimclass{
private:
    naviclass *pSimulator;
    
public:
    highlevelsimclass();
    highlevelsimclass(naviclass *pointer);
    ~highlevelsimclass();
    
    void doo(void);
};

#endif