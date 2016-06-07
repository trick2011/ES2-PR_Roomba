#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <sys/timeb.h>
#include <sstream>

using namespace std;

enum typelog {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class LOG{
    friend class settings;
public:
    explicit LOG(typelog type);
    ~LOG();

    template<class T>
    LOG &operator<<(const T &msg) {
        cout << msg;
        ofs << msg;
        opened = true;
        return *this;
    }

    LOG &operator<<(const uint8_t &msg);
private:
    bool opened = false;
    std::ofstream ofs;

    inline string getLabel(typelog type);
};

#endif
