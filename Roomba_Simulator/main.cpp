#include <iostream>
#include <string>

#include "file.h"

using namespace std;

int main()
{
    //roomobjectclass *roomba;
    //roomba = new roombaclass(null);
    //delete roomba;
    roomclass room;
    for(int i;i<10;i++){
        room.roomba->setspeed(1);
        cout << room.roomba->iPosHor << " " << room.roomba->iPosVer << endl;
        room.roomba->drive();
        cout << room.roomba->iPosHor << " " << room.roomba->iPosVer << endl;
    }
    return 0;
}

