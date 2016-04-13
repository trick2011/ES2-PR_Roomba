#include <iostream>
#include <string>


#include <sys/stat.h>
#include <unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include <linux/stat.h>


// extern "C"{
// void makeFIFO();
// char readFIFO();
// void writeFIFO(char cTosend);
// char RecievePipe();
// void SendPipe(char cSendCommand);
// };


class Communicate{
private:
        const std::string FIFO_FILE{"/tmp/LeFIFO"};
public:
        void writeFIFO(char cTosend){
                FILE *fifo;
                unsigned char message[1];

                message[0] = cTosend;

                fifo = fopen(FIFO_FILE.c_str(), "w");		//printf("past open\n");
                fwrite(&message,1, 1, fifo);		//printf("past write\n");
                fclose(fifo);				//printf("pipe closed\n");       
        }

        char readFIFO(){
                unsigned char readbuf[1];
                char cBuff;
                FILE *fifo;

                fifo = fopen(FIFO_FILE.c_str(), "r");		//printf("past fopen\n");
                fread(&readbuf, 1, 1, fifo);      
                fclose(fifo);				//printf("read pipe closed\n");
                cBuff = readbuf[0];

                return cBuff;
        }

        void makeFIFO()        {
                int status;
                
                /* Create the FIFO if it does not exist */
                umask(0666);
                status = mknod(FIFO_FILE.c_str(), S_IFIFO|0666, 0);
                if (status == -1 ) {printf("Cannot create fifo\n");} else{printf("FIFO made \n");}
        }

};



//main for testing
int main(){
        Communicate comobject;
	comobject.makeFIFO();
        comobject.writeFIFO('a');
        //comobject.make();
	//comobject.send('a');
        return(0);
}
