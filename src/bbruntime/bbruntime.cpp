#include "../stdutil/std.h"
#include "bbruntime.h"
#include "symbols.h"

std::map<std::string, int> global_syms;

static std::vector<std::string> syms;
static std::vector<std::string>::iterator sym_it;

static void rtSym(const std::string& sym)
{
    syms.push_back(sym);
}

Runtime::Runtime() = default;
Runtime::~Runtime() = default;

int Runtime::version()
{
    return VERSION;
}

const char* Runtime::nextSym()
{
    if (syms.empty())
    {
        linkSymbols(rtSym);
        sym_it = syms.begin();
    }
    if (sym_it == syms.end())
    {
        //syms.clear();
        return nullptr;
    }
    return (sym_it++)->c_str();
}

int Runtime::symValue(const char* sym)
{
    return -1;
}

void Runtime::shutdown()
{
    syms.clear();
}

Runtime*_cdecl runtimeGetRuntime()
{
    static Runtime runtime;
    return &runtime;
}
