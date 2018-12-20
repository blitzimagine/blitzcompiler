#include "std.h"
#include "bbbank.h"
#include "bbstream.h"

void bank_link(void (*rtSym)(std::string sym))
{
    rtSym("%CreateBank%size=0");
    rtSym("FreeBank%bank");
    rtSym("%BankSize%bank");
    rtSym("ResizeBank%bank%size");
    rtSym("CopyBank%src_bank%src_offset%dest_bank%dest_offset%count");
    rtSym("%PeekByte%bank%offset");
    rtSym("%PeekShort%bank%offset");
    rtSym("%PeekInt%bank%offset");
    rtSym("#PeekFloat%bank%offset");
    rtSym("PokeByte%bank%offset%value");
    rtSym("PokeShort%bank%offset%value");
    rtSym("PokeInt%bank%offset%value");
    rtSym("PokeFloat%bank%offset#value");
    rtSym("%ReadBytes%bank%file%offset%count");
    rtSym("%WriteBytes%bank%file%offset%count");
    rtSym("%CallDLL$dll_name$func_name%in_bank=0%out_bank=0");
}
