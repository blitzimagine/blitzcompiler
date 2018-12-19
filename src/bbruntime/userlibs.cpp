#include "std.h"
#include "userlibs.h"

void userlibs_link(void (*rtSym)(std::string sym))
{
    rtSym("_bbLoadLibs");
    rtSym("_bbStrToCStr");
    rtSym("_bbCStrToStr");
}
