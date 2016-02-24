#ifndef OPCODES_H
#define OPCODES_H

#include <stdint.h>
#include <iostream>
#include <vector>
#include <thread>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
//#include <termios.h>        //USed for UART


static const uint8_t Start =                        128;
static const uint8_t Reset =                        7;
static const uint8_t Stop =                         173;
static const uint8_t Baud =                         129; // 1 databyte
static const uint8_t power =                        133;

//mode commands
static const uint8_t safeMode =                     131;
static const uint8_t fullMode =                     132;

//Cleaning Commands
static const uint8_t cleanModeClean =               135;
static const uint8_t cleanModeMax =                 136;
static const uint8_t cleanModeSpot =                134;
static const uint8_t cleanModeSeekDock =            143;

//Actuator Commands
static const uint8_t drive =                        137; // 4 databytes
static const uint8_t brushes =                      138; // 1 databyte
static const uint8_t leds =                         139; // 3 databytes

static const uint8_t song =                         140; // 2N+2 databyes
static const uint8_t playSong =                     141; // 1 databyte

//Sensor request commands
static const uint8_t sensors =                      142; // 1 databyte
static const uint8_t queryList =                    149; // N+1 databytes
static const uint8_t Stream =                       148; // N+1 databytes

//Sensor packets stream receive codes
static const uint8_t bumpAndWheel =                 7; // 1 databyte
static const uint8_t wall =                         8; // 1 databyte
static const uint8_t cliffLeft =                    9; // 1 databyte
static const uint8_t cliffFrontLeft =               10; // 1 databyte
static const uint8_t cliffFrontRight =              11; // 1 databyte
static const uint8_t cliffRight =                   12; // 1 databyte
static const uint8_t virtualWall =                  13; // 1 databyte
static const uint8_t wheelOvercurrents =            14; // 1 databyte
static const uint8_t dirtDetect =                   15; // 1 databyte
static const uint8_t unusedByte =                   16; // 1 databyte -- comes after dirt detect in packet 0,1 or 6
static const uint8_t irReceiver =                   17; // 1 databyte
static const uint8_t distance =                     19; // 2 databytes
static const uint8_t angle =                        20; // 2 databytes
static const uint8_t chargingState =                21; // 1 databyte
static const uint8_t batteryVoltage =               22; // 2 databytes
static const uint8_t batteryCurrent =               23; // 2 databytes
static const uint8_t batteryTemperature =           24; // 1 databyte
static const uint8_t batteryCharge =                25; // 2 databytes
static const uint8_t batteryCapacity =              26; // 2 databytes
static const uint8_t wallSignal =                   27; // 2 databytes
static const uint8_t cliffLeftSignal =              28; // 2 databyte
static const uint8_t cliffFrontLeftSignal =         29; // 2 databyte
static const uint8_t cliffFrontRightSignal =        30; // 2 databyte
static const uint8_t cliffRightSignal =             31; // 2 databyte
static const uint8_t chargingSource =               34; // 1 databyte
static const uint8_t oiMode =                       35; // 1 databyte
static const uint8_t songNumber =                   36; // 1 databyte
static const uint8_t songPlaying =                  37; // 1 databyte
static const uint8_t numberOfPackets =              38; // 1 databyte
static const uint8_t requestedVelocity =            39; // 2 databytes
static const uint8_t requestedRadius =              40; // 2 databytes
static const uint8_t requestedRightVelocity =       41; // 2 databytes
static const uint8_t requestedLeftVelocity =        42; // 2 databytes
static const uint8_t leftEncoderCount =             43; // 2 databytes
static const uint8_t rightEncoderCount =            44; // 2 databytes
static const uint8_t lightBumper =                  45; // 1 databyte
static const uint8_t lightBumpLeftSignal =          46; // 2 databytes
static const uint8_t lightBumpFrontLeftSignal =     47; // 2 databytes
static const uint8_t lightBumpCenterLeftSignal =    48; // 2 databytes
static const uint8_t lightBumpCenterRightSignal =   49;// 2 databytes
static const uint8_t lightBumpFrontRightSignal =    50; // 2 databytes
static const uint8_t lightBumperRightSignal =       51; // 2 databytes
static const uint8_t leftMotorCurrent =             54; // 2 databytes
static const uint8_t rightMotorCurrent =            55; // 2 databytes
static const uint8_t mainBrushMotorCurrent =        56; // 2 databytes
static const uint8_t sideBrushMotorCurrent =        57; // 2 databytes
static const uint8_t statis =                       58; // 1 databyte



class opcodes
{
private:
    int c = 0;
    uint16_t sensorWaarden[58];


public:
    opcodes();


    void print();

    void startRoomba();
    //void drive("speed"); // speedgrades: slow, medium & fast
    //void turnRoomba("angle"); // angle in degrees (-90 to 90)
    void receiveUart();


    uint8_t getBumpAndWheel();
    uint8_t getWall();
    uint8_t getCliffLeft();
    uint8_t getCliffFrontLeft();
    uint8_t getCliffFrontRight();
    uint8_t getCliffRight();
    uint8_t getVirtualWall();
    uint8_t getWheelOvercurrents();
    uint8_t getDirtDetect();
    uint8_t getUnusedByte();
    uint8_t getIrReceiver();
    uint8_t getDistance();
    uint8_t getAngle();
    uint8_t getChargingState();
    uint8_t getBatteryVoltage();
    uint8_t getBatteryCurrent();
    uint8_t getBatteryTemperature();
    uint8_t getBatteryCharge();
    uint8_t getBatteryCapacity();
    uint8_t getWallSignal();
    uint8_t getCliffLeftSignal();
    uint8_t getCliffFrontLeftSignal();
    uint8_t getCliffFrontRightSignal();
    uint8_t getCliffRightSignal();
    uint8_t getChargingSource();
    uint8_t getOiMode();
    uint8_t getSongNumber();
    uint8_t getSongPlaying();
    uint8_t getNumberOfPackets();
    uint8_t getRequestedVelocity();
    uint8_t getRequestedRadius();
    uint8_t getRequestedRightVelocity();
    uint8_t getRequestedLeftVelocity();
    uint8_t getLeftEncoderCount();
    uint8_t getRightEncoderCount();
    uint8_t getLightBumper();
    uint8_t getLightBumpLeftSignal();
    uint8_t getLightBumpFrontLeftSignal();
    uint8_t getLightBumpCenterLeftSignal();
    uint8_t getLightBumpCenterRightSignal();
    uint8_t getLightBumpFrontRightSignal();
    uint8_t getLightBumperRightSignal();
    uint8_t getLeftMotorCurrent();
    uint8_t getRightMotorCurrent();
    uint8_t getMainBrushMotorCurrent();
    uint8_t getSideBrushMotorCurrent();
    uint8_t getStatis();

    /* get individual sensor values */
    uint8_t getBumpRight();
    uint8_t getBumpLeft();
    uint8_t getWheelDropRight();
    uint8_t getWheelDropLeft();

    uint8_t getSideBrushOvercurrent();
    uint8_t getMainBrushOvercurrent();
    uint8_t getRightWheelOvercurrent();
    uint8_t getLeftWheelOvercurrent();
    /*-------------------------------*/

private:
    void sentUart(uint8_t);

    void startUart();
    uint8_t howManyDatabytes(uint8_t code);
    uint8_t blablaUart();
};

#endif // OPCODES_H
