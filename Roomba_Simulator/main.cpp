#include <iostream>

#include "naviclass.hpp"
#include "highlevelsimclass.hpp"

using namespace std;

int main(void){
    
    naviclass Roomgrid{20,20};
    highlevelsimclass Simulator{&Roomgrid};
    
    //Roomgrid.printgridwhole();
    //cout << endl;
//    Roomgrid.setgridpoint(5,2,Roomgrid.BLOCKED);
    
//     Roomgrid.setgridfigure(5,5,Roomgrid.TRIANGLE,5,Roomgrid.BLOCKED);
//     Roomgrid.setgridfigure(13,7,Roomgrid.TRIANGLE,5,Roomgrid.DROP);
    Roomgrid.printgridwhole();
    
    return(0);
}