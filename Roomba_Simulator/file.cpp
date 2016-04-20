#include "file.h"

/**
 * @brief roomclass::roomclass
 * standard constructor for roomclass.
 * during testing it will create objects on its own for testing purposes.
 */
roomclass::roomclass(){
    sensors = new sensorclass(*this);
    roomba = new roombaclass(*sensors);
    

    roomobjectclass object(-5,-5,0,10,roomobjectclass::drop);
    roomobjects.push_back(object);
    roomobjectclass objectb(5,-5,0,10,roomobjectclass::drop);
    roomobjects.push_back(objectb);


    roomobjectclass objectc(-5,-5,10,0,roomobjectclass::drop);
    roomobjects.push_back(objectc);

    roomobjectclass objectd(-5,5,10,0,roomobjectclass::drop);
    roomobjects.push_back(objectd);
}
/**
 * @brief roomclass::~roomclass
 * default constructor
 */
roomclass::~roomclass(){
    delete sensors;
    delete roomba;
}

/**
 * @brief sensorclass::sensorclass
 * @param room
 * Default constructor for sensorclass and takes a reference param room in order to access the room
 */
sensorclass::sensorclass(roomclass& room) : room(room),bWheelDropLeft{false},bWheelDropRight{false},bBumpLeft{false},bBumpRight{false},iWallSignal{0},
iCliffLeftSignal{false},iCliffFrontLeftSignal{false},iCliffFrontSignal{false},iCliffFrontRightSignal{false},iCliffRightSignal{false},iLightBumpLeft{false},
iLightBumpFrontLeft{iLightBumpLeft},iLightBumpCenter{false},iLightBumpFrontRight{iLightBumpRight},iLightBumpRight{false},bCliffLeft{false},bCliffFrontLeft{false},
bCliffFrontRight{false},bCliffRight{false},bWallBump{false}{}
sensorclass::~sensorclass(){
    if(vsErrorVector.empty()){
        ofstream ofp;
        ofp.open("errorlog_sensorclass.txt",fstream::out|fstream::app);

        time_t end_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        ofp << std::ctime(&end_time) << endl;

        //ofp << ctime(çhrono::system_clock::to_time now());
        for(auto i: vsErrorVector){
            ofp << i << endl;
        }
        ofp.close();
    }
}

/**
 * @brief sensorclass::calcmultiplication
 * @param iDiffHor
 * @param iDiffVer
 * @return float
 */
inline float sensorclass::calcmultiplication(float iDiffHor, float iDiffVer){
        return((float)(iDiffVer / iDiffHor));
}
/**
 * @brief sensorclass::checkbump
 * @param fHorMov
 * @param fVerMov
 * @return
 * This function implements at the moment (20-03-16) the feature of sensorclass
 * to detect objects and to stop the roomba.
 * In the future this will also implement the soft bump and cliff sensors
 */
