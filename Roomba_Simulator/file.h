#ifndef FILE
#define FILE

#include <vector>
#include <cmath>

using namespace std;

class roomclass;
class roomobjectclass;
class roombaclass;
class sensorclass;

class roomclass{
private:
    roomobjectclass * roomba;
    sensorclass * sensors;
    vector<roomobjectclass> roomobjects;
public:
    roomclass();
    ~roomclass();
};
class sensorclass{
private:
    roomclass& room;
public:
    sensorclass(roomclass& room);
    void checkbump(void);
};

class roomobjectclass{
protected:
    signed int iPosHor;
    signed int iPosVer;
    unsigned int iSizeHor;
    unsigned int iSizeVer;
public:
    roomobjectclass(signed int iPosHor,signed int iPosVer);
};
class roombaclass : public roomobjectclass{
private:
    float fAngle;
    float fSpeed;
public:
    roombaclass(); // <-- die werkte ineens niet
    ~roombaclass();

    void drive(void);
};


#endif // FILE

