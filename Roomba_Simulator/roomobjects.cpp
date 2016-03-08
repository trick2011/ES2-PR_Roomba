#include "roomobjects.h"

roomclass::roomclass(){
    roomba = new roombaclass;
    sensors = new sensorclass(roomba,this);
}
roomclass::~roomclass(){
    delete roomba;
    delete sensors;
}

roomobjectclass::roomobjectclass(){

}
roomobjectclass::roomobjectclass(signed int iPosHor,signed int iPosVer):iPosHor(iPosHor),iPosVer(iPosVer),iVerSize(1),iHorSize(1){

}

sensorclass::sensorclass(roomobjectclass* roomba,roomclass * room): roomba(roomba),room(room){
    //room->roomobjects.push_back(wallclass());
}

stairclass::stairclass():roomobjectclass(0,0){

}
stairclass::stairclass(signed int iPosHor, signed int iPosVer):roomobjectclass(iPosHor,iPosVer){

}

wallclass::wallclass():roomobjectclass(0,0){

}
wallclass::wallclass(signed int iPosHor, signed int iPosVer):roomobjectclass(iPosHor,iPosVer){

}

roombaclass::roombaclass():roomobjectclass(0,0){
}
void roombaclass::drive(){
// sin()
// cos()
// bepaal rijafstand in richting
}
