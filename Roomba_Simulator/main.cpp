#include <iostream>

#include "naviclass.hpp"

using namespace std;

int main(void){
    
    naviclass Roomgrid{10,4};
    
    Roomgrid.printgridwhole();
    cout << endl;
    Roomgrid.setgridpoint(5,2,Roomgrid.BLOCKED);
    Roomgrid.printgridwhole();
    
    return(0);
}