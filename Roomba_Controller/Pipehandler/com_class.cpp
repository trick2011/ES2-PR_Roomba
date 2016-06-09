#include "com_class.h"

com_class::com_class():ctp_FIFOref{ctp_FIFO_FILE}{
	makeFIFO();
	//ctpFIFO = fopen(ctp_FIFO_FILE.c_str(), "w");
    ptcFIFO = fopen(ptc_FIFO_FILE.c_str(), "r");
}

com_class::~com_class(){
	//fclose(ctpFIFO);
    fclose(ptcFIFO);
}

//write fifo
void com_class::writeFIFO(char cTosend){
    //FILE *fifo;
    //ctp
	unsigned char message[1];

	//if (cTosend = 'w'|'v'|'x'|'y'|'z') // deze regels is hilarisch hij assigned de georde waarde van w v x y z in cTosend
	if((cTosend == 'w')||(cTosend == 'v')||(cTosend == 'x')||(cTosend == 'y')||(cTosend == 'z')||(cTosend == ' '))
	{
		//message[0] = cTosend;
		//fwrite(&cTosend,1, 1, ctpFIFO);
		message[0] = cTosend;
		fwrite(&message[0],1, 1, ctpFIFO);
		//sleep(1);
		//cout << message[0] << endl;
//		fflush(ctpFIFO);
//        fclose(ctpFIFO);
//        ctpFIFO = fopen(ctp_FIFO_FILE.c_str(), "w");

	}				
	//error
	else 
	{
		cout << "Something weird has happend";
	} 
}
//read fifo
char com_class::readFIFO(){
    unsigned char readbuf;
    //ptc


    while(0 == fread(&readbuf, 1, 1, ptcFIFO)){}

#ifdef VERBOSE
    cout<<"pipe: "<<readbuf<< endl;
#endif

    return(readbuf);
}


//make read and write fifo
void com_class::makeFIFO(){
	int r_status;
//	int w_status;

//Create the reading side FIFO if it does not exist
#ifdef __linux
    r_status = mknod(ptc_FIFO_FILE.c_str(), S_IFIFO|0666, 0);
#endif
#ifndef __linux
	r_status = -1;
#endif

//    if(r_status == EEXIST)
//        cout << "R_FIFO made" << endl;
//    else{
        if (r_status == -1 )
            cout<<"Cannot create rfifo"<<endl;
        else
            cout<<"R_FIFO made"<< endl;
//    }


//	//Create the writing side FIFO if it does not exist
//#ifdef __linux
//    w_status = mknod(ctp_FIFO_FILE.c_str(), S_IFIFO|0666, 0);
//#endif
//#ifndef __linux
//    w_status = -1;
//#endif

////	if(w_status == EEXIST)
////		cout << "W_FIFO made" << endl;
////    else{
//        if (w_status == -1 )
//            cout<<"Cannot create wfifo"<<endl;
//        else
//            cout<<"W_FIFO made"<<endl;
////	}
}
