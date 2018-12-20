#include "../stdutil/std.h"
#include "environ.h"

Environ::Environ(const std::string& f, Type* r, int l, Environ* gs)
    : level(l), globals(gs), returnType(r), funcLabel(f)
{
    decls = d_new DeclSeq();
    typeDecls = d_new DeclSeq();
    funcDecls = d_new DeclSeq();
    if (globals) globals->children.push_back(this);
}

Environ::~Environ()
{
    if (globals) globals->children.remove(this);
    while (!children.empty()) delete children.back();
    for (; !labels.empty(); labels.pop_back()) delete labels.back();

    //delete all types
    delete decls;
    delete funcDecls;
    delete typeDecls;

    for (int k = 0; k < (int)types.size(); ++k) delete types[k];
}

Decl* Environ::findDecl(const std::string& s)
{
    for (Environ* e = this; e; e = e->globals)
    {
        if (Decl* d = e->decls->findDecl(s))
        {
            if (d->kind & (DECL_LOCAL | DECL_PARAM))
            {
                if (e == this) return d;
            } else return d;
        }
    }
    return nullptr;
}

Decl* Environ::findFunc(const std::string& s)
{
    for (Environ* e = this; e; e = e->globals)
    {
        if (Decl* d = e->funcDecls->findDecl(s)) return d;
    }
    return nullptr;
}

Type* Environ::findType(const std::string& s)
{
    if (s == "%") return Type::int_type;
    if (s == "#") return Type::float_type;
    if (s == "$") return Type::string_type;
    for (Environ* e = this; e; e = e->globals)
    {
        if (Decl* d = e->typeDecls->findDecl(s)) return d->type->structType();
    }
    return nullptr;
}

Label* Environ::findLabel(const std::string& s)
{
    for (int k = 0; k < (int)labels.size(); ++k) if (labels[k]->name == s) return labels[k];
    return nullptr;
}

Label* Environ::insertLabel(const std::string& s, int def, int src, int sz)
{
    Label* l = d_new Label(s, def, src, sz);
    labels.push_back(l);
    return l;
}

std::string Environ::setBreak(const std::string& s)
{
    std::string t = breakLabel;
    breakLabel = s;
    return t;
}
