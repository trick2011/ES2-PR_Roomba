#include "naviclass.hpp"

//#define TEST

naviclass::naviclass(const int iSizeHor,const int iSizeVer) : iSizeVer{iSizeVer},iSizeHor{iSizeHor}{
    vector<roomba_state> EmptyVector;
    EmptyVector.resize(iSizeVer,EMPTY);
    RoomGrid.resize(iSizeHor,EmptyVector);
}

naviclass::~naviclass(){
    
}

void naviclass::printgridwhole(void){
#ifdef TEST
    cout << "entered: printgridwhole" << endl;
#endif
 for(signed int y=(iSizeVer-1); y != -1; y--){
    //cout << y << " : ";
    cout << '|';
    for(unsigned int x=0;x<iSizeHor;x++){
        switch (RoomGrid[x][y]) {
        case ROOMBA_L: cout << "\u2190";break;
        case ROOMBA_U: cout << "\u2191";break;
        case ROOMBA_R: cout << "\u2192";break;
        case ROOMBA_D: cout << "\u2193";break;
        case ROOMBA_LU: cout << "\u2196";break;
        case ROOMBA_RU: cout << "\u2197";break;
        case ROOMBA_RD: cout << "\u2198";break;
        case ROOMBA_LD: cout << "\u2199";break;
        default:
            cout << (char)RoomGrid[x][y];
            break;
        }
    }
    cout << '|';
    cout << endl;
 }
}

naviclass::roomba_state naviclass::setgridpoint(const int iXPos,const int iYPos, roomba_state Value){
#ifdef TEST
    cout << "entered: setgridpoint" << endl;
#endif
    if(iXPos >= iSizeHor)
        return(FUNCTIONERROR);
    if(iYPos >= iSizeVer)
        return(FUNCTIONERROR);
    
    RoomGrid[iXPos][iYPos] = Value;
    
    return(RoomGrid[iXPos][iYPos]);
}

naviclass::roomba_state naviclass::readpoint(const int  iXPos,const int iYPos){
    return(RoomGrid[iXPos][iYPos]);
}

bool naviclass::setgridfigure(const int  iXPos,const int iYPos, naviclass::figures iFigure,const int iSize, naviclass::roomba_state Value){
    switch(iFigure){
        case naviclass::CIRCLE: if(((iXPos + iSize)<iSizeHor)&&((iYPos + iSize)<iSizeVer)){
                                    for(unsigned int x=0;x<iSize;x++){
                                        for(unsigned int y=0;y<iSize;y++){
                                            RoomGrid[x+iXPos][y+iYPos] = Value;
                                        }
                                    }
                                    RoomGrid[iXPos + iSize-1][iYPos+iSize-1] = EMPTY;
                                    RoomGrid[iXPos + iSize-1][iYPos] = EMPTY;
                                    RoomGrid[iXPos][iYPos+iSize-1] = EMPTY;
                                    RoomGrid[iXPos][iYPos] = EMPTY;
                                }
                                else
                                    return(false);
                                break;
        case naviclass::SQUARE:if(((iXPos + iSize)<iSizeHor)&&((iYPos + iSize)<iSizeVer)){
                                    for(unsigned int x=0;x<iSize;x++){
                                        for(unsigned int y=0;y<iSize;y++){
                                            RoomGrid[x+iXPos][y+iYPos] = Value;
                                        }
                                    }
                                }
                                else
                                    return(false);
                                break;
        case naviclass::TRIANGLE: if(((iXPos + iSize)<iSizeHor)&&((iYPos + iSize)<iSizeVer)){
                                    int iLeftBound = iXPos, iRightBound = (iXPos+iSize),iLevel=iYPos;
                                    int iWalker=iXPos;
                                    while(iLevel <= iSize+iYPos){
                                        while((iWalker >= iLeftBound)&&(iWalker < iRightBound)){
                                            RoomGrid[iWalker][iLevel] = Value;
                                            iWalker++;
                                        }
                                        iRightBound--;
                                        iLeftBound++;
                                        iWalker = iLeftBound;
                                        iLevel++;
                                    }
                                }
                                else
                                    return(false);
                                break;
    }
    return(true);
}