bool sensorclass::checkbump(float fHorMov, float fVerMov){
    /** The following code makes sure that if a value is below 1 and
     *  above -1 and is not equal to 0 (+/- fFloatRange) that it wil
     *  be rounded up or down to the nearest full int value.
     */
    bool bReturnValue = false;
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

    if(room.roomobjects.size() != 0){ /**< check if there are objects inside the room other than the roomba. if not do nothing an return false **/
        //#warning "the following code should be optimized, it will now evaluate all if statements altough a if statement has already been true"
        /**< The following if statements will check the direction of the movement and trigger the right checkbumpXX() function **/

        checkLightBump(); /**< this does NOT work yet **/

        if(/*checkbumpUD */floatcomp(iHorMov,0)){    /**< if the direction is vertical    **/
            if(iVerMov>0) /**< check if vertical movement is positive or negative **/
                for(int iPosVer=0;iPosVer<=iVerMov;iPosVer++){ /**< follow the complete move path through and check for obstacles **/
                    if(checkbumpU(room.roomba->iPosHor,(room.roomba->iPosVer+iPosVer)) == true){
                       //--iPosVer;
                        room.roomba->move(0,iPosVer);
                        return(true);
                    }
                }
            else
                for(int iPosVer=0;iPosVer>=iVerMov;iPosVer--){ /**< follow the complete move path through and check for obstacles **/
                    if(checkbumpD(room.roomba->iPosHor,(room.roomba->iPosVer+iPosVer)) == true){ /**< check the current position + movement for objects **/
                        room.roomba->move(0,iPosVer);
                        return(true);
                    }
                }
            resetphysicalsensors();
            return(bReturnValue);
        }
        if(/*checkbumpLR */floatcomp(iVerMov,0)){    /**< if the direction is horizontal  **/
            if(iHorMov>0) /**< check if horizontal movement is positive or negative **/
                for(int iPosHor=0;iPosHor<=iHorMov;iPosHor++){ /**< follow the complete move path through and check for obstacles **/
                    if(checkbumpR((room.roomba->iPosHor+iPosHor),room.roomba->iPosVer) == true){
                        //iPosHor--;
                        room.roomba->move(iPosHor,0);
                        return(true);
                    }
                }
            else
                for(int iPosHor=0;iPosHor>=iHorMov;iPosHor--){ /**< follow the complete move path through and check for obstacles **/
                    if(checkbumpL((room.roomba->iPosHor+iPosHor),room.roomba->iPosVer) == true){
                        room.roomba->move(iPosHor,0);
                        return(true);
                    }
                }
            resetphysicalsensors();
            return(bReturnValue);
        }
        if(/*checkbumpUL*/(iHorMov<0)&&(iVerMov>0)){ /**< if the direction is diagonal UL **/
            //checkbumpUL();
            int iResult=0;
            float fResult;
            vector<int> viIanswerVer;
            vector<int> viIanswerHor;
            bool bAnswerUsed = false;
            
            /** This code analyses the diagonal path the roomba will take an find the x,y integer positions where the roomba will move through.
              * Those x,y positions will be pushed inside the vectors and tested for bumps by checkbumpUL()
              */
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
            for(unsigned int i=0;i<viIanswerHor.size();i++){ /**< check the found x,y positions for obstacles **/
                if(checkbumpUL(room.roomba->iPosHor+viIanswerHor[i],room.roomba->iPosVer+viIanswerVer[i]) == true){
                    room.roomba->move(viIanswerHor[i],viIanswerVer[i]);
                    return(true);
            	}
            }
            resetphysicalsensors();
            return(bReturnValue);
        }
        if(/*checkbumpUR*/(iHorMov>0)&&(iVerMov>0)){ /**< if the direction is diagonal UR **/
            //checkbumpUR();
            int iResult=0;
            float fResult;
            vector<int> viIanswerVer;
            vector<int> viIanswerHor;
            bool bAnswerUsed = false;

            /** This code analyses the diagonal path the roomba will take an find the x,y integer positions where the roomba will move through.
              * Those x,y positions will be pushed inside the vectors and tested for bumps by checkbumpUL()
              */
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
            for(unsigned int i=0;i<viIanswerHor.size();i++){ /**< check the found x,y positions for obstacles **/
                if(checkbumpUR(room.roomba->iPosHor+viIanswerHor[i],room.roomba->iPosVer+viIanswerVer[i]) == true){
                    room.roomba->move(viIanswerHor[i],viIanswerVer[i]);
                    return(true);
                }
            }
            resetphysicalsensors();
            return(bReturnValue);
        }
        if(/*checkbumpDR*/(iHorMov>0)&&(iVerMov<0)){ /**< if the direction is diagonal DL **/
            //checkbumpDR();
            int iResult=0;

            float fResult;
            vector<int> viIanswerVer;
            vector<int> viIanswerHor;
            bool bAnswerUsed = false;

            /** This code analyses the diagonal path the roomba will take an find the x,y integer positions where the roomba will move through.
              * Those x,y positions will be pushed inside the vectors and tested for bumps by checkbumpUL()
              */
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
            for(unsigned int i=0;i<viIanswerHor.size();i++){ /**< check the found x,y positions for obstacles **/
                if(checkbumpDR(room.roomba->iPosHor+viIanswerHor[i],room.roomba->iPosVer+viIanswerVer[i]) == true){
                    //room.roomba->iPosHor += viIanswerHor[i];
                    //room.roomba->iPosVer += viIanswerVer[i];
                    room.roomba->move(viIanswerHor[i],viIanswerVer[i]);
                    return(true);
                }
            }
            resetphysicalsensors();
            return(bReturnValue);
        }
        if(/*checkbumpDL*/(iHorMov<0)&&(iVerMov<0)){ /**< if the direction is diagonal DR **/
            //checkbumpDL();
            int iResult=0;

            float fResult;
            vector<int> viIanswerVer;
            vector<int> viIanswerHor;
            bool bAnswerUsed = false;

            /** This code analyses the diagonal path the roomba will take an find the x,y integer positions where the roomba will move through.
              * Those x,y positions will be pushed inside the vectors and tested for bumps by checkbumpUL()
              */
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
            for(unsigned int i=0;i<viIanswerHor.size();i++){ /**< check the found x,y positions for obstacles **/
                if(checkbumpDL(room.roomba->iPosHor+viIanswerHor[i],room.roomba->iPosVer+viIanswerVer[i]) == true){
                    //room.roomba->iPosHor += viIanswerHor[i];
                    //room.roomba->iPosVer += viIanswerVer[i];
                    room.roomba->move(viIanswerHor[i],viIanswerVer[i]);
                    return(true);
                }
            }
            resetphysicalsensors();
            return(bReturnValue);
        }
    }

    //resetlightbump();
    resetphysicalsensors();
    return(bReturnValue);
}
/**
 * @brief sensorclass::checkbumpL
 * @param iHorPos
 * @param iVerPos
 * @return
 * This function checks for a bump at the position where the roomba will move into.
 */
