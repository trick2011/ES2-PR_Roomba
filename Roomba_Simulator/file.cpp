#include "file.h"

roomclass::roomclass(){
    sensors = new sensorclass(*this);
    roomba = new roombaclass(sensors);
#ifdef __WIN32
#ifdef __linux__
	timer = new timerclass(*roomba);
#endif
#endif

    roomobjectclass object(-5,-5,0,10);
    roomobjects.push_back(object);
    roomobjectclass objectb(5,-5,0,10);
    roomobjects.push_back(objectb);


    roomobjectclass objectc(-5,-5,10,0);
    roomobjects.push_back(objectc);

    roomobjectclass objectd(-5,5,10,0);
    roomobjects.push_back(objectd);

}
roomclass::~roomclass(){
    delete sensors;
    delete roomba;
}

sensorclass::sensorclass(roomclass& room) : room(room){
    bBumpLeft = false;
    bBumpRight = false;
}
float sensorclass::calcmultiplication(float iDiffHor, float iDiffVer){
        return((float)(iDiffVer / iDiffHor));
}
bool sensorclass::checkbump(float fHorMov, float fVerMov){
    int iHorMov = fHorMov;
    int iVerMov = fVerMov;
    if(iVerMov == 0){
        if(floatcomp(fVerMov,0.0))
            iVerMov = 0;
        else{
            if(fVerMov > 0)
                iVerMov = 1;
            else
                iVerMov = -1;
        }
    }
    if(iHorMov == 0){
        if(floatcomp(fHorMov,0.0))
            iHorMov = 0;
        else{
            if(fHorMov > 0)
                iHorMov = 1;
            else
                iHorMov = -1;
        }
    }

    if(room.roomobjects.size() != 0){
        if(/*checkbumpUD */floatcomp(iHorMov,0)){
            if(iVerMov>0)
                for(int iPosVer=0;iPosVer<=iVerMov;iPosVer++){
                    if(checkbumpU(room.roomba->iPosHor,(room.roomba->iPosVer+iPosVer)) == true){
                       --iPosVer;
                        //room.roomba->iPosVer += iPosVer;
                        room.roomba->move(0,iPosVer);
                        bBumpLeft = true;
                        bBumpRight = true;
                        return(true);
                    }
                }
            else
                for(int iPosVer=0;iPosVer>=iVerMov;iPosVer--){
                    if(checkbumpD(room.roomba->iPosHor,(room.roomba->iPosVer+iPosVer)) == true){
                        //iPosVer++;
                        //room.roomba->iPosVer += iPosVer;
                        room.roomba->move(0,iPosVer);
                        bBumpLeft = true;
                        bBumpRight = true;
                        return(true);
                    }
                }
        }
        if(/*checkbumpLR */floatcomp(iVerMov,0)){
            if(iHorMov>0)
                for(int iPosHor=0;iPosHor<=iHorMov;iPosHor++){
                    if(checkbumpR((room.roomba->iPosHor+iPosHor),room.roomba->iPosVer) == true){
                        iPosHor--;
                        //room.roomba->iPosHor += iPosHor;
                        room.roomba->move(iPosHor,0);
                        bBumpLeft = true;
                        bBumpRight = true;
                        return(true);
                    }
                }
            else
                for(int iPosHor=0;iPosHor>=iHorMov;iPosHor--){
                    if(checkbumpL((room.roomba->iPosHor+iPosHor),room.roomba->iPosVer) == true){
                        //iPosHor++;
                        //room.roomba->iPosHor += iPosHor;
                        room.roomba->move(iPosHor,0);
                        bBumpLeft = true;
                        bBumpRight = true;
                        return(true);
                    }
                }
        }
        if(/*checkbumpUL*/(iHorMov<0)&&(iVerMov>0)){
            //checkbumpUL();
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
                if(checkbumpUL(room.roomba->iPosHor+viIanswerHor[i],room.roomba->iPosVer+viIanswerVer[i]) == true){
                    //room.roomba->iPosHor += viIanswerHor[i];
                    //room.roomba->iPosVer += viIanswerVer[i];
                    room.roomba->move(viIanswerHor[i],viIanswerVer[i]);
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
                if(checkbumpUR(room.roomba->iPosHor+viIanswerHor[i],room.roomba->iPosVer+viIanswerVer[i]) == true){
//                    room.roomba->iPosHor += viIanswerHor[i-1];
//                    room.roomba->iPosVer += viIanswerVer[i-1];
                    room.roomba->move(viIanswerHor[i],viIanswerVer[i]);
                    return(true);
                }
            }
        }
        if(/*checkbumpDR*/(iHorMov>0)&&(iVerMov<0)){
            //checkbumpDR();
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
                if(checkbumpDR(viIanswerHor[i],viIanswerVer[i]) == true){
                    //room.roomba->iPosHor += viIanswerHor[i];
                    //room.roomba->iPosVer += viIanswerVer[i];
                    room.roomba->move(room.roomba->iPosHor+viIanswerHor[i],room.roomba->iPosVer+viIanswerVer[i]);
                    return(true);
                }
            }
        }
        if(/*checkbumpDL*/(iHorMov<0)&&(iVerMov<0)){
            //checkbumpDL();
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
                if(checkbumpDL(room.roomba->iPosHor+viIanswerHor[i],room.roomba->iPosVer+viIanswerVer[i]) == true){
                    //room.roomba->iPosHor += viIanswerHor[i];
                    //room.roomba->iPosVer += viIanswerVer[i];
                    room.roomba->move(viIanswerHor[i],viIanswerVer[i]);
                    return(true);
            	}
            }
        }
    }

    bBumpLeft = false;
    bBumpRight = false;
    return(false);
}
bool sensorclass::checkbumpL(int iHorPos,int iVerPos){
    for(unsigned int i=0;i<room.roomobjects.size();i++){
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){
                if((iHorPos == iHorI)&&(iVerPos == iVerI)){
                    return(true);
                }
            }
        }
    }
    return(false);
}
bool sensorclass::checkbumpR(int iHorPos,int iVerPos){
    for(unsigned int i=0;i<room.roomobjects.size();i++){
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){
                if((iHorPos == iHorI)&&(iVerPos == iVerI)){
                    return(true);
                }
            }
        }
    }
    return(false);
}
bool sensorclass::checkbumpU(int iHorPos,int iVerPos){
    for(unsigned int i=0;i<room.roomobjects.size();i++){
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){
                if((iHorPos == iHorI)&&(iVerPos == iVerI)){
                    return(true);
                }
            }
        }
    }
    return(false);
}
bool sensorclass::checkbumpD(int iHorPos,int iVerPos){
    for(unsigned int i=0;i<room.roomobjects.size();i++){
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){
                if((iHorPos == iHorI)&&(iVerPos == iVerI)){
                    return(true);
                }
            }
        }
    }
    return(false);
}
bool sensorclass::checkbumpUL(int iHorPos,int iVerPos){
    bool bDoubleBump = false;
    bool bLeftBump = false;
    bool bRightBump = false;
    for(unsigned int i=0;i<room.roomobjects.size();i++){
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){
                if(bDoubleBump == false)
                    bDoubleBump = (iHorPos-1 == iHorI)&&(iVerPos+1 == iVerI);
                if(bLeftBump == false)
                    bLeftBump = (((iHorPos-1) == iHorI)&&(iVerPos == iVerI));
                if(bRightBump == false)
                    bRightBump = ((iHorPos == iHorI)&&((iVerPos+1) == iVerI));
            }

        }
    }
    if(bDoubleBump||bLeftBump||bRightBump){
        if(bDoubleBump){
            bBumpLeft = true;
            bBumpRight = true;
            return(true);
        }
        else{
            if(bLeftBump)
                bBumpLeft = true;
            if(bRightBump)
                bBumpRight = true;
        }
        return(true);
    }
    return(false);
}
bool sensorclass::checkbumpUR(int iHorPos,int iVerPos){
    bool bDoubleBump = false;
    bool bLeftBump = false;
    bool bRightBump = false;
    for(unsigned int i=0;i<room.roomobjects.size();i++){ // dit
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){
                if(bDoubleBump == false)
                    bDoubleBump = (iHorPos+1 == iHorI)&&(iVerPos+1 == iVerI);
                if(bLeftBump == false)
                    bLeftBump = (((iHorPos+1) == iHorI)&&(iVerPos == iVerI));
                if(bRightBump == false)
                    bRightBump = ((iHorPos == iHorI)&&((iVerPos+1) == iVerI));
            }
        }
    }
    if(bDoubleBump||bLeftBump||bRightBump){
        if(bDoubleBump){
            bBumpLeft = true;
            bBumpRight = true;
            return(true);
        }
        else{
            if(bLeftBump)
                bBumpLeft = true;
            if(bRightBump)
                bBumpRight = true;
        }
        return(true);
    }
    return(false);
}
bool sensorclass::checkbumpDL(int iHorPos,int iVerPos){
    bool bDoubleBump = false;
    bool bLeftBump = false;
    bool bRightBump = false;
    for(unsigned int i=0;i<room.roomobjects.size();i++){
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){
                if(bDoubleBump == false)
                    bDoubleBump = ((iHorPos-1) == iHorI)&&((iVerPos-1)== iVerI);
                if(bLeftBump == false)
                    bLeftBump = ((iHorPos == iHorI)&&((iVerPos-1) == iVerI));
                if(bRightBump == false)
                    bRightBump = (((iHorPos-1) == iHorI)&&(iVerPos == iVerI));
            }
        }
    }
    if(bDoubleBump||bLeftBump||bRightBump){
        if(bDoubleBump){
            bBumpLeft = true;
            bBumpRight = true;
            return(true);
        }
        else{
            if(bLeftBump)
                bBumpLeft = true;
            if(bRightBump)
                bBumpRight = true;
        }
        return(true);
    }
    return(false);
}
bool sensorclass::checkbumpDR(int iHorPos,int iVerPos){
    for(unsigned int i=0;i<room.roomobjects.size();i++){
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){
                if((iHorPos == iHorI)&&(iVerPos == iVerI)){
                    bBumpLeft = true;
                    bBumpRight = true;
                    return(true);
                }
                if(((iHorPos-1) == iHorI)&&(iVerPos == iVerI)){
                    bBumpLeft = false;
                    bBumpRight = true;
                    return(true);
                }
                if((iHorPos == iHorI)&&((iVerPos+1) == iVerI)){
                    bBumpLeft = true;
                    bBumpRight = false;
                    return(true);
                }
            }
        }
    }
    return(false);
}
bool sensorclass::floatcomp(float fIn1,float fIn2){
    if(fabs(fIn1-fIn2)>fFloatRange)
        return(false);
    else
        return(true);
}

