#pragma warning( disable:4786 )

#include "bbruntime_dll.h"
#include <iostream>
#include <vector>

using namespace std;

#include <map>
#include <eh.h>

#include <sstream>

#include "../bbruntime/bbruntime.h"

std::map<std::string, int> global_syms;

static vector<std::string> syms;
static vector<string>::iterator sym_it;

static void rtSym(std::string sym)
{
    syms.push_back(sym);
}

int Runtime::version()
{
    return VERSION;
}

const char* Runtime::nextSym()
{
    if (syms.empty())
    {
        bbruntime_link(rtSym);
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
    trackmem(false);
    syms.clear();
}

void Runtime::checkmem(streambuf* buf)
{
    ostream out(buf);
    ::checkmem(out);
}

Runtime*_cdecl runtimeGetRuntime()
{
    static Runtime runtime;
    return &runtime;
}

/********************** BUTT UGLY DLL->EXE HOOK! *************************/

static void* module_pc;
static std::map<std::string, int> module_syms;
static std::map<std::string, int> runtime_syms;
static std::map<std::string, int> new_syms;
static Runtime* runtime;

struct Sym
{
    std::string name;
    int value;
};

static Sym getSym(void** p)
{
    Sym sym;
    char* t = (char*)*p;
    while (char c = *t++) sym.name += c;
    sym.value = *(int*)t + (int)module_pc;
    *p = t + 4;
    return sym;
}

static int findSym(const std::string& t)
{
    std::map<std::string, int>::iterator it;

    it = module_syms.find(t);
    if (it != module_syms.end()) return it->second;
    it = runtime_syms.find(t);
    if (it != runtime_syms.end()) return it->second;

    std::string err = "Can't find symbol: " + t;
    std::cout << err.c_str() << std::endl;
    return 0;
}
