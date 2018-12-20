#ifndef STMTNODE_H
#define STMTNODE_H

#include "node.h"

struct StmtNode : public Node
{
    int pos; //offset in source stream
    StmtNode(): pos(-1) {}
    void debug(int pos, Codegen* g);

    virtual void semant(Environ* e) {}
    virtual void translate(Codegen* g) {}
};

struct StmtSeqNode : public Node
{
    std::string file;
    std::vector<StmtNode*> stmts;
    StmtSeqNode(const std::string& f): file(f) {}

    ~StmtSeqNode()
    {
        for (; !stmts.empty(); stmts.pop_back()) delete stmts.back();
    }

    void semant(Environ* e);
    void translate(Codegen* g);

    void push_back(StmtNode* s)
    {
        stmts.push_back(s);
    }

    int size()
    {
        return stmts.size();
    }

    static void reset(const std::string& file, const std::string& lab);
};

#include "exprnode.h"
#include "declnode.h"

struct IncludeNode : public StmtNode
{
    std::string file, label;
    StmtSeqNode* stmts;
    IncludeNode(const std::string& t, StmtSeqNode* ss): file(t), stmts(ss) {}

    ~IncludeNode()
    {
        delete stmts;
    }

    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct DeclStmtNode : public StmtNode
{
    DeclNode* decl;

    DeclStmtNode(DeclNode* d): decl(d)
    {
        pos = d->pos;
    }

    ~DeclStmtNode()
    {
        delete decl;
    }

    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct DimNode : public StmtNode
{
    std::string ident, tag;
    ExprSeqNode* exprs;
    ArrayType* sem_type;
    Decl* sem_decl;
    DimNode(const std::string& i, const std::string& t, ExprSeqNode* e): ident(i), tag(t), exprs(e) {}

    ~DimNode()
    {
        delete exprs;
    }

    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct AssNode : public StmtNode
{
    VarNode* var;
    ExprNode* expr;
    AssNode(VarNode* var, ExprNode* expr): var(var), expr(expr) {}

    ~AssNode()
    {
        delete var;
        delete expr;
    }

    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct ExprStmtNode : public StmtNode
{
    ExprNode* expr;
    ExprStmtNode(ExprNode* e): expr(e) {}

    ~ExprStmtNode()
    {
        delete expr;
    }

    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct LabelNode : public StmtNode
{
    std::string ident;
    int data_sz;
    LabelNode(const std::string& s, int sz): ident(s), data_sz(sz) {}
    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct GotoNode : public StmtNode
{
    std::string ident;
    GotoNode(const std::string& s): ident(s) {}
    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct GosubNode : public StmtNode
{
    std::string ident;
    GosubNode(const std::string& s): ident(s) {}
    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct IfNode : public StmtNode
{
    ExprNode* expr;
    StmtSeqNode *stmts, *elseOpt;
    IfNode(ExprNode* e, StmtSeqNode* s, StmtSeqNode* o): expr(e), stmts(s), elseOpt(o) {}

    ~IfNode()
    {
        delete expr;
        delete stmts;
        delete elseOpt;
    }

    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct ExitNode : public StmtNode
{
    std::string sem_brk;
    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct WhileNode : public StmtNode
{
    int wendPos;
    ExprNode* expr;
    StmtSeqNode* stmts;
    std::string sem_brk;
    WhileNode(ExprNode* e, StmtSeqNode* s, int wp): wendPos(wp), expr(e), stmts(s) {}

    ~WhileNode()
    {
        delete expr;
        delete stmts;
    }

    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct ForNode : public StmtNode
{
    int nextPos;
    VarNode* var;
    ExprNode *fromExpr, *toExpr, *stepExpr;
    StmtSeqNode* stmts;
    std::string sem_brk;
    ForNode(VarNode* v, ExprNode* f, ExprNode* t, ExprNode* s, StmtSeqNode* ss, int np);
    ~ForNode();
    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct ForEachNode : public StmtNode
{
    int nextPos;
    VarNode* var;
    std::string typeIdent;
    StmtSeqNode* stmts;
    std::string sem_brk;
    ForEachNode(VarNode* v, const std::string& t, StmtSeqNode* s, int np): nextPos(np), var(v), typeIdent(t), stmts(s) {}

    ~ForEachNode()
    {
        delete var;
        delete stmts;
    }

    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct ReturnNode : public StmtNode
{
    ExprNode* expr;
    std::string returnLabel;
    ReturnNode(ExprNode* e): expr(e) {}

    ~ReturnNode()
    {
        delete expr;
    }

    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct DeleteNode : public StmtNode
{
    ExprNode* expr;
    DeleteNode(ExprNode* e): expr(e) {}

    ~DeleteNode()
    {
        delete expr;
    }

    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct DeleteEachNode : public StmtNode
{
    std::string typeIdent;
    DeleteEachNode(const std::string& t): typeIdent(t) {}
    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct InsertNode : public StmtNode
{
    ExprNode *expr1, *expr2;
    bool before;
    InsertNode(ExprNode* e1, ExprNode* e2, bool b): expr1(e1), expr2(e2), before(b) {}

    ~InsertNode()
    {
        delete expr1;
        delete expr2;
    }

    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct CaseNode : public Node
{
    ExprSeqNode* exprs;
    StmtSeqNode* stmts;
    CaseNode(ExprSeqNode* e, StmtSeqNode* s): exprs(e), stmts(s) {}

    ~CaseNode()
    {
        delete exprs;
        delete stmts;
    }
};

struct SelectNode : public StmtNode
{
    ExprNode* expr;
    StmtSeqNode* defStmts;
    std::vector<CaseNode*> cases;
    VarNode* sem_temp;
    SelectNode(ExprNode* e): expr(e), defStmts(nullptr), sem_temp(nullptr) {}

    ~SelectNode()
    {
        delete expr;
        delete defStmts;
        delete sem_temp;
        for (; !cases.empty(); cases.pop_back()) delete cases.back();
    }

    void push_back(CaseNode* c)
    {
        cases.push_back(c);
    }

    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct RepeatNode : public StmtNode
{
    int untilPos;
    StmtSeqNode* stmts;
    ExprNode* expr;
    std::string sem_brk;
    RepeatNode(StmtSeqNode* s, ExprNode* e, int up): untilPos(up), stmts(s), expr(e) {}

    ~RepeatNode()
    {
        delete stmts;
        delete expr;
    }

    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct ReadNode : public StmtNode
{
    VarNode* var;
    ReadNode(VarNode* v): var(v) {}

    ~ReadNode()
    {
        delete var;
    }

    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

struct RestoreNode : public StmtNode
{
    std::string ident;
    Label* sem_label;
    RestoreNode(const std::string& i): ident(i) {}
    void semant(Environ* e) override;
    void translate(Codegen* g) override;
};

#endif
