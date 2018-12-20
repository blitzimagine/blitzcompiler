#pragma once

#include "../stdutil/stdutil.h"

class Debugger;

class Runtime
{
public:
    Runtime();
    virtual ~Runtime();
    virtual int version();
    virtual const char* nextSym();
    virtual int symValue(const char* sym);
    virtual void shutdown();
};

extern "C" _declspec(dllexport) Runtime* _cdecl runtimeGetRuntime();
