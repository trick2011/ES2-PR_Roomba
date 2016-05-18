#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <linux/stat.h>
#include "macros.h"
//#include "com_class.h"
//#include "check_class.h"

using namespace std;

class Communicate{
private:
        const std::string R_FIFO_FILE{"/tmp/rFIFO"}; //pipe to recieve
	const std::string W_FIFO_FILE{"/tmp/wFIFO"}; //pipe to send
public:

        void writeFIFO(char cTosend);
        char readFIFO();
        void makeFIFO();
};

class check_class : public Communicate{
private:
	bool Auto_clean_Flag;
	bool Man_clean_Flag;
	bool Dock_roomba_Flag;
public:
//	bool Auto_clean_Flag;
//	bool Man_clean_Flag;
//	bool Dock_roomba_Flag;
	void pipe_checker();
	int function_type_checker(char cCommand);
	int function_activator_static(char cCommand);
	int function_activator_volitail(char cCommand);
};


int main()
{
	check_class check_object;
	check_object.makeFIFO();

	while(1){
		//check_object.pipe_checker();
		cout<<"test"<<endl;
		sleep(1);}
	
return 0;
}

	//bool Auto_clean_Flag;
	//bool Man_clean_Flag;
	//bool Dock_roomba_Flag;

//pipe checker
	void check_class::pipe_checker(){
	char cRcommand;
	check_class pipe_object;
	cRcommand = pipe_object.readFIFO();
	if(cRcommand == 'k'){sleep(1);}
	else{pipe_object.function_type_checker(cRcommand);}
	}

//function devider
	int check_class::function_type_checker(char cCommand){
	check_class functiondevider_object;	
	//static function
	if(cCommand >= 'e' && cCommand <= 'g'){functiondevider_object.function_activator_static(cCommand);}
	//volitail function
	else if(cCommand >= 'a' && cCommand <= 'd'){
		int check = functiondevider_object.function_activator_volitail(cCommand);
		if(check == -1){return -1;}
		else{return 0;}}
	//error
	else{return -1;}	
	}
//static function selector
	int check_class::function_activator_static(char cCommand){
	switch(cCommand){
		case 'e':	//AutoClean
			if(Auto_clean_Flag == false){Auto_clean_Flag = true; cout<<"AutoClean ON"<<endl;}
			else if(Auto_clean_Flag == true){Auto_clean_Flag = false; cout<<"AutoClean OFF"<<endl;}
			else{cout<<"could not set the Auto clean flag"<<endl;}
			break;
		case 'f':	//ManClean
			if(Man_clean_Flag == false){Man_clean_Flag = true; cout<<"ManClean ON"<<endl;}
			else if(Man_clean_Flag == true){Man_clean_Flag = false; cout<<"ManClean OFF"<<endl;}
			else{cout<<"could not set the Man clean flag"<<endl;}
			break;
		case 'g':	//Dock
			if(Dock_roomba_Flag == false){Dock_roomba_Flag = true; cout<<"Docking ON"<<endl;}
			else if(Dock_roomba_Flag == true){Dock_roomba_Flag = false; cout<<"Docking OFF"<<endl;}
			else{cout<<"could not set the dock roomba flag"<<endl;}
			break;
		default :
			return -1;
			break;}
	}

	int check_class::function_activator_volitail(char cCommand){
	switch(cCommand){
		case 'd':
			//execute function here
			cout<<"case 1"<<endl;
			break;
		case 'e':
			//execute function here
			cout<<"case 2"<<endl;
			break;
		case 'f':
			//execute function here
			cout<<"case 3"<<endl;
			break;
		case 'g':
			//execute function here
			cout<<"case 4"<<endl;
			break;
		case 'h':
			//execute function here
			cout<<"case 5"<<endl;
			break;
		case 'i':
			//execute function here
			cout<<"case 6"<<endl;
			break;
		case 'j':
			//execute function here
			cout<<"case 7"<<endl;
			break;
		case 'k':
			//execute function here
			cout<<"case 8"<<endl;
			break;
		default :
			return -1;
			break;}
	}

//        const std::string R_FIFO_FILE{"/tmp/rFIFO"}; //pipe to recieve
//	const std::string W_FIFO_FILE{"/tmp/wFIFO"}; //pipe to send

//write fifo
        void Communicate::writeFIFO(char cTosend){
                FILE *fifo;
                unsigned char message[1];

		if (cTosend = 'w'|'v'|'x'|'y'|'z'){
	                message[0] = cTosend;		
	                fifo = fopen(W_FIFO_FILE.c_str(), "w");		//printf("past open\n");
	                fwrite(&message,1, 1, fifo);		//printf("past write\n");
	                fclose(fifo);}				//printf("pipe closed\n");
		//error
		else {printf("Something weird has happend");}      
        }
//read fifo
        char Communicate::readFIFO(){
                unsigned char readbuf[1];
                char cBuff;
                FILE *fifo;

                fifo = fopen(R_FIFO_FILE.c_str(), "r");		//printf("past fopen\n");
                fread(&readbuf, 1, 1, fifo);      
                fclose(fifo);				//printf("read pipe closed\n");
		
		if(readbuf[0] == NULL){cBuff = 'k'; return cBuff;}
		else{cBuff = readbuf[0]; return cBuff;}
                

                
        }
//make read and write fifo
        void Communicate::makeFIFO()        {
                int r_status;
                int w_status;

                /* Create the reading side FIFO if it does not exist */
                umask(0666);
                r_status = mknod(R_FIFO_FILE.c_str(), S_IFIFO|0666, 0);
                if (r_status == -1 ) {cout<<"Cannot create fifo"<<endl;} else{cout<<"FIFO made"<< endl;}

		/* Create the writing side FIFO if it does not exist */
                umask(0666);
                w_status = mknod(W_FIFO_FILE.c_str(), S_IFIFO|0666, 0);
                if (w_status == -1 ) {cout<<"Cannot create fifo"<<endl;} else{cout<<"FIFO made"<<endl;}
        }

