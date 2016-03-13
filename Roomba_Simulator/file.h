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

public:
    vector<roomobjectclass> roomobjects;
    roombaclass * roomba;
    sensorclass * sensors;

    roomclass();
    ~roomclass();
};
class sensorclass{
private:
    roomclass& room;

    bool bBumpLeft;
    bool bBumpRight;

    bool checkbumpL(int iHorPos,int iVerPos);
    bool checkbumpR(int iHorPos,int iVerPos);
    bool checkbumpU(int iHorPos,int iVerPos);
    bool checkbumpD(int iHorPos,int iVerPos);
    bool checkbumpUL(int iHorPos,int iVerPos);
    bool checkbumpUR(int iHorPos,int iVerPos);
    bool checkbumpDL(int iHorPos,int iVerPos);
    bool checkbumpDR(int iHorPos,int iVerPos);
    float calcmultiplication(float iDiffHor, float iDiffVer);
public:
    sensorclass(roomclass& room);
    bool checkbump(int iHorMov, int iVerMov);

    bool getbBumpLeft(void)  {return(bBumpLeft);}
    bool getbBumpRight(void) {return(bBumpRight);}
};

class roomobjectclass{
protected:

public:
    roomobjectclass(signed int iPosHor, signed int iPosVer);
    roomobjectclass(signed int iPosHor, signed int iPosVer, unsigned int iSizeHor, unsigned int iSizeVer);


    signed int iPosHor;
    signed int iPosVer;
    unsigned int iSizeHor;
    unsigned int iSizeVer;

    //virtual ~roomobjectclass();
    //virtual void drive(void);
};
class roombaclass : public roomobjectclass{
private:
    float fAngle;
    float fSpeed;
    sensorclass& sensors;
public:
    roombaclass(sensorclass* sensors); // <-- die werkte ineens niet
    ~roombaclass();

    void setangle(float fInputAngle);
    void setspeed(float fInputSpeed);
    float getangle(void) {return(fAngle);}
    float getspeed(void) {return(fSpeed);}

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