bool sensorclass::checkbumpL(int iHorPos,int iVerPos){
    for(unsigned int i=0;i<room.roomobjects.size();i++){ /**< loops through all objects inside the room**/
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){ /**< loops through all horizontal positions of that object **/
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){ /**< loops throught all vertical positions of that object **/
                if((iHorPos-1 == iHorI)&&(iVerPos == iVerI)){
                    //resetphysicalsensors();
                    switch(room.roomobjects[i].getroomobjecttype()){
                        case roomobjectclass::drop:
                                                    bCliffFrontLeft = true;
                                                    bCliffFrontRight = true;
                                                    break;
                        case roomobjectclass::roomba:
                                                    bBumpLeft = true;
                                                    bBumpRight = true;
                                                    break;
                        //case roomobjectclass::stairs: break;
                        case roomobjectclass::wall:
                                                    bBumpLeft = true;
                                                    bBumpRight = true;
                                                    break;
                        default: break;
                    }
                    return(true);
                }
            }
        }
    }
    return(false);
}
/**
 * @brief sensorclass::checkbumpR
 * @param iHorPos
 * @param iVerPos
 * @return
 * This function checks for a bump at the position where the roomba will move into.
 */
bool sensorclass::checkbumpR(int iHorPos,int iVerPos){
    for(unsigned int i=0;i<room.roomobjects.size();i++){ /**< loops through all objects inside the room**/
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){ /**< loops through all horizontal positions of that object **/
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){ /**< loops throught all vertical positions of that object **/
                if((iHorPos+1 == iHorI)&&(iVerPos == iVerI)){
                    //resetphysicalsensors();
                    switch(room.roomobjects[i].getroomobjecttype()){
                        case roomobjectclass::drop:
                                                    bCliffLeft = false;
                                                    bCliffFrontLeft = true;
                                                    bCliffFrontRight = true;
                                                    bCliffRight = false;
                                                    break;
                        case roomobjectclass::roomba:
                                                    bBumpLeft = true;
                                                    bBumpRight = true;
                                                    break;
                        //case roomobjectclass::stairs: break;
                        case roomobjectclass::wall:
                                                    bBumpLeft = true;
                                                    bBumpRight = true;
                                                    break;
                        default: break;
                    }
                    return(true);
                }
            }
        }
    }
    return(false);
}
/**
 * @brief sensorclass::checkbumpU
 * @param iHorPos
 * @param iVerPos
 * @return
 * This function checks for a bump at the position where the roomba will move into.
 */
