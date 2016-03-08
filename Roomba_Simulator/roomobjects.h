#ifndef ROOMOBJECTS_H
#define ROOMOBJECTS_H

#include <vector>
#include <string>

#include "timerclass.h"

using namespace std;

class roomclass;
class sensorclass;
class roomobjectclass;
class stairclass;
class wallclass;
class roombaclass;



class sensorclass{
private:

    // wheel drop sensors
    bool bWheelDropLeft;
    bool bWheelDropRight;
    bool bBumpLeft;
    bool bBumpRight;

    // wall sensor
    int iWallSignal;                // 0 - 1023

    // cliff sensor
    int iCliffLeftSignal;           // 0 - 4095
    int iCliffFrontLeftSignal;      // 0 - 4095
    int iCliffFrontSignal;          // 0 - 4095
    int iCliffFrontRightSignal;     // 0 - 4095
    int iCliffRightSignal;          // 0 - 4095

    // light bump sensors
    int iLightBumpLeft;             // 0 - 4095
    int iLightBumpFrontLeft;        // 0 - 4095
    int iLightBumpCenter;           // 0 - 4095
    int iLightBumpFrontRight;       // 0 - 4095
    int iLightBumpRight;            // 0 - 4095

    // cliff sensor
    bool bCliffLeft;
    bool bCliffFrontLeft;
    bool bCliffFrontRight;
    bool bCliffRight;

    // wall sensor
    bool bWallBump;

    roomobjectclass * roomba;
    roomclass * room;
public:
    sensorclass(roomobjectclass* roomba,roomclass * room);
};


class roomclass{
private:
    vector<roomobjectclass *> roomobjects;
public:
    roomclass();
    ~roomclass();

    roomobjectclass * roomba;
    sensorclass * sensors;
};
class roomobjectclass{
public:
    roomobjectclass();
private:
protected:
    signed int iPosHor;
    signed int iPosVer;
    signed int iVerSize;
    signed int iHorSize;

    roomobjectclass(signed int iPosHor,signed int iPosVer);
};
class stairclass : public roomobjectclass{
public:
    stairclass();
    stairclass(signed int iPosHor, signed int iPosVer);
};
class wallclass : public roomobjectclass{
public:
    wallclass();
    wallclass(signed int iPosHor, signed int iPosVer);
};
class roombaclass : public roomobjectclass{
private:
    float fDirectionAngle;
    float fSpeed;
public:
    roombaclass();
    void drive();
};

#endif // ROOMOBJECTS_H
