#include "naviclass.hpp"

#include "highlevelsimclass.hpp"

highlevelsimclass::highlevelsimclass(naviclass *pointer) : pSimulator{pointer}{
    pSimulator->setfigure(5,5,pSimulator->TRIANGLE,5,pSimulator->BLOCKED);
    pSimulator->setfigure(13,7,pSimulator->TRIANGLE,5,pSimulator->DROP);
    
    pSimulator->setpoint(5,2,pSimulator->BLOCKED);

    pSimulator->setpoint(0,0,pSimulator->ROOMBA_L);
    pSimulator->setpoint(0,1,pSimulator->ROOMBA_U);
    pSimulator->setpoint(0,2,pSimulator->ROOMBA_R);
    pSimulator->setpoint(0,3,pSimulator->ROOMBA_D);
    pSimulator->setpoint(0,4,pSimulator->ROOMBA_LU);
    pSimulator->setpoint(0,5,pSimulator->ROOMBA_RU);
    pSimulator->setpoint(0,6,pSimulator->ROOMBA_RD);
    pSimulator->setpoint(0,7,pSimulator->ROOMBA_LD);
}
highlevelsimclass::~highlevelsimclass(){

}
void highlevelsimclass::doo(void){
    cout << "doo" << endl;

}
