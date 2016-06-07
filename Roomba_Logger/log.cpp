#include "log.h"

typelog LOGsettings::type = DEBUG;
bool LOGsettings::toCout = false;
std::string LOGsettings::file = "log.txt";

LOG::LOG(typelog type):type(type)
{
    timeb time;
    ftime(&time);
    ofs.open(LOGsettings::file,std::ofstream::app);
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

LOGsettings::LOGsettings(typelog newType,bool newToCout,std::string newFile)
{
    LOGsettings::file = newFile;
    LOGsettings::toCout = newToCout;
    LOGsettings::type = newType;
}
