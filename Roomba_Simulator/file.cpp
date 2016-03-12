#include "file.h"

roomclass::roomclass(){
    sensors = new sensorclass(*this);
    roomba = new roombaclass(sensors);

    roomobjectclass object(0,5);
    roomobjects.push_back(object);

}
roomclass::~roomclass(){
    delete sensors;
    delete roomba;
}

sensorclass::sensorclass(roomclass& room) : room(room){

}
float sensorclass::calcmultiplication(float iDiffHor, float iDiffVer){
        return((float)(iDiffVer / iDiffHor));
}
bool sensorclass::checkbump(int iHorMov, int iVerMov){
    if(room.roomobjects.size() != 0){
        if(/*checkbumpUD */iHorMov == 0){
            if(iVerMov>0)
                for(int iPosVer=0;iPosVer<iVerMov;iPosVer++){
                    if(checkbumpU(room.roomba->iPosHor,(room.roomba->iPosVer+iPosVer)) == true){
                        iPosVer--;
                        room.roomba->iPosVer += iPosVer;
                        bBumpLeft = true;
                        bBumpLeft = true;
                        return(true);
                    }
                }
            else
                for(int iPosVer=0;iPosVer>iVerMov;iPosVer--){
                    if(checkbumpD(room.roomba->iPosHor,(room.roomba->iPosVer+iPosVer)) == true){
                        iPosVer++;
                        room.roomba->iPosVer += iPosVer;
                        bBumpLeft = true;
                        bBumpLeft = true;
                        return(true);
                    }
                }
        }
        if(/*checkbumpLR */iVerMov == 0){
            if(iHorMov>0)
                for(int iPosHor=0;iPosHor<iHorMov;iPosHor++){
                    if(checkbumpR((room.roomba->iPosHor+iPosHor),room.roomba->iPosVer) == true){
                        iPosHor--;
                        room.roomba->iPosHor += iPosHor;
                        bBumpLeft = true;
                        bBumpRight = true;
                        return(true);
                    }
                }
            else
                for(int iPosHor=0;iPosHor>iHorMov;iPosHor--){
                    if(checkbumpL((room.roomba->iPosHor+iPosHor),room.roomba->iPosVer) == true){
                        iPosHor++;
                        room.roomba->iPosHor += iPosHor;
                        bBumpLeft = true;
                        bBumpRight = true;
                        return(true);
                    }
                }
        }
        if(/*checkbumpUL*/(iHorMov<0)&&(iVerMov>0)){
            //checkbumpUL();
            #warning "THE FOLLOWING CODE HAS YET TO BE COMPILED AND TESTED"
            int iResult=0;

            float fResult;
            vector<int> viIanswerVer;
            vector<int> viIanswerHor;
            bool bAnswerUsed = false;
            
            for(float fCounterHor=0;fCounterHor>((float)iHorMov-0.1);fCounterHor-=0.1){
            	fResult = calcmultiplication((float)iHorMov,(float)iVerMov);
            	iResult= (int)(fResult * fCounterHor);
            	bAnswerUsed = false;
            	for(unsigned int i=0;i<viIanswerVer.size();i++){
            
            		if(viIanswerVer[i] == iResult){
            			bAnswerUsed = true;
            			break;
            		}
            
            	}
            	if(bAnswerUsed == false){
            		viIanswerVer.push_back(iResult);
            		viIanswerHor.push_back((int)fCounterHor);
            	}
            
            }
            for(unsigned int i=0;i<viIanswerHor.size();i++){
            	if(checkbumpUR(viIanswerHor[i],viIanswerVer[i]) == true){
            		room.roomba->iPosHor += viIanswerHor[i];
            		room.roomba->iPosVer += viIanswerVer[i];
                    return(true);
            	}
            }
        }
        if(/*checkbumpUR*/(iHorMov>0)&&(iVerMov>0)){
            //checkbumpUR();
            int iResult=0;

            float fResult;
            vector<int> viIanswerVer;
            vector<int> viIanswerHor;
            bool bAnswerUsed = false;

            for(float fCounterHor=0;fCounterHor<((float)iHorMov+0.1);fCounterHor+=0.1){
                fResult = calcmultiplication((float)iHorMov,(float)iVerMov);
                iResult= (int)(fResult * fCounterHor);
                bAnswerUsed = false;
                for(unsigned int i=0;i<viIanswerVer.size();i++){

                    if(viIanswerVer[i] == iResult){
                        bAnswerUsed = true;
                        break;
                    }

                }
                if(bAnswerUsed == false){
                    viIanswerVer.push_back(iResult);
                    viIanswerHor.push_back((int)fCounterHor);
                }

            }
            for(unsigned int i=0;i<viIanswerHor.size();i++){
                if(checkbumpUR(viIanswerHor[i],viIanswerVer[i]) == true){
                    room.roomba->iPosHor += viIanswerHor[i];
                    room.roomba->iPosVer += viIanswerVer[i];
                    return(true);
                }
            }
        }
        if(/*checkbumpDR*/(iHorMov>0)&&(iVerMov<0)){
            //checkbumpDR();
            #warning "THE FOLLOWING CODE HAS YET TO BE COMPILED AND TESTED"
            int iResult=0;

            float fResult;
            vector<int> viIanswerVer;
            vector<int> viIanswerHor;
            bool bAnswerUsed = false;

            for(float fCounterHor=0;fCounterHor<((float)iHorMov+0.1);fCounterHor+=0.1){
                fResult = calcmultiplication((float)iHorMov,(float)iVerMov);
                iResult= (int)(fResult * fCounterHor);
                bAnswerUsed = false;
                for(unsigned int i=0;i<viIanswerVer.size();i++){

                    if(viIanswerVer[i] == iResult){
                        bAnswerUsed = true;
                        break;
                    }

                }
                if(bAnswerUsed == false){
                    viIanswerVer.push_back(iResult);
                    viIanswerHor.push_back((int)fCounterHor);
                }

            }
            for(unsigned int i=0;i<viIanswerHor.size();i++){
                if(checkbumpUR(viIanswerHor[i],viIanswerVer[i]) == true){
                    room.roomba->iPosHor += viIanswerHor[i];
                    room.roomba->iPosVer += viIanswerVer[i];
                    return(true);
                }
            }
        }
        if(/*checkbumpDL*/(iHorMov<0)&&(iVerMov<0)){
            //checkbumpDL();
            #warning "THE FOLLOWING CODE HAS YET TO BE COMPILED AND TESTED"
            int iResult=0;

            float fResult;
            vector<int> viIanswerVer;
            vector<int> viIanswerHor;
            bool bAnswerUsed = false;
            
            for(float fCounterHor=0;fCounterHor>((float)iHorMov-0.1);fCounterHor-=0.1){
            	fResult = calcmultiplication((float)iHorMov,(float)iVerMov);
            	iResult= (int)(fResult * fCounterHor);
            	bAnswerUsed = false;
            	for(unsigned int i=0;i<viIanswerVer.size();i++){
            
            		if(viIanswerVer[i] == iResult){
            			bAnswerUsed = true;
            			break;
            		}
            
            	}
            	if(bAnswerUsed == false){
            		viIanswerVer.push_back(iResult);
            		viIanswerHor.push_back((int)fCounterHor);
            	}
            
            }
            for(unsigned int i=0;i<viIanswerHor.size();i++){
            	if(checkbumpUR(viIanswerHor[i],viIanswerVer[i]) == true){
            		room.roomba->iPosHor += viIanswerHor[i];
            		room.roomba->iPosVer += viIanswerVer[i];
                    return(true);
            	}
            }
        }
//        for(unsigned int i=0;i<room.roomobjects.size();i++){

//            for(int iHorI=room.roomobjects[i].iPosHor;iHorI<(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor+1);iHorI++){
//                for(int iVerI=room.roomobjects[i].iPosVer;iVerI<(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer+1);iVerI++){
//                    // check for other speed if(iHorMov != 1||iVerMov != 1){}
//                    if((iHorMov != 1 && iHorMov != -1)||(iVerMov != 1 && iVerMov != -1)){
//                        char iSelector = 0;
//                        if(iHorMov < 0){
//                            iSelector += 1;
//                        }
//                        if(iVerMov < 0){
//                            iSelector += 2;
//                        }
////                        switch(iSelector){
////                            case 0:
////                            case 1:
////                            case 2:
////                            case 3:
////                            default:
////                        }

//                    }
//                    else{
//                        if(((room.roomba->iPosHor+iHorMov) == iHorI)&&((room.roomba->iPosVer+iVerMov) == iVerI)){
//                            return(true);
//                        }
//                    }
//                }
//            }
//        }
    }

    return(false);
}
bool sensorclass::checkbumpL(int iHorPos,int iVerPos){
    return(false);
}
bool sensorclass::checkbumpR(int iHorPos,int iVerPos){
    return(false);
}
bool sensorclass::checkbumpU(int iHorPos,int iVerPos){
for(unsigned int i=0;i<room.roomobjects.size();i++){
    for(int iHorI=room.roomobjects[i].iPosHor;iHorI<(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor+1);iHorI++){
        for(int iVerI=room.roomobjects[i].iPosVer;iVerI<(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer+1);iVerI++){
            if((iHorPos == iHorI)&&(iVerPos == iVerI)){
                return(true);
            }
        }
    }
}
return(false);
}
bool sensorclass::checkbumpD(int iHorPos,int iVerPos){
    return(false);
}
bool sensorclass::checkbumpUL(int iHorPos,int iVerPos){
    return(false);
}
bool sensorclass::checkbumpUR(int iHorPos,int iVerPos){
    return(false);
}
bool sensorclass::checkbumpDL(int iHorPos,int iVerPos){
    return(false);
}
bool sensorclass::checkbumpDR(int iHorPos,int iVerPos){
    return(false);
}


roomobjectclass::roomobjectclass(signed int iPosHor,signed int iPosVer):iPosHor(iPosHor),iPosVer(iPosVer){
    iSizeHor = 0;
    iSizeVer = 0;
}


roombaclass::roombaclass(sensorclass* sensors):roomobjectclass(0,0),sensors(*sensors){
    fAngle = 0;
    fSpeed = 0;
}
roombaclass::~roombaclass(){

}
void roombaclass::drive(void){
    // sin(angle) * speed = hor movement
    // cos(angle) * speed = ver movementy
    int iHorMov = sin(fAngle) * fSpeed;
    int iVerMov = cos(fAngle) * fSpeed;

    if(sensors.checkbump(iHorMov,iVerMov) == false){
        iPosHor += iHorMov;
        iPosVer += iVerMov;
    }
}
void roombaclass::setspeed(float fInputSpeed){
    fSpeed = fInputSpeed;
}

string wallclass::readobjectname(void){
    return(sObjectName);
}
void wallclass::writeobjectname(string sInput){
   sObjectName = sInput;
}