bool sensorclass::checkbumpU(int iHorPos,int iVerPos){
    for(unsigned int i=0;i<room.roomobjects.size();i++){ /**< loops through all objects inside the room**/
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){ /**< loops through all horizontal positions of that object **/
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){ /**< loops throught all vertical positions of that object **/
                if((iHorPos == iHorI)&&(iVerPos+1 == iVerI)){
                    //resetphysicalsensors();
                    switch(room.roomobjects[i].getroomobjecttype()){
                        case roomobjectclass::drop:
                                                    bCliffLeft = false;
                                                    bCliffFrontLeft = true;
                                                    bCliffFrontRight = true;
                                                    bCliffRight = false;
                                                    break;
                        case roomobjectclass::roomba:
                                                    bBumpLeft = true;
                                                    bBumpRight = true;
                                                    break;
                        //case roomobjectclass::stairs: break;
                        case roomobjectclass::wall:
                                                    bBumpLeft = true;
                                                    bBumpRight = true;
                                                    break;
                        default: break;
                    }
                    return(true);
                }
            }
        }
    }
    return(false);
}
/**
 * @brief sensorclass::checkbumpD
 * @param iHorPos
 * @param iVerPos
 * @return
 * This function checks for a bump at the position where the roomba will move into.
 */
bool sensorclass::checkbumpD(int iHorPos,int iVerPos){
    for(unsigned int i=0;i<room.roomobjects.size();i++){ /**< loops through all objects inside the room**/
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){ /**< loops through all horizontal positions of that object **/
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){ /**< loops throught all vertical positions of that object **/
                if((iHorPos == iHorI)&&(iVerPos-1 == iVerI)){
                    //resetphysicalsensors();
                    switch(room.roomobjects[i].getroomobjecttype()){
                        case roomobjectclass::drop:
                                                    bCliffLeft = false;
                                                    bCliffFrontLeft = true;
                                                    bCliffFrontRight = true;
                                                    bCliffRight = false;
                                                    break;
                        case roomobjectclass::roomba:
                                                    bBumpLeft = true;
                                                    bBumpRight = true;
                                                    break;
                        //case roomobjectclass::stairs: break;
                        case roomobjectclass::wall:
                                                    bBumpLeft = true;
                                                    bBumpRight = true;
                                                    break;
                        default: break;
                    }
                    return(true);
                }
            }
        }
    }
    return(false);
}
/**
 * @brief sensorclass::checkbumpUL
 * @param iHorPos
 * @param iVerPos
 * @return
 * This function checks for a bump at the position where the roomba will move into.
 */
bool sensorclass::checkbumpUL(int iHorPos,int iVerPos){
    int iPositions[3]{0,0,0};
    bool bDoubleBump = false;
    bool bLeftBump = false;
    bool bRightBump = false;
    for(unsigned int i=0;i<room.roomobjects.size();i++){ /**< loops through all objects inside the room**/
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){ /**< loops through all horizontal positions of that object **/
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){ /**< loops throught all vertical positions of that object **/
                if(bDoubleBump == false){
                    iPositions[0] = i;
                    bDoubleBump = (iHorPos-1 == iHorI)&&(iVerPos+1 == iVerI);
                }
                if(bLeftBump == false){
                    iPositions[2] = i;
                    bLeftBump = (((iHorPos-1) == iHorI)&&(iVerPos == iVerI));
                }
                if(bRightBump == false){
                    iPositions[3] = i;
                    bRightBump = ((iHorPos == iHorI)&&((iVerPos+1) == iVerI));
                }
            }

        }
    }
    if(bDoubleBump||bLeftBump||bRightBump){ /**< if any bumps where detected set the senor bools **/
        setbumpcomplex(bDoubleBump,bLeftBump,bRightBump,iPositions[0],iPositions[1],iPositions[2]);
        return(true);
    }
    return(false);
}
/**
 * @brief sensorclass::checkbumpUR
 * @param iHorPos
 * @param iVerPos
 * @return
 * This function checks for a bump at the position where the roomba will move into.
 */
