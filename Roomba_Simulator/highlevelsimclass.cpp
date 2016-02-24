#include "naviclass.hpp"

#include "highlevelsimclass.hpp"

highlevelsimclass::highlevelsimclass(naviclass *pointer) : pSimulator{pointer}{
    pSimulator->setgridfigure(5,5,pSimulator->TRIANGLE,5,pSimulator->BLOCKED);
    pSimulator->setgridfigure(13,7,pSimulator->TRIANGLE,5,pSimulator->DROP);
    
    pSimulator->setgridpoint(5,2,pSimulator->BLOCKED);    
}
highlevelsimclass::~highlevelsimclass(){

}
void highlevelsimclass::doo(void){
    cout << "doo" << endl;

}