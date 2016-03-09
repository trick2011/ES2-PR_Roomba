#include "file.h"

roomclass::roomclass(){
    sensors = new sensorclass(*this);
    roomba = new roombaclass;

}
roomclass::~roomclass(){
    delete sensors;
    delete roomba;
}

sensorclass::sensorclass(roomclass& room) : room(room){

}
void sensorclass::checkbump(void){

}

roomobjectclass::roomobjectclass(signed int iPosHor,signed int iPosVer):iPosHor(iPosHor),iPosVer(iPosVer){
    iSizeHor = 1;
    iSizeVer = 1;
}


roombaclass::roombaclass():roomobjectclass(0,0){
    fAngle = 0;
    fSpeed = 0;
}
roombaclass::~roombaclass(){

}
void roombaclass::drive(void){
    // sin(angle) * speed = hor movement
    // cos(angle) * speed = ver movement
    int iHorMov = sin(fAngle) * fSpeed;
    int iVerMov = cos(fAngle) * fSpeed;
    iPosHor += iHorMov;
    iPosVer += iVerMov;
}