bool sensorclass::checkbumpUR(int iHorPos,int iVerPos){
    int iPositions[3]{0,0,0};
    bool bDoubleBump = false;
    bool bLeftBump = false;
    bool bRightBump = false;
    for(unsigned int i=0;i<room.roomobjects.size();i++){ /**< loops through all objects inside the room**/
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){ /**< loops through all horizontal positions of that object **/
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){ /**< loops throught all vertical positions of that object **/
                if(bDoubleBump == false){
                    iPositions[0] = i;
                    bDoubleBump = (iHorPos+1 == iHorI)&&(iVerPos+1 == iVerI);
                    if(bDoubleBump)
                        bDoubleBump = true;
                }
                if(bLeftBump == false){
                    iPositions[1] = i;
                    bLeftBump = (((iHorPos+1) == iHorI)&&(iVerPos == iVerI));
                }
                if(bRightBump == false){
                    iPositions[2] = i;
                    bRightBump = ((iHorPos == iHorI)&&((iVerPos+1) == iVerI));
                }
            }
        }
    }
    if(bDoubleBump||bLeftBump||bRightBump){ /**< if any bumps where detected set the senor bools **/
        //setbumpcomplex(bDoubleBump,bLeftBump,bRightBump,iPostions[0]);
        resetphysicalsensors();
        setbumpcomplex(bDoubleBump,bLeftBump,bRightBump,iPositions[0],iPositions[1],iPositions[2]);
//        if(bDoubleBump){
//            switch(room.roomobjects[iPositions[0]].getroomobjecttype()){
//                case roomobjectclass::drop:
//                                            bCliffLeft = true;
//                                            bCliffFrontLeft = true;
//                                            bCliffFrontRight = true;
//                                            bCliffRight = true;
//                                            break;
//                case roomobjectclass::roomba:
//                                            bBumpLeft = true;
//                                            bBumpRight = true;
//                                            break;
//                //case roomobjectclass::stairs: break;
//                case roomobjectclass::wall:
//                                            bBumpLeft = true;
//                                            bBumpRight = true;
//                                            break;
//                default: break;
//            }
//            return(true);
//        }
//        else{
//            if(bLeftBump)
//                switch(room.roomobjects[iPositions[1]].getroomobjecttype()){
//                    case roomobjectclass::drop:
//                                                bCliffLeft = true;
//                                                bCliffFrontLeft = true;
//                                                break;
//                    case roomobjectclass::roomba:
//                                                bBumpLeft = true;
//                                                break;
//                    case roomobjectclass::wall:
//                                                bBumpLeft = true;
//                                                break;
//                    default: break;
//                }
//            if(bRightBump)
//                switch(room.roomobjects[iPositions[2]].getroomobjecttype()){
//                    case roomobjectclass::drop:
//                                                bCliffFrontRight = true;
//                                                bCliffRight = true;
//                                                break;
//                    case roomobjectclass::roomba:
//                                                bBumpRight = true;
//                                                break;
//                    //case roomobjectclass::stairs: break;
//                    case roomobjectclass::wall:
//                                                bBumpRight = true;
//                                                break;
//                    default: break;
//                }
//                return(true);
//        }
        return(true);
    }
    return(false);
}
/**
 * @brief sensorclass::checkbumpDL
 * @param iHorPos
 * @param iVerPos
 * @return
 * This function checks for a bump at the position where the roomba will move into.
 */
bool sensorclass::checkbumpDL(int iHorPos,int iVerPos){
    int iPositions[3]{0,0,0};
    bool bDoubleBump = false;
    bool bLeftBump = false;
    bool bRightBump = false;
    for(unsigned int i=0;i<room.roomobjects.size();i++){ /**< loops through all objects inside the room**/
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){ /**< loops through all horizontal positions of that object **/
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){ /**< loops throught all vertical positions of that object **/
                if(bDoubleBump == false){
                    iPositions[0] = i;
                    bDoubleBump = ((iHorPos-1) == iHorI)&&((iVerPos-1)== iVerI);
                }
                if(bLeftBump == false){
                    iPositions[1] = 0;
                    bLeftBump = ((iHorPos == iHorI)&&((iVerPos-1) == iVerI));
                }
                if(bRightBump == false){
                    iPositions[2] = 0;
                    bRightBump = (((iHorPos-1) == iHorI)&&(iVerPos == iVerI));
                }
            }
        }
    }
    if(bDoubleBump||bLeftBump||bRightBump){ /**< if any bumps where detected set the senor bools **/
        setbumpcomplex(bDoubleBump,bLeftBump,bRightBump,iPositions[0],iPositions[1],iPositions[2]);
        return(true);
    }
    return(false);
}
/**
 * @brief sensorclass::checkbumpDR
 * @param iHorPos
 * @param iVerPos
 * @return
 * This function checks for a bump at the position where the roomba will move into.
 */
