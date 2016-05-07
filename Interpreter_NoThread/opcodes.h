#ifndef OPCODES_H
#define OPCODES_H
#include <stdint.h>

namespace roomba {


    static const uint8_t Start =                        128;
    static const uint8_t Reset =                        7;
    static const uint8_t Stop =                         173;
    static const uint8_t Baud =                         129; // 1 databyte
    static const uint8_t power =                        133;



    //mode commands
    namespace modes {
    static const uint8_t safeMode =                     131;
    static const uint8_t fullMode =                     132;
    }

    //Cleaning Commands
    namespace cleanModes{
    static const uint8_t Clean =                        135;
    static const uint8_t Max =                          136;
    static const uint8_t Spot =                         134;
    static const uint8_t SeekDock =                     143;
    }

    //Actuator Commands
    static const uint8_t drive =                        137; // 4 databytes
    static const uint8_t brushes =                      138; // 1 databyte
    static const uint8_t leds =                         139; // 3 databytes

    static const uint8_t song =                         140; // 2N+2 databyes
    static const uint8_t playSong =                     141; // 1 databyte

    //Sensor request commands
    namespace requestType{
        static const uint8_t individual =                   142; // 1 databyte
        static const uint8_t queryList =                    149; // N+1 databytes
        static const uint8_t Stream =                       148; // N+1 databytes
    }
    
    namespace sensors{
        static const uint8_t bumpAndWheel =                 7; // 1 databyte
        static const uint8_t wall =                         8; // 1 databyte
        static const uint8_t cliffLeft =                    9; // 1 databyte
        static const uint8_t cliffFrontLeft =               10; // 1 databyte
        static const uint8_t cliffFrontRight =              11; // 1 databyte
        static const uint8_t cliffRight =                   12; // 1 databyte
        static const uint8_t virtualWall =                  13; // 1 databyte
        static const uint8_t wheelOvercurrents =            14; // 1 databyte
        static const uint8_t dirtDetect =                   15; // 1 databyte
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
        static const uint8_t lightBumpCenterRightSignal =   49; // 2 databytes
        static const uint8_t lightBumpFrontRightSignal =    50; // 2 databytes
        static const uint8_t lightBumpRightSignal =         51; // 2 databytes
        static const uint8_t leftMotorCurrent =             54; // 2 databytes
        static const uint8_t rightMotorCurrent =            55; // 2 databytes
        static const uint8_t mainBrushMotorCurrent =        56; // 2 databytes
        static const uint8_t sideBrushMotorCurrent =        57; // 2 databytes
        static const uint8_t statis =                       58; // 1 databyte
    }

    namespace charger {

        static const uint8_t Red =                      248;
        static const uint8_t Green =                    244;
        static const uint8_t RedAndGreen =              252;
        static const uint8_t RedAndForceField =         250;
        static const uint8_t GreenAndForField =         246;
        static const uint8_t RedGreenAndForceField =    254;

    }

    namespace speed {
        static const int SLOW =                         0;
        static const int CRUISE =                       1;
        static const int FAST =                         2;
        static const int STOP =                         3;
        static const int BACKWARDS  =                   4;
    }

    namespace brush{

        static const uint8_t NOBRUSH =                  0x00;
        static const uint8_t SIDEBRUSH =                0x01;
        static const uint8_t MAINBRUSH =                0x04;
        static const uint8_t BOTH =                     0x05;
    }
    namespace radius {
        static const int SMALL_LEFT =                   0;
        static const int BIG_LEFT =                     1;
        static const int SMALL_RIGHT =                  2;
        static const int BIG_RIGHT =                    3;
    }

}

#endif // OPCODES_H
