#include "std.h"
#include "bbsys.h"
#include "bbruntime.h"

void basic_link(void (*rtSym)(std::string sym));
void math_link(void (*rtSym)(std::string sym));
void string_link(void (*rtSym)(std::string sym));
void stream_link(void (*rtSym)(std::string sym));
void sockets_link(void (*rtSym)(std::string sym));
void filesystem_link(void (*rtSym)(std::string sym));
void bank_link(void (*rtSym)(std::string sym));
void graphics_link(void (*rtSym)(std::string sym));
void input_link(void (*rtSym)(std::string sym));
void audio_link(void (*rtSym)(std::string sym));
void multiplay_link(void (*rtSym)(std::string sym));
void userlibs_link(void (*rtSym)(std::string sym));
void blitz3d_link(void (*rtSym)(std::string sym));

void bbruntime_link(void (*rtSym)(std::string sym))
{
    rtSym("End");
    rtSym("Stop");
    rtSym("AppTitle$title$close_prompt=\"\"");
    rtSym("RuntimeError$message");
    rtSym("ExecFile$command");
    rtSym("Delay%millisecs");
    rtSym("%MilliSecs");
    rtSym("$CommandLine");
    rtSym("$SystemProperty$property");
    rtSym("$GetEnv$env_var");
    rtSym("SetEnv$env_var$value");

    rtSym("%CreateTimer%hertz");
    rtSym("%WaitTimer%timer");
    rtSym("FreeTimer%timer");
    rtSym("DebugLog$text");

    rtSym("_bbDebugStmt");
    rtSym("_bbDebugEnter");
    rtSym("_bbDebugLeave");

    basic_link(rtSym);
    math_link(rtSym);
    string_link(rtSym);
    stream_link(rtSym);
    sockets_link(rtSym);
    filesystem_link(rtSym);
    bank_link(rtSym);
    graphics_link(rtSym);
    input_link(rtSym);
    audio_link(rtSym);
    multiplay_link(rtSym);
    blitz3d_link(rtSym);
    userlibs_link(rtSym);
}

//start up error
static void sue(const char* t)
{
    string p = string("Startup Error: ") + t;
    std::cout << (p.c_str()) << std::endl;
    exit(1);
}

void bbruntime_panic(const char* err)
{
    RTEX( err );
}
