#ifndef BBSYS_H
#define BBSYS_H

#include "basic.h"

inline void debugError(const char* e)
{
    std::cerr << "Error: " << e << std::endl;
    exit(1);
}

struct bbEx : std::exception
{
    const char* err;

    bbEx(const char* e): err(e)
    {
        if (e) debugError(e);
    }
};

#define RTEX( _X_ ) throw bbEx( _X_ );

#endif
