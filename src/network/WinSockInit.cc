//
// Created by Kévin POLOSSAT on 20/01/2018.
//

#include "WinSockInit.h"

#if defined (_WIN32) || defined (_WIN64)
const static lw_network::WinSockInit wsaInit = lw_network::WinSockInit();
lw_network::WinSockInit::WinSockInit() {
	WSAData wsadata;
	auto a = ::WSAStartup(MAKEWORD(2, 2), &wsadata);
}

lw_network::WinSockInit::~WinSockInit() {
	WSACleanup();
}

#endif //defined (_WIN32) || defined (_WIN64)


