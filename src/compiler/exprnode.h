#ifndef EXPRNODE_H
#define EXPRNODE_H

#include "node.h"

struct ConstNode; //is constant int,float or string

struct ExprNode : public Node
{
    Type* sem_type;
    ExprNode(): sem_type(nullptr) {}
    ExprNode(Type* t): sem_type(t) {}

    ExprNode* castTo(Type* ty, Environ* e);
    ExprNode* semant(Environ* e, Type* ty);

    virtual ExprNode* semant(Environ* e) =0;
    virtual TNode* translate(Codegen* g) =0;

    virtual ConstNode* constNode()
    {
        return nullptr;
    }
};

struct ExprSeqNode : public Node
{
    std::vector<ExprNode*> exprs;

    ~ExprSeqNode()
    {
        for (; !exprs.empty(); exprs.pop_back()) delete exprs.back();
    }

    void push_back(ExprNode* e)
    {
        exprs.push_back(e);
    }

    int size()
    {
        return exprs.size();
    }

    void semant(Environ* e);
    TNode* translate(Codegen* g, bool userlib);
    void castTo(DeclSeq* ds, Environ* e, bool userlib);
    void castTo(Type* t, Environ* e);
};

#include "varnode.h"

struct CastNode : public ExprNode
{
    ExprNode* expr;
    Type* type;
    CastNode(ExprNode* ex, Type* ty): expr(ex), type(ty) {}

    ~CastNode()
    {
        delete expr;
    }

    ExprNode* semant(Environ* e) override;
    TNode* translate(Codegen* g) override;
};

struct CallNode : public ExprNode
{
    std::string ident, tag;
    ExprSeqNode* exprs;
    Decl* sem_decl;
    CallNode(const std::string& i, const std::string& t, ExprSeqNode* e): ident(i), tag(t), exprs(e) {}

    ~CallNode()
    {
        delete exprs;
    }

    ExprNode* semant(Environ* e) override;
    TNode* translate(Codegen* g) override;
};

struct VarExprNode : public ExprNode
{
    VarNode* var;
    VarExprNode(VarNode* v): var(v) {}

    ~VarExprNode()
    {
        delete var;
    }

    ExprNode* semant(Environ* e) override;
    TNode* translate(Codegen* g) override;
};

struct ConstNode : public ExprNode
{
    ExprNode* semant(Environ* e) override
    {
        return this;
    }

    ConstNode* constNode() override
    {
        return this;
    }

    virtual int intValue() =0;
    virtual float floatValue() =0;
    virtual std::string stringValue() =0;
};

struct IntConstNode : public ConstNode
{
    int value;
    IntConstNode(int n);
    TNode* translate(Codegen* g) override;
    int intValue() override;
    float floatValue() override;
    std::string stringValue() override;
};

struct FloatConstNode : public ConstNode
{
    float value;
    FloatConstNode(float f);
    TNode* translate(Codegen* g) override;
    int intValue() override;
    float floatValue() override;
    std::string stringValue() override;
};

struct StringConstNode : public ConstNode
{
    std::string value;
    StringConstNode(const std::string& s);
    TNode* translate(Codegen* g) override;
    int intValue() override;
    float floatValue() override;
    std::string stringValue() override;
};

struct UniExprNode : public ExprNode
{
    int op;
    ExprNode* expr;
    UniExprNode(int op, ExprNode* expr): op(op), expr(expr) {}

    ~UniExprNode()
    {
        delete expr;
    }

    ExprNode* constize();
    ExprNode* semant(Environ* e) override;
    TNode* translate(Codegen* g) override;
};

// and, or, eor, lsl, lsr, asr
struct BinExprNode : public ExprNode
{
    int op;
    ExprNode *lhs, *rhs;
    BinExprNode(int op, ExprNode* lhs, ExprNode* rhs): op(op), lhs(lhs), rhs(rhs) {}

    ~BinExprNode()
    {
        delete lhs;
        delete rhs;
    }

    ExprNode* semant(Environ* e) override;
    TNode* translate(Codegen* g) override;
};

// *,/,Mod,+,-
struct ArithExprNode : public ExprNode
{
    int op;
    ExprNode *lhs, *rhs;
    ArithExprNode(int op, ExprNode* lhs, ExprNode* rhs): op(op), lhs(lhs), rhs(rhs) {}

    ~ArithExprNode()
    {
        delete lhs;
        delete rhs;
    }

    ExprNode* semant(Environ* e) override;
    TNode* translate(Codegen* g) override;
};

//<,=,>,<=,<>,>=
struct RelExprNode : public ExprNode
{
    int op;
    ExprNode *lhs, *rhs;
    Type* opType;
    RelExprNode(int op, ExprNode* lhs, ExprNode* rhs): op(op), lhs(lhs), rhs(rhs) {}

    ~RelExprNode()
    {
        delete lhs;
        delete rhs;
    }

    ExprNode* semant(Environ* e) override;
    TNode* translate(Codegen* g) override;
};

struct NewNode : public ExprNode
{
    std::string ident;
    NewNode(const std::string& i): ident(i) {}
    ExprNode* semant(Environ* e) override;
    TNode* translate(Codegen* g) override;
};

struct FirstNode : public ExprNode
{
    std::string ident;
    FirstNode(const std::string& i): ident(i) {}
    ExprNode* semant(Environ* e) override;
    TNode* translate(Codegen* g) override;
};

struct LastNode : public ExprNode
{
    std::string ident;
    LastNode(const std::string& i): ident(i) {}
    ExprNode* semant(Environ* e) override;
    TNode* translate(Codegen* g) override;
};

struct AfterNode : public ExprNode
{
    ExprNode* expr;
    AfterNode(ExprNode* e): expr(e) {}

    ~AfterNode()
    {
        delete expr;
    }

    ExprNode* semant(Environ* e) override;
    TNode* translate(Codegen* g) override;
};

struct BeforeNode : public ExprNode
{
    ExprNode* expr;
    BeforeNode(ExprNode* e): expr(e) {}

    ~BeforeNode()
    {
        delete expr;
    }

    ExprNode* semant(Environ* e) override;
    TNode* translate(Codegen* g) override;
};

struct NullNode : public ExprNode
{
    ExprNode* semant(Environ* e) override;
    TNode* translate(Codegen* g) override;
};

struct ObjectCastNode : public ExprNode
{
    ExprNode* expr;
    std::string type_ident;
    ObjectCastNode(ExprNode* e, const std::string& t): expr(e), type_ident(t) {}

    ~ObjectCastNode()
    {
        delete expr;
    }

    ExprNode* semant(Environ* e) override;
    TNode* translate(Codegen* g) override;
};

struct ObjectHandleNode : public ExprNode
{
    ExprNode* expr;
    ObjectHandleNode(ExprNode* e): expr(e) {}

    ~ObjectHandleNode()
    {
        delete expr;
    }

    ExprNode* semant(Environ* e) override;
    TNode* translate(Codegen* g) override;
};

#endif
