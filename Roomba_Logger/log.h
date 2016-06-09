#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <sys/timeb.h>

using namespace std;



enum typelog {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

struct LOGsettings{
    static typelog type;
    static bool toCout;
    static std::string file;

    LOGsettings(){}
    LOGsettings(typelog newType, bool newToCout, std::string newFile);

};

class LOG{
public:
    explicit LOG(typelog type);
    ~LOG();

    template<class T>
    LOG &operator<<(const T &msg) {
        if(type >= LOGsettings::type)
        {
            if(LOGsettings::toCout)
                cout << msg;
            ofs << msg;
        }
        opened = true;
        return *this;
    }

    LOG &operator<<(const uint8_t &msg);
private:
    bool opened = false;
    std::ofstream ofs;
    typelog type = DEBUG;
    inline string getLabel(typelog type);

    inline void addTime(){
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
};

#endif
