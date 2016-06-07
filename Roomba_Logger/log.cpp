#include "log.h"



LOG::LOG(typelog type)
{
    timeb time;
    ftime(&time);
    ofs.open("log.txt",std::ofstream::app);
    operator << ((time.time/3600)%24+2)<<":" //hours
             << (time.time/60)%60 << ":"     //minutes
             << time.time%60 << "."          //seconds
             << time.millitm                 //milliseconds
             << " ";
    operator << ("["+getLabel(type)+"] ");
}

LOG::~LOG()
{
    if(opened) {
        cout << endl;
        ofs << endl;
    }
    opened = false;
    ofs.close();
}


LOG &LOG::operator<<(const uint8_t &msg)
{
    cout << std::to_string(msg);
    ofs  << std::to_string(msg);
    opened = true;
    return *this;
}

string LOG::getLabel(typelog type)
{
    string label;
    switch(type) {
        case DEBUG: label = "DEBUG"; break;
        case INFO:  label = "INFO "; break;
        case WARN:  label = "WARN "; break;
        case ERROR: label = "ERROR"; break;
        default   : label = "DEBUG"; break;
    }
    return label;
}
