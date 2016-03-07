#include <iostream>

#include "naviclass.hpp"
#include "highlevelsimclass.hpp"

using namespace std;

int main(void){
    
    naviclass Roomgrid{20,20};
    highlevelsimclass Simulator{&Roomgrid};

    Roomgrid.printgridwhole();    
    return(0);
}
