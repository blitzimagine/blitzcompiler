#include "std.h"

void string_link(void (*rtSym)(std::string sym))
{
    rtSym("$String$string%repeat");
    rtSym("$Left$string%count");
    rtSym("$Right$string%count");
    rtSym("$Replace$string$from$to");
    rtSym("%Instr$string$find%from=1");
    rtSym("$Mid$string%start%count=-1");
    rtSym("$Upper$string");
    rtSym("$Lower$string");
    rtSym("$Trim$string");
    rtSym("$LSet$string%size");
    rtSym("$RSet$string%size");
    rtSym("$Chr%ascii");
    rtSym("%Asc$string");
    rtSym("%Len$string");
    rtSym("$Hex%value");
    rtSym("$Bin%value");
    rtSym("$CurrentDate");
    rtSym("$CurrentTime");
}
