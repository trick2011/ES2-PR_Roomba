#ifndef NAVICLASS_H
#define NAVICLASS_H

#include <vector>
#include <iostream>
//#include <iomanip>

using namespace std;

class naviclass{
public: 
    enum roomba_state{EMPTY=' ',BLOCKED = 'X',DROP = '~',ROOMBA_U = 'U',ROOMBA_D = 'D',ROOMBA_L = 'L',ROOMBA_R ='R',ROOMBA_LU,ROOMBA_RU,ROOMBA_LD,ROOMBA_RD,FUNCTIONERROR};
    enum figures{CIRCLE=0,SQUARE,TRIANGLE};
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
    roomba_state readpoint(const int  iXPos,const int iYPos);
    bool setgridfigure(const int  iXPos,const int iYPos, naviclass::figures iFigure,const int iSize, naviclass::roomba_state Value);
};

#endif