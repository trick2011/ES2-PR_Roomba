#ifndef com_class_h
#define com_class_h

#include <string>
class Communicate{
private:
        const std::string R_FIFO_FILE{"/tmp/rFIFO"}; //pipe to recieve
	const std::string W_FIFO_FILE{"/tmp/wFIFO"}; //pipe to send
public:

        void writeFIFO(char cTosend);
        char readFIFO();
        void makeFIFO();
};
#endif
