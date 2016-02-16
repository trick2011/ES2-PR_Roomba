#include "naviclass.hpp"


naviclass::naviclass(const int iSizeHor,const int iSizeVer) : iSizeVer{iSizeVer},iSizeHor{iSizeHor}{
    vector<roomba_state> EmptyVector;
    EmptyVector.resize(iSizeVer,EMPTY);
    RoomGrid.resize(iSizeHor,EmptyVector);
}

naviclass::~naviclass(){
    
}

void naviclass::printgridwhole(void){
 for(signed int y=(iSizeVer-1); y != -1; y--){
    //cout << y << " : ";
    cout << '|';
    for(unsigned int x=0;x<iSizeHor;x++){
        cout << (char)RoomGrid[x][y];   
    }
    cout << '|';
    cout << endl;
 }
}

naviclass::roomba_state naviclass::setgridpoint(const int iXPos,const int iYPos, roomba_state Value){
    if(iXPos >= iSizeHor)
        return(FUNCTIONERROR);
    if(iYPos >= iSizeVer)
        return(FUNCTIONERROR);
    
    RoomGrid[iXPos][iYPos] = Value;
    
    return(RoomGrid[iXPos][iYPos]);
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