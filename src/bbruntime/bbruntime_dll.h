/* Win32 runtime dynamic link lib */

#ifndef BBRUNTIME_DLL_H
#define BBRUNTIME_DLL_H

#include "../stdutil/stdutil.h"

class Debugger;

class Runtime
{
public:
    virtual int version();
    virtual const char* nextSym();
    virtual int symValue(const char *sym);
    virtual void shutdown();
    virtual void checkmem(std::streambuf* buf);
};

extern "C" _declspec(dllexport) Runtime* _cdecl runtimeGetRuntime();

#endif
