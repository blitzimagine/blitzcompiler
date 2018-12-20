#include "../stdutil/std.h"
#include "type.h"

static struct v_type : public Type
{
    bool canCastTo(Type* t) override
    {
        return t == void_type;
    }
} v;

static struct i_type : public Type
{
    bool intType() override
    {
        return true;
    }

    bool canCastTo(Type* t) override
    {
        return t == int_type || t == float_type || t == string_type;
    }
} i;

static struct f_type : public Type
{
    bool floatType() override
    {
        return true;
    }

    bool canCastTo(Type* t) override
    {
        return t == int_type || t == float_type || t == string_type;
    }
} f;

static struct s_type : public Type
{
    bool stringType() override
    {
        return true;
    }

    bool canCastTo(Type* t) override
    {
        return t == int_type || t == float_type || t == string_type;
    }
} s;

bool StructType::canCastTo(Type* t)
{
    return t == this || t == null_type || (this == null_type && t->structType());
}

bool VectorType::canCastTo(Type* t)
{
    if (this == t) return true;
    if (VectorType* v = t->vectorType())
    {
        if (elementType != v->elementType) return false;
        if (sizes.size() != v->sizes.size()) return false;
        for (int k = 0; k < (int)sizes.size(); ++k)
        {
            if (sizes[k] != v->sizes[k]) return false;
        }
        return true;
    }
    return false;
}

static StructType n("Null");

Type* Type::void_type = &v;
Type* Type::int_type = &i;
Type* Type::float_type = &f;
Type* Type::string_type = &s;
Type* Type::null_type = &n;
