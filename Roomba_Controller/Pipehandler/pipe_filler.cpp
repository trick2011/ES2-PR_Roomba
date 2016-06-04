#include "pipe_filler.h"

pipe_filler::pipe_filler(interpreter& peter,com_class& comclass):peter{peter},comclass{comclass}{

}
void pipe_filler::operator()(){
	while(true){
		if(peter.sCliff.bLeft||peter.sCliff.bFrontLeft||peter.sCliff.bFrontRightLeft||peter.sCliff.bRight)
			comclass.writeFIFO('x');
		else
			if(peter.sBumps.bLeft)
				comclass.writeFIFO('w');
			else
				if(peter.sBumps.bRight)
					comclass.writeFIFO('v');
				else
					comclass.writeFIFO(' ');
		sleep(1);
	}
}
