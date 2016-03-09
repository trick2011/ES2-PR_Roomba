#ifndef FILE_H
#define FILE_H

#include <string>
#include <iostream>

#include <vector>
#include <cmath>

using namespace std;

class roomclass;
class roomobjectclass;
class sensorclass;

class roombaclass;
class wallclass;

class roomclass{
private:
    roomobjectclass * roomba;
    sensorclass * sensors;
public:
    vector<roomobjectclass> roomobjects;
    roomclass();
    ~roomclass();
};
class sensorclass{
private:
    roomclass& room;
public:
    sensorclass(roomclass& room);
    bool checkbump(void);
};

class roomobjectclass{
protected:
    signed int iPosHor;
    signed int iPosVer;
    unsigned int iSizeHor;
    unsigned int iSizeVer;
public:
    roomobjectclass(signed int iPosHor,signed int iPosVer);

    int testvariable;
};
class roombaclass : public roomobjectclass{
private:
    float fAngle;
    float fSpeed;
    sensorclass& sensors;
public:
    roombaclass(sensorclass* sensors); // <-- die werkte ineens niet
    ~roombaclass();

    void drive(void);
};
class wallclass : public roomobjectclass{
private:
    string sObjectName;
public:
    string readobjectname(void);
    void writeobjectname(string sInput);
};

#endif // FILE

