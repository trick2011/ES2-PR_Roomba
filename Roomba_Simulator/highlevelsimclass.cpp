#include "naviclass.hpp"

#include "highlevelsimclass.hpp"

highlevelsimclass::highlevelsimclass(naviclass *pointer) : pSimulator{pointer}{
    pSimulator->setgridfigure(5,5,pSimulator->TRIANGLE,5,pSimulator->BLOCKED);
    pSimulator->setgridfigure(13,7,pSimulator->TRIANGLE,5,pSimulator->DROP);
    
    pSimulator->setgridpoint(5,2,pSimulator->BLOCKED);    

    pSimulator->setgridpoint(0,0,pSimulator->ROOMBA_L);
    pSimulator->setgridpoint(0,1,pSimulator->ROOMBA_U);
    pSimulator->setgridpoint(0,2,pSimulator->ROOMBA_R);
    pSimulator->setgridpoint(0,3,pSimulator->ROOMBA_D);
    pSimulator->setgridpoint(0,4,pSimulator->ROOMBA_LU);
    pSimulator->setgridpoint(0,5,pSimulator->ROOMBA_RU);
    pSimulator->setgridpoint(0,6,pSimulator->ROOMBA_RD);
    pSimulator->setgridpoint(0,7,pSimulator->ROOMBA_LD);
}
highlevelsimclass::~highlevelsimclass(){

}
void highlevelsimclass::doo(void){
    cout << "doo" << endl;

}
