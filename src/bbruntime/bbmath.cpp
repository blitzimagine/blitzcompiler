#include "std.h"
#include "bbmath.h"

void math_link(void (*rtSym)(std::string sym))
{
    rtSym("#Sin#degrees");
    rtSym("#Cos#degrees");
    rtSym("#Tan#degrees");
    rtSym("#ASin#float");
    rtSym("#ACos#float");
    rtSym("#ATan#float");
    rtSym("#ATan2#floata#floatb");
    rtSym("#Sqr#float");
    rtSym("#Floor#float");
    rtSym("#Ceil#float");
    rtSym("#Exp#float");
    rtSym("#Log#float");
    rtSym("#Log10#float");
    rtSym("#Rnd#from#to=0");
    rtSym("%Rand%from%to=1");
    rtSym("SeedRnd%seed");
    rtSym("%RndSeed");
}
