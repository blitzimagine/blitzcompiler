#pragma warning(disable:4786)

#include <iostream>

#include "config/config.h"
#include "stdutil/stdutil.h"

#include <map>
#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "blitz/libs.h"

using namespace std;

#include "linker/linker.h"
#include "compiler/environ.h"
#include "compiler/parser.h"
#include "compiler/codegen_x86/codegen_x86.h"

static void showInfo()
{
    const int major = (VERSION & 0xffff) / 100, minor = (VERSION & 0xffff) % 100;
    cout << "BlitzCC V" << major << "." << minor << endl;
    cout << "(C)opyright 2000-2003 Blitz Research Ltd" << endl;
}

static void showUsage()
{
    cout << "Usage: bbc [-h|-q|+q|-c|-d|-k|+k|-v] [sourcefile.bb] [outputfile.asm]" << endl;
}

static void showHelp()
{
    showUsage();
    cout << "-h         : show this help" << endl;
    cout << "-q         : quiet mode" << endl;
    cout << "+q         : very quiet mode" << endl;
    cout << "-d         : debug compile" << endl;
    cout << "-k         : dump keywords" << endl;
    cout << "+k         : dump keywords and syntax" << endl;
    cout << "-v         : version info" << endl;
}

static void err(const string& t)
{
    cerr << t << endl;
    exit(-1);
}

static void out(const string& t)
{
    cout << t << endl;
}

static void usageError()
{
    showUsage();
    exit(-1);
}

static string quickHelp(const string& kw)
{
    Environ* e = runtimeEnviron;
    Decl* d = e->funcDecls->findDecl(tolower(kw));
    if (!d || d->type->funcType() == nullptr) return "No quick help available for " + kw;
    string t = kw;
    FuncType* f = d->type->funcType();
    if (f->returnType == Type::float_type) t += '#';
    else if (f->returnType == Type::string_type) t += '$';

    t += " ";

    if (f->returnType != Type::void_type) t += "( ";

    for (int k = 0; k < f->params->size(); ++k)
    {
        string s;
        if (k) s += ',';
        Decl* p = f->params->decls[k];
        s += p->name;
        if (p->type == Type::float_type) s += '#';
        else if (p->type == Type::string_type) s += '$';
        else if (p->type == Type::void_type) s += '*';
        if (p->defType) s = '[' + s + ']';
        t += s;
    }

    if (f->returnType != Type::void_type)
    {
        t += f->params->size() ? " )" : ")";
    }
    return t;
}

static void dumpKeys(bool lang, bool mod, bool help)
{
    if (lang)
    {
        map<string, int>::iterator it;
        map<string, int>& keywords = Toker::getKeywords();
        for (it = keywords.begin(); it != keywords.end(); ++it)
        {
            if (it->first.find(' ') != string::npos) continue;
            cout << it->first << endl;
        }
    }

    if (!mod) return;

    for (int k = 0; k < (int)keyWords.size(); ++k)
    {
        string t = keyWords[k];

        if (t[0] == '_') continue;
        if (!isalpha(t[0])) t = t.substr(1);
        for (int n = 0; n < (int)t.size(); ++n)
        {
            if (!isalnum(t[n]) && t[n] != '_')
            {
                t = t.substr(0, n);
                break;
            }
        }
        if (help) t = quickHelp(t);
        cout << t << endl;
    }
}

static string verstr(int ver)
{
    return itoa((ver & 65535) / 100) + "." + itoa((ver & 65535) % 100);
}

static void versInfo()
{
    cout << "Compiler version:" << verstr(bcc_ver) << endl;
    cout << "Runtime version:" << verstr(run_ver) << endl;
    cout << "Debugger version:" << verstr(dbg_ver) << endl;
    cout << "Linker version:" << verstr(lnk_ver) << endl;
}

