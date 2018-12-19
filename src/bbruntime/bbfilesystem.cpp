#include "std.h"
#include "bbfilesystem.h"

void filesystem_link(void (*rtSym)(std::string sym))
{
    rtSym("%OpenFile$filename");
    rtSym("%ReadFile$filename");
    rtSym("%WriteFile$filename");
    rtSym("CloseFile%file_stream");
    rtSym("%FilePos%file_stream");
    rtSym("%SeekFile%file_stream%pos");

    rtSym("%ReadDir$dirname");
    rtSym("CloseDir%dir");
    rtSym("$NextFile%dir");
    rtSym("$CurrentDir");
    rtSym("ChangeDir$dir");
    rtSym("CreateDir$dir");
    rtSym("DeleteDir$dir");

    rtSym("%FileSize$file");
    rtSym("%FileType$file");
    rtSym("CopyFile$file$to");
    rtSym("DeleteFile$file");
}
