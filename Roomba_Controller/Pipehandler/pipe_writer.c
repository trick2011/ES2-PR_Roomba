//test
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

# define	R_FIFO_FILE "/tmp/rFIFO"

int main()
{
	FILE *fifo;
        unsigned char message[1];
	
	while(1){
	for(int i =0; i <= 4; i++)
	{
	        message[0] = 'c';		
        	fifo = fopen(R_FIFO_FILE, "w");		
        	fwrite(&message,1, 1, fifo);		
        	fclose(fifo);
		sleep(1);
		printf("send\n");
	}
	for(int i =0; i <= 4; i++)
	{
		message[0] = 'b';		
        	fifo = fopen(R_FIFO_FILE, "w");		
        	fwrite(&message,1, 1, fifo);		
        	fclose(fifo);
		sleep(1);
		printf("send\n");
	}
	}

return 0;
}

