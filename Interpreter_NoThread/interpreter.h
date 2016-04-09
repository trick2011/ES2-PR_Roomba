#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

#include "opcodes.h"
#include "../Roomba_Interpreter/UART/uart.h"
#include "fail_error.h"

#define debug
#define fulldebug
//std::chrono::milliseconds interval(500);

class UARTClass;

class interpreter
{
public:
    interpreter();
    ~interpreter();

    void startRoomba();
    void stopRoomba();

    void brushes(int);

    void drives(int s); // speedgrades: slow, medium & fast
    void turnRoomba(int16_t angle); // angle in degrees

    void failSave();

    bool getBumpAndWheel();
    uint8_t getWall();
    uint8_t getCliffLeft();
    uint8_t getCliffFrontLeft();
    uint8_t getCliffFrontRight();
    uint8_t getCliffRight();
    uint8_t getVirtualWall();
    bool getWheelOvercurrents();
    uint8_t getDirtDetect();
    uint8_t getIrReceiver();
    int16_t getDistance();
    int16_t getAngle();
    uint8_t getChargingState();
    uint16_t getBatteryVoltage();
    int16_t getBatteryCurrent();
    int8_t getBatteryTemperature();
    uint16_t getBatteryCharge();
    uint16_t getBatteryCapacity();
    uint16_t getWallSignal();
    uint16_t getCliffLeftSignal();
    uint16_t getCliffFrontLeftSignal();
    uint16_t getCliffFrontRightSignal();
    uint16_t getCliffRightSignal();
    uint8_t getChargingSource();
    uint8_t getOiMode();
    uint8_t getSongNumber();
    uint8_t getSongPlaying();
    int16_t getRequestedVelocity();
    int16_t getRequestedRadius();
    int16_t getRequestedRightVelocity();
    int16_t getRequestedLeftVelocity();
    uint16_t getLeftEncoderCount();
    uint16_t getRightEncoderCount();
    bool getLightBumper();
    uint16_t getLightBumpLeftSignal();
    uint16_t getLightBumpFrontLeftSignal();
    uint16_t getLightBumpCenterLeftSignal();
    uint16_t getLightBumpCenterRightSignal();
    uint16_t getLightBumpFrontRightSignal();
    uint16_t getLightBumpRightSignal();
    int16_t getLeftMotorCurrent();
    int16_t getRightMotorCurrent();
    int16_t getMainBrushMotorCurrent();
    int16_t getSideBrushMotorCurrent();
    uint8_t getStatis();

    /* get individual sensor values */
    bool getBumpRight();
    bool getBumpLeft();
    bool getWheelDropRight();
    bool getWheelDropLeft();

    bool getSideBrushOvercurrent();
    bool getMainBrushOvercurrent();
    bool getRightWheelOvercurrent();
    bool getLeftWheelOvercurrent();
    /*-------------------------------*/


//private:
    // automode functions //
    void startAutoMode();
    void autoMode();
    std::thread AUTO;

    bool autoRunning;

    struct sWheelDrops
    {
        bool bLeft = false;
        bool bRight;
    };
    struct sOverCurrent
    {
        bool bWheelLeft;
        bool bWheelRight;
        bool bMainBrush;
        bool bSideBrush;
    };
    struct sCliff
    {
        bool bLeft;
        bool bFrontLeft;
        bool bFrontRight;
        bool bRight;
    };
    struct sInfraRed
    {
        bool bLeft;
        bool bRight;
        bool bClose;
    };
    struct sBumps
    {
        bool bLeft;
        bool bRight;
    };
    struct sWall
    {
        bool bRight;
        bool bFrontRight;
        bool bCenterRight;
        bool bCenterLeft;
        bool bFrontLeft;
        bool bLeft;
    };
public:
    sWheelDrops WheelDrops;
    sOverCurrent OverCurrent;
    sCliff Cliff;
    sInfraRed InfraRed;
    sBumps Bumps;
    sWall Wall;

    // end automode functions //


    UARTClass *uart;
    bool stopFailSave = false;
    std::mutex sendTex;

    void stopFailSaveThread();

};

#endif // INTERPRETER_H