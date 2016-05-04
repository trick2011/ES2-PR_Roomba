#include "pipehandler.h"

#ifdef __linux
bool pipehandler::makeFIFO(){
    /* Create the FIFO if it does not exist */
    umask(0777); // dit was 0666
    if (mknod(FIFO_FILE.c_str(), S_IFIFO|0777, 0) == -1 ){
        std::cout << "Cannot create fifo\n" << std::endl;
        return(true);
    }
    else{
        std::cout << "FIFO made" << std::endl;
        return(false);
    }
    return(false);
}

bool pipehandler::openfifo(void){

    return(false);
}

char pipehandler::readFIFO(){
    unsigned char readbuf[1];

    //fifo = fopen(FIFO_FILE.c_str(), "r");		//printf("past fopen\n");
    if(fifo != NULL)
        fread(&readbuf, 1, 1, fifo);
    //fclose(fifo);				//printf("read pipe closed\n");

    return(*readbuf);
}
void pipehandler::writeFIFO(char cTosend){
//    fifo = fopen(FIFO_FILE.c_str(), "w");		//printf("past open\n");
    if(fifo != NULL)
        fwrite(&cTosend,1, 1, fifo);		//printf("past write\n");
//    fclose(fifo);				//printf("pipe closed\n");
}
 #endif
