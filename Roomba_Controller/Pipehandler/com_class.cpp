#include "com_class.h"

com_class::com_class(){
	makeFIFO();
}

//write fifo
void com_class::writeFIFO(char cTosend){
	FILE *fifo;
	unsigned char message[1];

	//if (cTosend = 'w'|'v'|'x'|'y'|'z') // deze regels is hilarisch hij assigned de georde waarde van w v x y z in cTosend
	if((cTosend == 'w')||(cTosend == 'v')||(cTosend == 'x')||(cTosend == 'y')||(cTosend == 'z'))
	{
		//message[0] = cTosend;
		fifo = fopen(W_FIFO_FILE.c_str(), "w");		
		fwrite(&cTosend,1, 1, fifo);
		fclose(fifo);
	}				
	//error
	else 
	{
		cout << "Something weird has happend";
	} 
}
//read fifo
char com_class::readFIFO(){
	unsigned char readbuf[1];
	FILE *fifo;

	fifo = fopen(R_FIFO_FILE.c_str(), "r");		
	fread(&readbuf, 1, 1, fifo);      
	fclose(fifo);				

	cout<<"pipe: "<<readbuf[0]<<" ";

	return(readbuf[0]);
}


//make read and write fifo
void com_class::makeFIFO(){
	int r_status;
	int w_status;

//Create the reading side FIFO if it does not exist
#ifdef __linux
	r_status = mknod(R_FIFO_FILE.c_str(), S_IFIFO|0666, 0);
#endif
#ifndef __linux
	r_status = -1;
#endif
	if (r_status == -1 )
	{
		cout<<"Cannot create rfifo"<<endl;
	} 
	if(r_status == EEXIST)
		cout << "R_FIFO made" << endl;
	else
	{
		cout<<"R_FIFO made"<< endl;
	}
	//Create the writing side FIFO if it does not exist
#ifdef __linux
	w_status = mknod(W_FIFO_FILE.c_str(), S_IFIFO|0666, 0);
#endif
#ifndef __linux
	w_status = -1;
#endif
	if (w_status == -1 )
	{
		cout<<"Cannot create wfifo"<<endl;
	} 
	if(w_status == EEXIST)
		cout << "W_FIFO made" << endl;
	else
	{
		cout<<"W_FIFO made"<<endl;
	}
}
