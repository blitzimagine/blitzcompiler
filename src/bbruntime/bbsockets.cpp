#include "std.h"
#include "bbsockets.h"

void sockets_link(void (*rtSym)(std::string sym))
{
    rtSym("$DottedIP%IP");
    rtSym("%CountHostIPs$host_name");
    rtSym("%HostIP%host_index");

    rtSym("%CreateUDPStream%port=0");
    rtSym("CloseUDPStream%udp_stream");
    rtSym("SendUDPMsg%udp_stream%dest_ip%dest_port=0");
    rtSym("%RecvUDPMsg%udp_stream");
    rtSym("%UDPStreamIP%udp_stream");
    rtSym("%UDPStreamPort%udp_stream");
    rtSym("%UDPMsgIP%udp_stream");
    rtSym("%UDPMsgPort%udp_stream");
    rtSym("UDPTimeouts%recv_timeout");

    rtSym("%OpenTCPStream$server%server_port%local_port=0");
    rtSym("CloseTCPStream%tcp_stream");
    rtSym("%CreateTCPServer%port");
    rtSym("CloseTCPServer%tcp_server");
    rtSym("%AcceptTCPStream%tcp_server");
    rtSym("%TCPStreamIP%tcp_stream");
    rtSym("%TCPStreamPort%tcp_stream");
    rtSym("TCPTimeouts%read_millis%accept_millis");
}
