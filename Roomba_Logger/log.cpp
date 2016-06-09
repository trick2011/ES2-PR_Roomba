#include "log.h"

typelog LOGsettings::type = DEBUG;
bool LOGsettings::toCout = false;
std::string LOGsettings::file = "log.txt";

LOG::LOG(typelog type):type(type)
{
    ofs.open(LOGsettings::file,std::ofstream::app);
    addTime();
    operator << ("["+getLabel(type)+"] ");
}

LOG::~LOG()
{
    if(opened) {
        if(type >= LOGsettings::type)
        {
            if(LOGsettings::toCout)
                cout << endl;
            ofs << endl;
        }
    }
    opened = false;
    ofs.close();
}


LOG &LOG::operator<<(const uint8_t &msg)
{
    if(type >= LOGsettings::type)
    {
        if(LOGsettings::toCout)
            cout << std::to_string(msg);
        ofs  << std::to_string(msg);
    }
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

void LOG::addTime(){
    timeb time;
    ftime(&time);
    int hours = ((time.time/3600)%24+2);
    if(time.dstflag) hours += 1;
    hours += (time.timezone/60);
    if(hours < 10) operator << (0);
    operator << (hours) <<":";
    int minutes = (time.time/60)%60;
    if(minutes < 10) operator << (0);
    operator << (minutes)<<":";
    int seconds = time.time%60;
    if(seconds < 10) operator << (0);
    operator << (seconds)<<".";
    int milliseconds = time.millitm;
    if(milliseconds < 100) operator << (0);
    if(milliseconds < 10) operator << (0);
    operator << (milliseconds) <<" ";
}

LOGsettings::LOGsettings(typelog newType,bool newToCout,std::string newFile)
{
    LOGsettings::file = newFile;
    LOGsettings::toCout = newToCout;
    LOGsettings::type = newType;
}
