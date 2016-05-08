#ifndef FILE_H
#define FILE_H

//#define TIMER_DEBUG

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <cmath>

#include <chrono> /**< timer **/
#include <thread> /**< timer **/

using namespace std;
/**  This class is the master class in which all other
 *   classes will be created.
 * */
class Roomclass;
/**  This class is a masterclass for all objects to be
 *   created inside roomclass.
 *   It contains general attributes for relative position.
 */
class Roomobjectclass;
/** This class implements all the roomba sensors
 *
 */
class Sensors;
/**  This class implementens all the roomba sensors and
 *   contains the functions to trigger the sensors.
 */
class Sensorclass;
/**  This class will be responsible for triggering
 *   roomba->drive() at a specified amount
 */
class Timerclass;

/**  This class is a subclass of roomobjectclass and
 *   implements the roomba.
 */
class Roombaclass;
/** This class is a sublcass of roomobject class and
 *  implements natural objects which appear inside a room.
 */
class Wallclass;
class Dropclass;


class Roomclass{
public:
	vector<Roomobjectclass> roomobjects;
	Roombaclass * roomba;
	Sensorclass * sensors;

	Roomclass();
	~Roomclass();
};
class Sensors{
protected:
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

    // light bump sensors           // implementing
    int iLightBumpLeft;             // 0 - 4095
    int& iLightBumpFrontLeft;       // 0 - 4095 this is made a reference to iLightBumpLeft because in implementing the lightbump left and front left have been taken toghether
    int iLightBumpCenter;           // 0 - 4095
    int& iLightBumpFrontRight;      // 0 - 4095 this is made a reference to iLightBumpRight because in implementing the lightbump right and front right have been taken toghether
    int iLightBumpRight;            // 0 - 4095

    // cliff sensor                 // implemented
    bool bCliffLeft;
    bool bCliffFrontLeft;
    bool bCliffFrontRight;
    bool bCliffRight;

    // wall sensor                  // not implemented
    bool bWallBump;
public:
	Sensors();

    bool getbBumpLeft(void){return(bBumpLeft);}
    bool getbBumpRight(void){return(bBumpRight);}

    bool getCliffLeft(void){return(bCliffLeft);}
    bool getCliffFrontLeft(void){return(bCliffFrontLeft);}
    bool getCliffFrontRight(void){return(bCliffFrontRight);}
    bool getCliffRight(void){return(bCliffRight);}

    int getLightBumpLeft(void){return(iLightBumpLeft);}
    int getLightBumpFrontLeft(void){return(iLightBumpFrontLeft);}
    int getLightBumpCenter(void){return(iLightBumpCenter);}
    int getLightBumpFrontRight(void){return(iLightBumpFrontRight);}
    int getLightBumpRight(void){return(iLightBumpRight);}
};

class Sensorclass : public Sensors{
protected:
    bool floatcomp(float fIn1,float fIn2);
    vector<string> vsErrorVector;

    const unsigned int iLightBumpRange = 10;
    const unsigned int iLightBumpValueMax = 4095;

    const float fFloatRange = 0.10;
	Roomclass& room;

    bool checkbumpL(int iHorPos,int iVerPos);
    bool checkbumpR(int iHorPos,int iVerPos);
    bool checkbumpU(int iHorPos,int iVerPos);
    bool checkbumpD(int iHorPos,int iVerPos);
    bool checkbumpUL(int iHorPos,int iVerPos);
    bool checkbumpUR(int iHorPos,int iVerPos);
    bool checkbumpDL(int iHorPos,int iVerPos);
    bool checkbumpDR(int iHorPos,int iVerPos);
    float calcmultiplication(float iDiffHor, float iDiffVer);

    bool checkLightBumpUL(void);
    bool checkLightBumpUR(void);
    bool checkLightBumpU(void);
    void checkLightBump(void);

    void resetlightbump(void);
    void resetphysicalsensors(void); // resets bBump(L/R) and bCLiff(L/LF/FR/R)
    void setbumpcomplex(bool bDoubleBump,bool bLeftBump,bool bRightBump,int iPositionOne,int iPositionTwo,int iPositionThree);

public:
    unsigned int determineLightBumpValue(const unsigned int iHor,const unsigned int iVer);
	Sensorclass(Roomclass& room);
	Sensorclass();/**< this constructor should NEVER be used outside of testing! IT WILL BREAK FUNCTIONS **/
	~Sensorclass();

	friend ostream& operator<<(ostream& output,Sensorclass &sensors){
        output << "   " << sensors.getbBumpLeft() << sensors.getbBumpRight() << sensors.getCliffLeft() << sensors.getCliffFrontLeft() << sensors.getCliffFrontRight() << sensors.getCliffRight();
        output << " " << sensors.getLightBumpLeft() << " " << sensors.getLightBumpFrontLeft() << " " << sensors.getLightBumpCenter() << " " << sensors.getLightBumpFrontRight() << " " << sensors.getLightBumpRight()  << endl;
        return(output);
    }

    bool checkbump(float iHorMov,float iVerMov);
};
class Timerclass{
private:
	Roombaclass& roomba;
    chrono::time_point<chrono::system_clock> start,end;
    bool bRunning;
    double dTimerDuration;
    void timer(/*roombaclass& roomba*/);
public:
    //timerclass(roombaclass &roomba) : timerclass(roomba,0.5){;}
	Timerclass(Roombaclass& roomba,double dTimerDuration);


    void operator()(){timer();}

    void setTimerDuration(double dInput) {dTimerDuration = dInput;}
    double readTimerDuration(void) {return(dTimerDuration);}
    void setTimerEnable(bool bInput) {bRunning = bInput;}
    double readTimerEnable(void) {return(bRunning);}
};

class Roomobjectclass{
public:
    enum roomobjecttypes{roomba=1,wall=2,standard=2,drop,stairs};
protected:
    const float pi = 3.14159265;
    roomobjecttypes roomobjecttype;
public:
	Roomobjectclass(signed int iPosHor, signed int iPosVer, roomobjecttypes roomobjecttypeIn);
	Roomobjectclass(signed int iPosHor, signed int iPosVer, unsigned int iSizeHor, unsigned int iSizeVer, roomobjecttypes roomobjecttypeIn);

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
class Roombaclass : public Roomobjectclass{
private:
    float fAngle;
    float fSpeed;
	Sensorclass& sensors;

public:
	friend ostream& operator<<(ostream& output,const Roombaclass &roomba){
             return (output << roomba.iPosHor << "   " << roomba.iPosVer);
    }

	Roombaclass(Sensorclass& sensors); // <-- die werkte ineens niet
	~Roombaclass();

    void move(float fHorMov,float fVerMov);
    void setangle(float fInputAngle);
    void setspeed(float fInputSpeed);
    float getangle(void) {return(fAngle);}
    float getspeed(void) {return(fSpeed);}

    void drive(void);
};

#endif // FILE

