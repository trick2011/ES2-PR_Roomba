#ifndef NAVICLASS_H
#define NAVICLASS_H

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class naviclass{
public: 
    enum roomba_state{EMPTY=' ',BLOCKED = 'X',DROP,ROOMBA_U = 'U',ROOMBA_D = 'D',ROOMBA_L = 'L',ROOMBA_R ='R',ROOMBA_LU,ROOMBA_RU,ROOMBA_LD,ROOMBA_RD,FUNCTIONERROR};
private:
    int iSizeVer;
    int iSizeHor;
    static const int iInitialiseSizeVer = 20;
    static const int iInitialiseSizeHor = 100;
    
    
    vector<vector<roomba_state> > RoomGrid;
    
    
public:
    naviclass(const int iSizeHor = iInitialiseSizeHor,const int iSizeVer = iInitialiseSizeVer);
    ~naviclass();
    
    void printgridwhole(void);
    roomba_state setgridpoint(const int iXPos,const int iYPos, roomba_state Value);
};

#endif


// const int sizever = 300;
// const int sizehor  = 180;
// 
// enum roomba_state{EMPTY='0',BLOCKED,DROP,ROOMBA_U,ROOMBA_D,ROOMBA_L,ROOMBA_R,ROOMBA_LU,ROOMBA_RU,ROOMBA_LD,ROOMBA_RD};
// 
// using namespace std;
// 
// int main(void){
// roomba_state array[sizehor][sizever] = {};
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