bool sensorclass::checkbumpDR(int iHorPos,int iVerPos){
    int iPositions[3]{0,0,0};
    bool bDoubleBump = false;
    bool bLeftBump = false;
    bool bRightBump = false;
    for(unsigned int i=0;i<room.roomobjects.size();i++){ /**< loops through all objects inside the room**/
        for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){ /**< loops through all horizontal positions of that object **/
            for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){ /**< loops throught all vertical positions of that object **/
                if(bDoubleBump == false){
                    iPositions[0] = i;
                    bDoubleBump = (iHorPos+1 == iHorI)&&(iVerPos-1 == iVerI);
                }
                if(bLeftBump == false){
                    iPositions[1] = i;
                    bLeftBump = (((iHorPos+1) == iHorI)&&(iVerPos == iVerI));
                }
                if(bRightBump == false){
                    iPositions[2] = i;
                    bRightBump = ((iHorPos == iHorI)&&((iVerPos-1) == iVerI));
                }
            }
        }
    }
    if(bDoubleBump||bLeftBump||bRightBump){ /**< if any bumps where detected set the senor bools **/
        setbumpcomplex(bDoubleBump,bLeftBump,bRightBump,iPositions[0],iPositions[1],iPositions[2]);
        return(true);
    }
    return(false);
}
/**
 * @brief sensorclass::floatcomp
 * @param fIn1
 * @param fIn2
 * @return float
 * checks if fIn1 ~= fIn2
 */
