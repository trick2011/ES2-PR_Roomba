#include "naviclass.hpp"


naviclass::naviclass(int iSizeVer, int iSizeHor) : iSizeHor{iSizeHor},iSizeVer{iSizeVer}{
    vector<roomba_state> EmptyVector;
    EmptyVector.resize(iSizeHor,EMPTY);
    RoomGrid.resize(iSizeVer,EmptyVector);
}

naviclass::~naviclass(){
    
}

void naviclass::printgridwhole(void){
 for(signed int y=(iSizeVer-1); y != -1; y--){
    //cout << y << " : ";
    for(unsigned int x=0;x<iSizeHor;x++){
        cout << (char)RoomGrid[y][x];   
    }
    cout << endl;
 }
}

// for(unsigned int i=(sizever-1);i != 0;i--){
//     for(unsigned int j=0;j<sizehor;j++){
//         array[j][i] = EMPTY;
// 	if((i == 9) && (j == 99)){
//             array[j][i] = BLOCKED;
//  	    //cout << "jup" << endl;
// 	}
// 	cout << (char)array[j][i];
//     }
//     cout << endl;
// }