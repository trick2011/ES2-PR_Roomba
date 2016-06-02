#ifndef com_class_h
#define com_class_h

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#ifdef __linux
#include <linux/stat.h>
#endif

#include "macros.h"
//#include "check_class.h"

using namespace std;

class com_class{
protected:
	const int pipeempty = 0;
    const std::string ptc_FIFO_FILE = "/tmp/ptcFIFO"; //pipe to recieve r
    const std::string ctp_FIFO_FILE = "/tmp/ctpFIFO"; //pipe to send w

    FILE *ptcFIFO;
    FILE *ctpFIFO;
public:
	com_class();
    ~com_class();

	void writeFIFO(char cTosend);
	char readFIFO();
	void makeFIFO();
};
#endif
