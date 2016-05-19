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
#include <linux/stat.h>
#include "macros.h"
//#include "check_class.h"

using namespace std;

class com_class{
protected:
	const std::string R_FIFO_FILE = "/tmp/rFIFO"; //pipe to recieve
	const std::string W_FIFO_FILE = "/tmp/wFIFO"; //pipe to send
public:
	void writeFIFO(char cTosend);
	char readFIFO();
	void makeFIFO();
};
#endif
