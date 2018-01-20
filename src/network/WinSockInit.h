#ifndef WINSOCK_INIT_H_
#define WINSOCK_INIT_H_

#if defined (_WIN32) || defined (_WIN64)

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")

namespace lw_network {
class WinSockInit {
public:
	WinSockInit();
	~WinSockInit();
};
extern const WinSockInit wsaInit;
}
#endif //defined (_WIN32) || defined (_WIN64)

#endif //WINSOCK_INIT_H_