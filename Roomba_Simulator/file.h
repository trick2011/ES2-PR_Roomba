#ifndef FILE_H
#define FILE_H

#include <string>
#include <iostream>
#include <fstream>

#include <vector>
#include <cmath>

#include <chrono> /**< timer **/
#include <thread> /**< timer **/

using namespace std;
/**  This class is the master class in which all other
 *   classes will be created.
 * */
class roomclass;
/**  This class is a masterclass for all objects to be
 *   created inside roomclass.
 *   It contains general attributes for relative position.
 */
class roomobjectclass;
/**  This class implementens all the roomba sensors and
 *   contains the functions to trigger the sensors.
 */
class sensorclass;
/**  This class will be responsible for triggering
 *   roomba->drive() at a specified amount
 */
class timerclass;

/**  This class is a subclass of roomobjectclass and
 *   implements the roomba.
 */
class roombaclass;
/** This class is a sublcass of roomobject class and
 *  implements natural objects which appear inside a room.
 */
class wallclass;
class dropclass;


class roomclass{
public:
    vector<roomobjectclass> roomobjects;
    roombaclass * roomba;
    sensorclass * sensors;

    roomclass();
    ~roomclass();
};
class sensorclass{
private:
    vector<string> vsErrorVector;

    const float fFloatRange = 0.10;
    roomclass& room;

    // wheel drop sensors           // not implemented
    bool bWheelDropLeft;            // will not be implemented
    bool bWheelDropRight;           // will not be implemented

    // physical bump sensors        // implemented
    bool bBumpLeft;
    bool bBumpRight;

    // wall sensor                  // not implemented
    int iWallSignal;                // 0 - 1023

    // cliff sensor                 // not implemented
    int iCliffLeftSignal;           // 0 - 4095
    int iCliffFrontLeftSignal;      // 0 - 4095
    int iCliffFrontSignal;          // 0 - 4095
    int iCliffFrontRightSignal;     // 0 - 4095
    int iCliffRightSignal;          // 0 - 4095

    // light bump sensors           // not implemented
    int iLightBumpLeft;             // 0 - 4095
    int iLightBumpFrontLeft;        // 0 - 4095
    int iLightBumpCenter;           // 0 - 4095
    int iLightBumpFrontRight;       // 0 - 4095
    int iLightBumpRight;            // 0 - 4095

    // cliff sensor                 // implemented
    bool bCliffLeft;
    bool bCliffFrontLeft;
    bool bCliffFrontRight;
    bool bCliffRight;

    // wall sensor                  // not implemented
    bool bWallBump;

    bool checkbumpL(int iHorPos,int iVerPos);
    bool checkbumpR(int iHorPos,int iVerPos);
    bool checkbumpU(int iHorPos,int iVerPos);
    bool checkbumpD(int iHorPos,int iVerPos);
    bool checkbumpUL(int iHorPos,int iVerPos);
    bool checkbumpUR(int iHorPos,int iVerPos);
    bool checkbumpDL(int iHorPos,int iVerPos);
    bool checkbumpDR(int iHorPos,int iVerPos);
    float calcmultiplication(float iDiffHor, float iDiffVer);

    void resetphysicalsensors(void); // resets bBump(L/R) and bCLiff(L/LF/FR/R)
    void setbumpcomplex(bool bDoubleBump,bool bLeftBump,bool bRightBump,int iPositionOne,int iPositionTwo,int iPositionThree);

    bool floatcomp(float fIn1,float fIn2);
public:
    sensorclass(roomclass& room);
    ~sensorclass();
    bool checkbump(float iHorMov,float iVerMov);

    bool getbBumpLeft(void){return(bBumpLeft);}
    bool getbBumpRight(void){return(bBumpRight);}

    bool getCliffLeft(void){return(bCliffLeft);}
    bool getCliffFrontLeft(void){return(bCliffFrontLeft);}
    bool getCliffFrontRight(void){return(bCliffFrontRight);}
    bool getCliffRight(void){return(bCliffRight);}
};
class timerclass{
private:
    roombaclass& roomba;
    chrono::time_point<chrono::system_clock> start,end;
    bool bRunning;
    double dTimerDuration;
    void timer(/*roombaclass& roomba*/);
public:
    //timerclass(roombaclass &roomba) : timerclass(roomba,0.5){;}
    timerclass(roombaclass& roomba,double dTimerDuration);


    void operator()(){timer();}

    void setTimerDuration(double dInput) {dTimerDuration = dInput;}
    double readTimerDuration(void) {return(dTimerDuration);}
    void setTimerEnable(bool bInput) {bRunning = bInput;}
    double readTimerEnable(void) {return(bRunning);}
};

class roomobjectclass{
public:
    enum roomobjecttypes{roomba=1,wall=2,standard=2,drop,stairs};
protected:
    const float pi = 3.14159265;
    roomobjecttypes roomobjecttype;
public:
    roomobjectclass(signed int iPosHor, signed int iPosVer, roomobjecttypes roomobjecttypeIn);
    roomobjectclass(signed int iPosHor, signed int iPosVer, unsigned int iSizeHor, unsigned int iSizeVer, roomobjecttypes roomobjecttypeIn);

    signed int iPosHor;
    signed int iPosVer;
    float fPosVer;
    float fPosHor;

    unsigned int iSizeHor;
    unsigned int iSizeVer;

    roomobjecttypes getroomobjecttype(void){return(roomobjecttype);}
    //virtual ~roomobjectclass();
    //virtual void drive(void);
};
class roombaclass : public roomobjectclass{
private:
    float fAngle;
    float fSpeed;
    sensorclass& sensors;


public:
    roombaclass(sensorclass& sensors); // <-- die werkte ineens niet
    ~roombaclass();

    void move(float fHorMov,float fVerMov);
    void setangle(float fInputAngle);
    void setspeed(float fInputSpeed);
    float getangle(void) {return(fAngle);}
    float getspeed(void) {return(fSpeed);}

    void drive(void);
};
//class wallclass : public roomobjectclass{
//private:
//    string sObjectName;
//public:
//    wallclass(signed int iPosHor, signed int iPosVer, unsigned int iSizeHor, unsigned int iSizeVer):roomobjectclass(iPosHor,iPosVer,iSizeHor,iSizeVer,wall){roomobjecttype = wall;}
//    string readobjectname(void);
//    void writeobjectname(string sInput);
//};
//class dropclass : public roomobjectclass{
//    dropclass(signed int iPosHor, signed int iPosVer, unsigned int iSizeHor, unsigned int iSizeVer):roomobjectclass(iPosHor,iPosVer,iSizeHor,iSizeVer,drop){roomobjecttype = drop;}
//};

#endif // FILE

