#include "libs.h"

#include <Windows.h>
#include "../bbruntime/bbruntime_dll.h"

int bcc_ver;
int lnk_ver;
int run_ver;
int dbg_ver;

Linker* linkerLib;
Runtime* runtimeLib;

Module* runtimeModule;
Environ* runtimeEnviron;
vector<string> keyWords;
vector<UserFunc> userFuncs;

static Type* typeof(int c)
{
    switch (c)
    {
    case '%': return Type::int_type;
    case '#': return Type::float_type;
    case '$': return Type::string_type;
    }
    return Type::void_type;
}

static int curr;
static string text;

static int bnext(istream& in)
{
    text = "";

    int t = 0;

    for (;;)
    {
        while (isspace(in.peek())) in.get();
        if (in.eof()) return curr = 0;
        t = in.get();
        if (t != ';') break;
        while (!in.eof() && in.get() != '\n') {}
    }

    if (isalpha(t))
    {
        text += (char)t;
        while (isalnum(in.peek()) || in.peek() == '_') text += (char)in.get();
        return curr = -1;
    }
    if (t == '\"')
    {
        while (in.peek() != '\"') text = text + (char)in.get();
        in.get();
        return curr = -2;
    }

    return curr = t;
}

static const char* linkRuntime()
{
    while (const char* sym = runtimeLib->nextSym())
    {
        string s(sym);

        int pc = runtimeLib->symValue(sym);

        //internal?
        if (s[0] == '_')
        {
            runtimeModule->addSymbol(("_" + s).c_str(), pc);
            continue;
        }

        bool cfunc = false;

        if (s[0] == '!')
        {
            cfunc = true;
            s = s.substr(1);
        }

        keyWords.push_back(s);

        //global!
        int start = 0, end;
        Type* t = Type::void_type;
        if (!isalpha(s[0]))
        {
            start = 1;
            t = typeof(s[0]);
        }
        int k;
        for (k = 1; k < (int)s.size(); ++k)
        {
            if (!isalnum(s[k]) && s[k] != '_') break;
        }
        end = k;
        DeclSeq* params = d_new DeclSeq();
        string n = s.substr(start, end - start);
        while (k < (int)s.size())
        {
            Type* t = typeof(s[k++]);
            int from = k;
            for (; isalnum(s[k]) || s[k] == '_'; ++k) {}
            string str = s.substr(from, k - from);
            ConstType* defType = nullptr;
            if (s[k] == '=')
            {
                int from = ++k;
                if (s[k] == '\"')
                {
                    for (++k; s[k] != '\"'; ++k) {}
                    string t = s.substr(from + 1, k - from - 1);
                    defType = d_new ConstType(t);
                    ++k;
                }
                else
                {
                    if (s[k] == '-') ++k;
                    for (; isdigit(s[k]); ++k) {}
                    if (t == Type::int_type)
                    {
                        int n = atoi(s.substr(from, k - from));
                        defType = d_new ConstType(n);
                    }
                    else
                    {
                        float n = (float)atof(s.substr(from, k - from));
                        defType = d_new ConstType(n);
                    }
                }
            }
            Decl* d = params->insertDecl(str, t, DECL_PARAM, defType);
        }

        FuncType* f = d_new FuncType(t, params, false, cfunc);
        n = tolower(n);
        runtimeEnviron->funcDecls->insertDecl(n, f, DECL_FUNC);
        runtimeModule->addSymbol(("_f" + n).c_str(), pc);
    }
    return nullptr;
}

static set<string> _ulibkws;

static const char* loadUserLib(const string& userlib)
{
    string t = "userlibs/" + userlib;

    string lib = "";
    ifstream in(t.c_str());

    bnext(in);
    while (curr)
    {
        if (curr == '.')
        {
            if (bnext(in) != -1) return "expecting identifier after '.'";

            if (text == "lib")
            {
                if (bnext(in) != -2) return "expecting string after lib directive";
                lib = text;
            }
            else
            {
                return "unknown decl directive";
            }
            bnext(in);
        }
        else if (curr == -1)
        {
            if (!lib.size()) return "function decl without lib directive";

            string id = text;
            string lower_id = tolower(id);

            if (_ulibkws.count(lower_id)) return "duplicate identifier";
            _ulibkws.insert(lower_id);

            Type* ty = nullptr;
            switch (bnext(in))
            {
            case '%': ty = Type::int_type;
                break;
            case '#': ty = Type::float_type;
                break;
            case '$': ty = Type::string_type;
                break;
            }
            if (ty) bnext(in);
            else ty = Type::void_type;

            DeclSeq* params = d_new DeclSeq();

            if (curr != '(') return "expecting '(' after function identifier";
            bnext(in);
            if (curr != ')')
            {
                for (;;)
                {
                    if (curr != -1) break;
                    string arg = text;

                    Type* ty = nullptr;
                    switch (bnext(in))
                    {
                    case '%': ty = Type::int_type;
                        break;
                    case '#': ty = Type::float_type;
                        break;
                    case '$': ty = Type::string_type;
                        break;
                    case '*': ty = Type::null_type;
                        break;
                    }
                    if (ty) bnext(in);
                    else ty = Type::int_type;

                    ConstType* defType = nullptr;

                    Decl* d = params->insertDecl(arg, ty, DECL_PARAM, defType);

                    if (curr != ',') break;
                    bnext(in);
                }
            }
            if (curr != ')') return "expecting ')' after function decl";

            keyWords.push_back(id);

            FuncType* fn = d_new FuncType(ty, params, true, true);

            runtimeEnviron->funcDecls->insertDecl(lower_id, fn, DECL_FUNC);

            if (bnext(in) == ':')
            {
                //real name?
                bnext(in);
                if (curr != -1 && curr != -2) return "expecting identifier or string after alias";
                id = text;
                bnext(in);
            }

            userFuncs.push_back(UserFunc(lower_id, id, lib));
        }
    }
    return nullptr;
}

static const char* linkUserLibs()
{
    _ulibkws.clear();

    WIN32_FIND_DATA fd;

    HANDLE h = FindFirstFile("userlibs/*.decls", &fd);

    if (h == INVALID_HANDLE_VALUE) return nullptr;

    const char* err = nullptr;

    do
    {
        if (err = loadUserLib(fd.cFileName))
        {
            static char buf[64];
            sprintf_s(buf, "Error in userlib '%s' - %s", fd.cFileName, err);
            err = buf;
            break;
        }
    }
    while (FindNextFile(h, &fd));

    FindClose(h);

    _ulibkws.clear();

    return err;
}

const char* openLibs()
{
    linkerLib = linkerGetLinker();
    runtimeLib = runtimeGetRuntime();

    bcc_ver = VERSION;
    lnk_ver = linkerLib->version();
    run_ver = runtimeLib->version();

    if ((lnk_ver >> 16) != (bcc_ver >> 16) ||
        (run_ver >> 16) != (bcc_ver >> 16) ||
        (lnk_ver >> 16) != (bcc_ver >> 16))
        return "Library version error";


    runtimeModule = linkerLib->createModule();
    runtimeEnviron = d_new Environ("", Type::int_type, 0, nullptr);

    keyWords.clear();
    userFuncs.clear();

    return nullptr;
}

const char* linkLibs()
{
    if (const char* p = linkRuntime()) return p;

    if (const char* p = linkUserLibs()) return p;

    return nullptr;
}

void closeLibs()
{
    delete runtimeEnviron;
    if (linkerLib) linkerLib->deleteModule(runtimeModule);
    if (runtimeLib) runtimeLib->shutdown();

    runtimeEnviron = nullptr;
    linkerLib = nullptr;
}
