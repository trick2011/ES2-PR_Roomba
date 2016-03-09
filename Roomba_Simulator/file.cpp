#include "file.h"

roomclass::roomclass(){
    sensors = new sensorclass(*this);
    roomba = new roombaclass(sensors);

    roomobjectclass object(0,1);
    roomobjects.push_back(object);

}
roomclass::~roomclass(){
    delete sensors;
    delete roomba;
}

sensorclass::sensorclass(roomclass& room) : room(room){

}
bool sensorclass::checkbump(void){
    if(room.roomobjects.size() != 0){
        for(unsigned int i=0;i<room.roomobjects.size();i++){
            //room.roomobjects[i].testvariable = 0;
        }
    }

    return(false);
}

roomobjectclass::roomobjectclass(signed int iPosHor,signed int iPosVer):iPosHor(iPosHor),iPosVer(iPosVer){
    iSizeHor = 1;
    iSizeVer = 1;
}


roombaclass::roombaclass(sensorclass* sensors):roomobjectclass(0,0),sensors(*sensors){
    fAngle = 0;
    fSpeed = 0;
}
roombaclass::~roombaclass(){

}
void roombaclass::drive(void){
    // sin(angle) * speed = hor movement
    // cos(angle) * speed = ver movementy
    if(sensors.checkbump() == true){
        int iHorMov = sin(fAngle) * fSpeed;
        int iVerMov = cos(fAngle) * fSpeed;
        iPosHor += iHorMov;
        iPosVer += iVerMov;
    }
}

string wallclass::readobjectname(void){
    return(sObjectName);
}
void wallclass::writeobjectname(string sInput){
   sObjectName = sInput;
}