//#ifdef __WIN32
//#ifdef __linux__
//timerclass::timerclass(roombaclass& roomba):roomba(roomba){
//    timer.it_value.tv_sec = 1;
//	timer.it_value.tv_usec = 0;
//    timer.it_interval.tv_sec = 1;
//	timer.it_interval.tv_usec = 0;
//    signal(SIGALRM, &sigalrm_handler);
//    setitimer(ITIMER_REAL, &timer, NULL);

//}
//void timerclass::sigalrm_handler(int signum){
//	roomba->drive();
//}
//#endif
//#endif

roomobjectclass::roomobjectclass(signed int iPosHor,signed int iPosVer):iPosHor(iPosHor),iPosVer(iPosVer),fPosVer(iPosVer),fPosHor(iPosHor){
    iSizeHor = 0;
    iSizeVer = 0;
}
roomobjectclass::roomobjectclass(signed int iPosHor,signed int iPosVer,unsigned int iSizeHor,unsigned int iSizeVer):iPosHor(iPosHor),iPosVer(iPosVer),fPosVer(iPosVer),fPosHor(iPosHor),iSizeHor(iSizeHor),iSizeVer(iSizeVer){

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
    //float fHorMov = sin((fAngle*(pi/(float)180)) * fSpeed);

    float fHorMov = sin(fAngle*pi/180) * fSpeed;
    float fVerMov = cos(fAngle*pi/180) * fSpeed;


    if(sensors.checkbump(fHorMov,fVerMov) == false){
        move(fHorMov,fVerMov);
    }
}
void roombaclass::setspeed(float fInputSpeed){
    fSpeed = fInputSpeed;
}
void roombaclass::setangle(float fInputAngle){
    fAngle = fInputAngle;
}
void roombaclass::move(float fHorMov,float fVerMov){
    fPosHor += fHorMov;
    fPosVer += fVerMov;

    iPosHor += fPosHor-iPosHor;
    iPosVer += fPosVer-iPosVer;
}

string wallclass::readobjectname(void){
    return(sObjectName);
}
void wallclass::writeobjectname(string sInput){
   sObjectName = sInput;
}
