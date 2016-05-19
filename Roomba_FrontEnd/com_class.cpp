#include "com_class.h"

//write fifo
void com_class::writeFIFO(char cTosend){
	FILE *fifo;
	unsigned char message[1];

	if (cTosend = 'w'|'v'|'x'|'y'|'z')
	{
		message[0] = cTosend;		
		fifo = fopen(W_FIFO_FILE.c_str(), "w");		
		fwrite(&message,1, 1, fifo);		
		fclose(fifo);
	}				
	//error
	else 
	{
		printf("Something weird has happend");
	} 
}
//read fifo
char com_class::readFIFO(){
	unsigned char readbuf[1];
	char cBuff;
	FILE *fifo;

	fifo = fopen(R_FIFO_FILE.c_str(), "r");		
	fread(&readbuf, 1, 1, fifo);      
	fclose(fifo);				

	cBuff = readbuf[0]; 
	cout<<"pipe: "<<cBuff<<" ";

	//error: pipe empty
	if(readbuf[0] == NULL)
	{
		cBuff = 'o';  
		return cBuff;
	}
	//if pipe != empty, passtrough data
	else
	{	
		cBuff = readbuf[0]; 
		return cBuff;
	}                        
}


//make read and write fifo
void com_class::makeFIFO(){
	int r_status;
	int w_status;

//Create the reading side FIFO if it does not exist
	r_status = mknod(R_FIFO_FILE.c_str(), S_IFIFO|0666, 0);
	if (r_status == -1 ) 
	{
		cout<<"Cannot create rfifo"<<endl;
	} 
	else
	{
		cout<<"R_FIFO made"<< endl;
	}
	//Create the writing side FIFO if it does not exist
		w_status = mknod(W_FIFO_FILE.c_str(), S_IFIFO|0666, 0);
	if (w_status == -1 ) 
	{
		cout<<"Cannot create wfifo"<<endl;
	} 
	else
	{
		cout<<"W_FIFO made"<<endl;
	}
}
