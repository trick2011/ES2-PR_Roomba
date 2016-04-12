/** Macros*/
#ifndef MACROS_H_
#define MACROS_H_

//Bools
#define TRUE		1
#define FALSE		0
//signals are seen like (site->roombacontrol)
//Send
#define	MoveForward	'a'
#define MoveRearword 	'b'
#define	MoveRight	'c'
#define	MoveLeft	'd'
#define EnableAuto	'e'
#define	DisableAuto	'f'
#define	StartClean	'g'
#define StopClean	'h'
#define	DockRoomba	'i'
//Recieve
#define	BumpRight	'n'
#define	BumpLeft	'o'
#define	Drop		'p'
#define	TrashbinFull	'q'
#define BatteryLow	'r'
//FIFO
#define FIFO_FILE	"/tmp/LeFIFO"

#endif
/** End of macro list*/

/** prototypes*/
void makeFIFO();
char readFIFO();
void writeFIFO(char cTosend);
char RecievePipe();
void SendPipe(char cSendCommand);

/**************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include <linux/stat.h>

void main()
{
	char buff;	

	//makeFIFO();

	//SendPipe('n');

	buff = RecievePipe();
	printf("recieved:  %c\n", buff);

	
}


//recieve functie
char RecievePipe()
{
	//var	
	char commando, cRecievedCommand;

 	cRecievedCommand = readFIFO();
		//READ PIPE
	switch(cRecievedCommand)
	{
		case 'a':	//MoveForward
			printf("Pipe: MoveForward\n ");
			commando = MoveForward;
			break;
		case 'b':	//MoveRearword
			printf("Pipe: MoveRearward\n ");
			commando = MoveRearword;
			break;
		case 'c':	//MoveRight
			printf("Pipe: MoveRight\n ");
			commando = MoveRight;
			break;
		case 'd':	//MoveLeft
			printf("Pipe: MoveLeft\n ");
			commando = MoveLeft;
			break;
		case 'e':	//EnableAuto
			printf("Pipe: EnableAuto\n ");
			commando = EnableAuto;
			break;
		case 'f':	//DisableAuto
			printf("Pipe: DisableAuto\n ");
			commando = DisableAuto;
			break;
		case 'g':	//StartClean
			printf("Pipe: StartClean\n ");
			commando = StartClean;
			break;
		case 'h':	//StopClean
			printf("Pipe: StopClean\n ");
			commando = StopClean;
			break;
		case 'i':	//DockRoomba
			printf("Pipe: DockRoomba\n ");
			commando = DockRoomba;
			break;
		default:
			printf("Something weird has happend, this is the default");
	}
return cRecievedCommand;	
}

//send functie
void SendPipe(char cSendCommand)
{ 
	if (cSendCommand = 'n'|'o'|'p'|'q'|'r'){writeFIFO(cSendCommand);}
	else {printf("Something weird has happend");}	
}

void writeFIFO(char cTosend)
{
	FILE *fifo;
	unsigned char message[1];

	message[0] = cTosend;

	fifo = fopen(FIFO_FILE, "w");		printf("past open\n");
	fwrite(&message,1, 1, fifo);		printf("past write\n");
	fclose(fifo);				printf("pipe closed\n");       
}

char readFIFO()
{
	unsigned char readbuf[1];
	char cBuff;
	FILE *fifo;

	fifo = fopen(FIFO_FILE, "r");		printf("past fopen\n");
        fread(&readbuf, 1, 1, fifo);      
        fclose(fifo);				printf("read pipe closed\n");
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
