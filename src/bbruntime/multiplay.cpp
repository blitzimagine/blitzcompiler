#include "std.h"
#include "multiplay.h"

void multiplay_link(void (*rtSym)(std::string sym))
{
    rtSym("%StartNetGame");
    rtSym("%HostNetGame$game_name");
    rtSym("%JoinNetGame$game_name$ip_address");
    rtSym("StopNetGame");

    rtSym("%CreateNetPlayer$name");
    rtSym("DeleteNetPlayer%player");
    rtSym("$NetPlayerName%player");
    rtSym("%NetPlayerLocal%player");

    rtSym("%SendNetMsg%type$msg%from_player%to_player=0%reliable=1");

    rtSym("%RecvNetMsg");
    rtSym("%NetMsgType");
    rtSym("%NetMsgFrom");
    rtSym("%NetMsgTo");
    rtSym("$NetMsgData");
}
