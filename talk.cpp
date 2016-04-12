extern "C" 
{void makeFIFO();
char readFIFO();
void writeFIFO(char cTosend);
char RecievePipe();
void SendPipe(char cSendCommand);};


//main for testing
int main
{
	Communicate.make();
	Communicate.send('a');
return 0;
}

class Communicate
{
	Private:
		//
	Public:
		void make()
		{
			makeFIFO();
		}

		void send(char cSendCommand)
		{
			SendPipe(char cSendCommand);
		}

		char recieve()
		{
			char cRbuff;
			
			cRbuff = RecievePipe();
			return cRbuff;
		}
};

