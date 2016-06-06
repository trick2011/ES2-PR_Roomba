#include "pipe_filler.h"

pipe_filler::pipe_filler(interpreter& peter,com_class& comclass):peter{peter},comclass{comclass}{

}
void pipe_filler::operator()(){
#ifndef PIPE
	//comclass.ctp_FIFOref.c_str()
	ofstream ofp;
	while(1){
		sleep(1);
		ofp.open(comclass.ctp_FIFOref,fstream::trunc);
		if(Basicclean::getEnableCleaning())
			if(peter.Cliff.bLeft == true||peter.Cliff.bFrontLeft||peter.Cliff.bFrontRight||peter.Cliff.bRight)
				ofp << site_opcodes::Drop;
			else
				if(peter.Bumps.bLeft)
					ofp << site_opcodes::BumpLeft;
				else
					if(peter.Bumps.bRight)
						ofp << site_opcodes::BumpRight;
					else
						ofp << site_opcodes::Nothing;
		else
			if(peter.getCliffLeft()||peter.getCliffFrontLeft()||peter.getCliffFrontRight()||peter.getCliffRight())
				ofp << site_opcodes::Drop;
			else
				if(peter.getBumpLeft())
					ofp << site_opcodes::BumpLeft;
				else
					if(peter.getBumpRight())
						ofp << site_opcodes::BumpRight;
					else
						ofp << site_opcodes::Nothing;
		ofp.close();
	}
#endif
#ifdef PIPE
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	if (sigaction(SIGPIPE, &sa, 0) == -1) {
	  perror("sigaction");
	  exit(1);
	}
	while(true){
//		if(peter.sCliff.bLeft == true||peter.sCliff.bFrontLeft||peter.sCliff.bFrontRightLeft||peter.sCliff.bRight)
//			comclass.writeFIFO('x');
//		else
//			if(peter.sBumps.bLeft)
//				comclass.writeFIFO('w');
//			else
//				if(peter.sBumps.bRight)
//					comclass.writeFIFO('v');
//				else
//					comclass.writeFIFO(' ');
		comclass.writeFIFO('v');
		cout << "written" << endl;
		//sleep(1);
		chrono::time_point<chrono::system_clock> start,end;
		start = chrono::system_clock::now();
		chrono::duration<double> elapsed_seconds;
		while(true){
			end = chrono::system_clock::now();
			elapsed_seconds = end - start;
			if(elapsed_seconds.count() >= 1.5){
				break;
			}

		}
	}
#endif
}