int _cdecl main(int argc, char* argv[])
{
    if (argc == 1)
        usageError();

    string in_file, out_file, args;

    bool debug = false, quiet = false, veryquiet = false;
    bool dumpkeys = false, dumphelp = false, showhelp = false;
    bool versinfo = false;

    for (int k = 1; k < argc; ++k)
    {
        string t = argv[k];

        t = tolower(t);

        if (t == "-h")
        {
            showhelp = true;
        } else if (t == "-q")
        {
            quiet = true;
        } else if (t == "+q")
        {
            quiet = veryquiet = true;
        } else if (t == "-d")
        {
            debug = true;
        } else if (t == "-k")
        {
            dumpkeys = true;
        } else if (t == "+k")
        {
            dumpkeys = dumphelp = true;
        } else if (t == "-v")
        {
            versinfo = true;
        } else
        {
            if ((!in_file.empty() && !out_file.empty()) || t[0] == '-' || t[0] == '+')
                usageError();
            if (in_file.empty())
            {
                in_file = argv[k];
                if (!args.empty())
                    args += ' ';
                args += in_file;
            } else if (out_file.empty())
            {
                out_file = argv[k];
                if (!args.empty())
                    args += ' ';
                args += out_file;
            }
        }
    }

    if (const char* er = openLibs())
        err(er);

    if (const char* er = linkLibs())
        err(er);

    if (showhelp) showHelp();
    if (dumpkeys) dumpKeys(true, true, dumphelp);
    if (versinfo) versInfo();

    if (in_file.empty())
        return 0;

    if (in_file[0] == '\"')
    {
        if (in_file.size() < 3 || in_file[in_file.size() - 1] != '\"') usageError();
        in_file = in_file.substr(1, in_file.size() - 2);
    }

    if (out_file.empty())
    {
        bool foundExtension = false;
        for (int i = in_file.length() - 1; i >= 0; i--)
        {
            char c = in_file[i];
            if (c == '.')
            {
                foundExtension = true;
                continue;
            }

            if (foundExtension)
            {
                out_file.push_back(c);
            }
        }
        if (foundExtension)
            reverse(out_file.begin(), out_file.end());

        if (out_file.empty())
            out_file = in_file;

        out_file += ".asm";
    }

    ifstream in(in_file.c_str());
    if (!in) err("Unable to open input file");
    if (!quiet)
    {
        showInfo();
        cout << "Compiling \"" << in_file << "\"" << endl;
    }

    int n = in_file.rfind('/');
    if (n == string::npos) n = in_file.rfind('\\');
    if (n != string::npos)
    {
        if (!n || in_file[n - 1] == ':')
            ++n;

        setCurrentDirectory(in_file.substr(0, n));
    }

    ProgNode* prog = nullptr;
    Environ* environ_ = nullptr;
    Module* module = nullptr;

    try
    {
        //parse
        if (!veryquiet) cout << "Parsing..." << endl;
        Toker toker(in);
        Parser parser(toker);
        prog = parser.parse(in_file);

        //semant
        if (!veryquiet) cout << "Generating..." << endl;
        environ_ = prog->semant(runtimeEnviron);

        //translate
        if (!veryquiet) cout << "Translating..." << endl;
        qstreambuf qbuf;
        iostream asmcode(&qbuf);
        Codegen_x86 codegen(asmcode, debug);

        prog->translate(&codegen, userFuncs);

        std::string asmCodeStr(qbuf.data(), qbuf.size());
        if (out_file.empty())
        {
            cout << endl << asmCodeStr << endl;
        } else
        {
            std::ofstream out(out_file, std::ios::out);
            if (out.fail())
            {
                err("Failed to open '" + out_file + "' for writing");
            } else
            {
                out.write(asmCodeStr.c_str(), asmCodeStr.length());
            }
            out.flush();
            out.close();
        }
    } catch (Ex& x)
    {
        string file = '\"' + x.file + '\"';
        int row = ((x.pos >> 16) & 65535) + 1, col = (x.pos & 65535) + 1;
        cout << file << ":" << row << ":" << col << ":" << row << ":" << col << ":" << x.ex << endl;
        exit(-1);
    }

    delete prog;

    delete module;
    delete environ_;

    closeLibs();

    return 0;
}