bool sensorclass::floatcomp(float fIn1,float fIn2){
    if(fabs(fIn1-fIn2)>fFloatRange)
        return(false);
    else
        return(true);
}
void sensorclass::resetphysicalsensors(void){
    bBumpLeft = false;
    bBumpRight = false;

    bCliffLeft = false;
    bCliffFrontLeft = false;
    bCliffFrontRight = false;
    bCliffRight = false;
}
void sensorclass::resetlightbump(void){
    iLightBumpLeft = 0;
    iLightBumpFrontLeft = 0;
    iLightBumpCenter = 0;
    iLightBumpFrontRight = 0;
    iLightBumpRight = 0;
}
void sensorclass::setbumpcomplex(bool bDoubleBump,bool bLeftBump,bool bRightBump,int iPositionOne,int iPositionTwo,int iPositionThree){
    resetphysicalsensors();
    if(bDoubleBump){
        switch(room.roomobjects[iPositionOne].getroomobjecttype()){
            case roomobjectclass::drop:
                                        bCliffLeft = true;
                                        bCliffFrontLeft = true;
                                        bCliffFrontRight = true;
                                        bCliffRight = true;
                                        break;
            case roomobjectclass::roomba:
                                        bBumpLeft = true;
                                        bBumpRight = true;
                                        break;
            //case roomobjectclass::stairs: break;
            case roomobjectclass::wall:
                                        bBumpLeft = true;
                                        bBumpRight = true;
                                        break;
            default:    stringstream ss;
                        string tmp;
                        ss << "Defaulted inside bDoubleBump with info: " << bDoubleBump << " " << bLeftBump <<" "<< bRightBump << " " << iPositionOne << " " << iPositionTwo << " " << iPositionThree << endl;
                        getline(ss,tmp);
                        vsErrorVector.push_back(tmp); break;
        }
        return;
    }
    else{
        if(bLeftBump)
            switch(room.roomobjects[iPositionTwo].getroomobjecttype()){
                case roomobjectclass::drop:
                                            bCliffLeft = true;
                                            bCliffFrontLeft = true;
                                            break;
                case roomobjectclass::roomba:
                                            bBumpLeft = true;
                                            break;
                case roomobjectclass::wall:
                                            bBumpLeft = true;
                                            break;
                default: stringstream ss;
                        string tmp;
                        ss << "Defaulted inside bLeftBump with info: " << bDoubleBump << " " << bLeftBump <<" "<< bRightBump << " " << iPositionOne << " " << iPositionTwo << " " << iPositionThree << endl;
                        getline(ss,tmp);
                        vsErrorVector.push_back(tmp); break;
            }
        if(bRightBump)
            switch(room.roomobjects[iPositionThree].getroomobjecttype()){
                case roomobjectclass::drop:
                                            bCliffFrontRight = true;
                                            bCliffRight = true;
                                            break;
                case roomobjectclass::roomba:
                                            bBumpRight = true;
                                            break;
                //case roomobjectclass::stairs: break;
                case roomobjectclass::wall:
                                            bBumpRight = true;
                                            break;
                default:    stringstream ss;
                            string tmp;
                            ss << "Defaulted inside bRightBump with info: " << bDoubleBump << " " << bLeftBump <<" "<< bRightBump << " " << iPositionOne << " " << iPositionTwo << " " << iPositionThree << endl;
                            getline(ss,tmp);
                            vsErrorVector.push_back(tmp); break;
            }
            return;
    }
}
void sensorclass::checkLightBump(void){
    //room.roomba->iPosHor
    //room.roomba->iPosVer
    bool bReturnBool = false;
    if(checkLightBumpUL())
        bReturnBool = true;
    if(checkLightBumpUR())
        bReturnBool = true;
    if(checkLightBumpU())
        bReturnBool = true;
    if(!bReturnBool)
        resetlightbump();
    return;
}
bool sensorclass::checkLightBumpUL(void){
    for(unsigned int iPos=iLightBumpRange;iPos>0;--iPos){
        for(unsigned int i=0;i<room.roomobjects.size();i++){ /**< loops through all objects inside the room**/
            for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){ /**< loops through all horizontal positions of that object **/
                for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){ /**< loops throught all vertical positions of that object **/
                    //iHorI
                    //iVerI
                    if(((room.roomba->iPosHor+static_cast<signed int>(iPos)) == iHorI)&&((room.roomba->iPosVer+static_cast<signed int>(iPos)) == iVerI)){
                        iLightBumpLeft = determineLightBumpValue(iPos,iPos);
                        //iLightBumpFrontLeft = iLightBumpLeft;

                        return(true);
                    }
                }

            }
        }
    }
    return(false);
}
bool sensorclass::checkLightBumpUR(void){
    for(unsigned int iPos=0;iPos<iLightBumpRange;++iPos){
        for(unsigned int i=0;i<room.roomobjects.size();i++){ /**< loops through all objects inside the room**/
            for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){ /**< loops through all horizontal positions of that object **/
                for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){ /**< loops throught all vertical positions of that object **/
                    //iHorI
                    //iVerI
                    if(((room.roomba->iPosHor+static_cast<signed int>(iPos)) == iHorI)&&((room.roomba->iPosVer+static_cast<signed int>(iPos)) == iVerI)){
                        iLightBumpRight = determineLightBumpValue(iPos,iPos);
                        //iLightBumpFrontRight = iLightBumpRight;
                        return(true);
                    }
                }

            }
        }
    }
    return(false);
}
bool sensorclass::checkLightBumpU(void){
    for(unsigned int iPos=0;iPos>iLightBumpRange;++iPos){
        for(unsigned int i=0;i<room.roomobjects.size();i++){ /**< loops through all objects inside the room**/
            for(int iHorI=room.roomobjects[i].iPosHor;iHorI<=(room.roomobjects[i].iPosHor+(signed int)room.roomobjects[i].iSizeHor);iHorI++){ /**< loops through all horizontal positions of that object **/
                for(int iVerI=room.roomobjects[i].iPosVer;iVerI<=(room.roomobjects[i].iPosVer+(signed int)room.roomobjects[i].iSizeVer);iVerI++){ /**< loops throught all vertical positions of that object **/
                    //iHorI
                    //iVerI
                    if(((room.roomba->iPosHor) == iHorI)&&((room.roomba->iPosVer+static_cast<signed int>(iPos)) == iVerI)){
                        iLightBumpCenter = determineLightBumpValue(0,iPos);
                        return(true);
                    }
                }

            }
        }
    }
    return(false);
}
unsigned int sensorclass::determineLightBumpValue(const unsigned int iHor,const unsigned int iVer){

    // steps = pythagoras(iHor,iVer);
    float fDistance = exp(iHor) + exp(iVer);
    fDistance = sqrt(fDistance);

    unsigned int uiReturnValue = iLightBumpValueMax - ((static_cast<float>(iLightBumpValueMax)/static_cast<float>(iLightBumpRange))*fDistance);
    // lightbumpvalue = total - (total / maxsteps) * steps;

    //// iLightBumpRange
    //unsigned int uiReturnValue = iLightBumpValueMax - (static_cast<float>(iLightBumpValueMax)/static_cast<float>(iLightBumpRange));
    return(uiReturnValue);
}


