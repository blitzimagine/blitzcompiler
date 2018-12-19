#include "std.h"
#include "bbstream.h"

void stream_link(void (*rtSym)(std::string sym))
{
    rtSym("%Eof%stream");
    rtSym("%ReadAvail%stream");
    rtSym("%ReadByte%stream");
    rtSym("%ReadShort%stream");
    rtSym("%ReadInt%stream");
    rtSym("#ReadFloat%stream");
    rtSym("$ReadString%stream");
    rtSym("$ReadLine%stream");
    rtSym("WriteByte%stream%byte");
    rtSym("WriteShort%stream%short");
    rtSym("WriteInt%stream%int");
    rtSym("WriteFloat%stream#float");
    rtSym("WriteString%stream$string");
    rtSym("WriteLine%stream$string");
    rtSym("CopyStream%src_stream%dest_stream%buffer_size=16384");
}
