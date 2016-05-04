//c++ includes
#include <iostream>
#include <string>

//c includes
#include <sys/stat.h>
#include <unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
//#include<string.h>

#ifdef __linux
#include <linux/stat.h>
#endif

class pipehandler{
private:
    const std::string FIFO_FILE{"/tmp/LeFIFO"};
    FILE *fifo;
public:
    bool makeFIFO();
    bool openfifo(void);
    void writeFIFO(char cTosend);
    char readFIFO();

    //void operator()(){/*actie*/();}
};