timerclass::timerclass(roombaclass& roomba,double dTimerDurationb = 0.5):roomba(roomba),dTimerDuration{dTimerDurationb}{
    //thread timerthread(thread(timerclass::timer,roomba),this);

    //timer();
}
void timerclass::timer(/*roombaclass& roomba*/){
    start = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds;
    while(bRunning){
        end = chrono::system_clock::now();
        elapsed_seconds = end - start;
        if(elapsed_seconds.count() >= dTimerDuration){
            start = chrono::system_clock::now();
            roomba.drive();
            //cout << "TEST" << endl;
        }

    }
}

/**
 * @brief roomobjectclass::roomobjectclass
 * @param iPosHor
 * @param iPosVer
 * standard roomobjectclass constructor
 */
roomobjectclass::roomobjectclass(signed int iPosHor,signed int iPosVer, roomobjecttypes roomobjecttypeIn = roomobjectclass::standard):iPosHor(iPosHor),iPosVer(iPosVer),fPosVer(iPosVer),fPosHor(iPosHor){
    iSizeHor = 0;
    iSizeVer = 0;
    roomobjecttype = /*roomobjectclass::*/roomobjecttypeIn;
}
/**
 * @brief roomobjectclass::roomobjectclass
 * @param iPosHor
 * @param iPosVer
 * @param iSizeHor
 * @param iSizeVer
 * second constructor for roomobjectclass
 */
roomobjectclass::roomobjectclass(signed int iPosHor,signed int iPosVer,unsigned int iSizeHor,unsigned int iSizeVer, roomobjecttypes roomobjecttypeIn = roomobjectclass::standard):iPosHor(iPosHor),iPosVer(iPosVer),fPosVer(iPosVer),fPosHor(iPosHor),iSizeHor(iSizeHor),iSizeVer(iSizeVer){
    roomobjecttype = /*roomobjectclass::*/roomobjecttypeIn;
}

/**
 * @brief roombaclass::roombaclass
 * @param sensors
 * default constructor for roombaclass
 */
roombaclass::roombaclass(sensorclass& sensors):roomobjectclass(0,0,roomobjectclass::roomba),sensors(sensors){
    fAngle = 0;
    fSpeed = 0;
    //roomobjecttype = /*roomobjectclass::*/roomba;

    timerclass timer(*this,0.5);
    thread tTimerThread(timer);
    tTimerThread.detach();
}

roombaclass::~roombaclass(){

}
/**
 * @brief roombaclass::drive
 * this function drives the roomba relative to the 0,0 point and makes sure that the float and int values are ~ equal AND make check the bumps
 */
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
/**
 * @brief roombaclass::setspeed
 * @param fInputSpeed
 * fSpeed setter
 */
void roombaclass::setspeed(float fInputSpeed){
    fSpeed = fInputSpeed;
}
/**
 * @brief roombaclass::setangle
 * @param fInputAngle
 * sAngle setter
 */
void roombaclass::setangle(float fInputAngle){
    fAngle += fInputAngle;
}
/**
 * @brief roombaclass::move
 * @param fHorMov
 * @param fVerMov
 * move the float and int values
 */
void roombaclass::move(float fHorMov,float fVerMov){
    fPosHor += fHorMov;
    fPosVer += fVerMov;

    iPosHor += fPosHor-iPosHor;
    iPosVer += fPosVer-iPosVer;
}

///**
// * @brief wallclass::readobjectname
// * @return
// */
//string wallclass::readobjectname(void){
//    return(sObjectName);
//}
///**
// * @brief wallclass::writeobjectname
// * @param sInput
// */
//void wallclass::writeobjectname(string sInput){
//   sObjectName = sInput;
//}
