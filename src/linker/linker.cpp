#include "../stdutil/std.h"
#include "linker.h"

class BBModule : public Module
{
public:
    BBModule();
    BBModule(std::istream& in);
    ~BBModule();

    int getPC() override;

    void emit(int byte) override;
    void emitw(int word) override;
    void emitd(int dword) override;
    void emitx(void* mem, int sz) override;
    bool addSymbol(const char* sym, int pc) override;
    bool addReloc(const char* dest_sym, int pc, bool pcrel) override;

    bool findSymbol(const char* sym, int* pc) override;

private:
    char* data;
    int data_sz, pc;

    std::map<std::string, int> symbols;
    std::map<int, std::string> rel_relocs, abs_relocs;

    bool findSym(const std::string& t, Module* libs, int* n)
    {
        if (findSymbol(t.c_str(), n)) return true;
        if (libs->findSymbol(t.c_str(), n)) return true;
        std::string err = "Symbol '" + t + "' not found";
        std::cerr << "Blitz Linker Error" << err << std::endl;
        return false;
    }

    void ensure(int n)
    {
        if (pc + n <= data_sz) return;
        data_sz = data_sz / 2 + data_sz;
        if (data_sz < pc + n) data_sz = pc + n;
        char* old_data = data;
        data = d_new char[data_sz];
        memcpy(data, old_data, pc);
        delete old_data;
    }
};

BBModule::BBModule(): data(nullptr), data_sz(0), pc(0) {}

BBModule::~BBModule()
{
    delete[] data;
}

int BBModule::getPC()
{
    return pc;
}

void BBModule::emit(int byte)
{
    ensure(1);
    data[pc++] = byte;
}

void BBModule::emitw(int word)
{
    ensure(2);
    *(short*)(data + pc) = word;
    pc += 2;
}

void BBModule::emitd(int dword)
{
    ensure(4);
    *(int*)(data + pc) = dword;
    pc += 4;
}

void BBModule::emitx(void* mem, int sz)
{
    ensure(sz);
    memcpy(data + pc, mem, sz);
    pc += sz;
}

bool BBModule::addSymbol(const char* sym, int pc)
{
    std::string t(sym);
    if (symbols.find(t) != symbols.end()) return false;
    symbols[t] = pc;
    return true;
}

bool BBModule::addReloc(const char* dest_sym, int pc, bool pcrel)
{
    std::map<int, std::string>& rel = pcrel ? rel_relocs : abs_relocs;
    if (rel.find(pc) != rel.end()) return false;
    rel[pc] = std::string(dest_sym);
    return true;
}

bool BBModule::findSymbol(const char* sym, int* pc)
{
    std::string t = std::string(sym);
    std::map<std::string, int>::iterator it = symbols.find(t);
    if (it == symbols.end()) return false;
    *pc = it->second + (int)data;
    return true;
}

int Linker::version()
{
    return VERSION;
}

Module* Linker::createModule()
{
    return d_new BBModule();
}

void Linker::deleteModule(Module* mod)
{
    delete mod;
}

Linker*_cdecl linkerGetLinker()
{
    static Linker linker;
    return &linker;
}
