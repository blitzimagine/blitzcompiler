#ifndef TYPE_H
#define TYPE_H

#include "decl.h"

struct FuncType;
struct ArrayType;
struct StructType;
struct ConstType;
struct VectorType;

struct Type
{
    virtual ~Type() {}

    virtual bool intType()
    {
        return false;
    }

    virtual bool floatType()
    {
        return false;
    }

    virtual bool stringType()
    {
        return false;
    }

    //casts to inherited types
    virtual FuncType* funcType()
    {
        return nullptr;
    }

    virtual ArrayType* arrayType()
    {
        return nullptr;
    }

    virtual StructType* structType()
    {
        return nullptr;
    }

    virtual ConstType* constType()
    {
        return nullptr;
    }

    virtual VectorType* vectorType()
    {
        return nullptr;
    }

    //operators
    virtual bool canCastTo(Type* t)
    {
        return this == t;
    }

    //built in types
    static Type *void_type, *int_type, *float_type, *string_type, *null_type;
};

struct FuncType : public Type
{
    Type* returnType;
    DeclSeq* params;
    bool userlib, cfunc;
    FuncType(Type* t, DeclSeq* p, bool ulib, bool cfn): returnType(t), params(p), userlib(ulib), cfunc(cfn) {}

    ~FuncType()
    {
        delete params;
    }

    FuncType* funcType() override
    {
        return this;
    }
};

struct ArrayType : public Type
{
    Type* elementType;
    int dims;
    ArrayType(Type* t, int n): elementType(t), dims(n) {}

    ArrayType* arrayType() override
    {
        return this;
    }
};

struct StructType : public Type
{
    string ident;
    DeclSeq* fields;
    StructType(const string& i): ident(i), fields(nullptr) {}
    StructType(const string& i, DeclSeq* f): ident(i), fields(f) {}

    ~StructType()
    {
        delete fields;
    }

    StructType* structType() override
    {
        return this;
    }

    bool canCastTo(Type* t) override;
};

struct ConstType : public Type
{
    Type* valueType;
    int intValue;
    float floatValue;
    string stringValue;
    ConstType(int n): valueType(int_type), intValue(n) {}
    ConstType(float n): valueType(float_type), floatValue(n) {}
    ConstType(const string& n): valueType(string_type), stringValue(n) {}

    ConstType* constType() override
    {
        return this;
    }
};

struct VectorType : public Type
{
    string label;
    Type* elementType;
    vector<int> sizes;
    VectorType(const string& l, Type* t, const vector<int>& szs): label(l), elementType(t), sizes(szs) {}

    VectorType* vectorType() override
    {
        return this;
    }

    bool canCastTo(Type* t) override;
};

#endif
