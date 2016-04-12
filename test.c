#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include <linux/stat.h>

#define FIFO_FILE       "/tmp/LeFIFO"

//prototypes
void makeFIFO();
char readFIFO();
void writeFIFO(char cTosend);

//int main(void) only exists for testing purposes
int main(void)
{
        char cReadbuffer;

	makeFIFO();
        writeFIFO('s');
		printf("\n");
	cReadbuffer = readFIFO();
		printf("\n");
    	printf("Received string: %c\n", cReadbuffer);

	writeFIFO('o');
		printf("\n");
	cReadbuffer = readFIFO();
		printf("\n");
    	printf("Received string: %c\n", cReadbuffer);
		

        return(1);
}

void writeFIFO(char cTosend)
{
	FILE *fifo;
	unsigned char message[1];

	message[0] = cTosend;

	fifo = fopen(FIFO_FILE, "w");		//printf("past open\n");
	fwrite(&message,1, 1, fifo);		//printf("past write\n");
	fclose(fifo);				//printf("pipe closed\n");       
}

char readFIFO()
{
	unsigned char readbuf[1];
	char cBuff;
	FILE *fifo;

	fifo = fopen(FIFO_FILE, "r");		//printf("past fopen\n");
        fread(&readbuf, 1, 1, fifo);      
        fclose(fifo);				//printf("read pipe closed\n");
	cBuff = readbuf[0];

	return cBuff;
}

void makeFIFO()
{
	int status;
	
	/* Create the FIFO if it does not exist */
        umask(0666);
        status = mknod(FIFO_FILE, S_IFIFO|0666, 0);
	if (status == -1 ) {printf("Cannot create fifo\n");} else{printf("FIFO made \n");}
}
