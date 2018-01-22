//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#include "Launcher.h"
#include "UDPNonBlockingCommunication.h"

bool rtype::Launcher::launch(std::shared_ptr<rtype::GameLobby> gl) {
    rtype::protocol_tcp::GameStart gs;
    gl->notifyAll(gs);
    auto udp = rtype::network::UDPNonBlockingCommuncation();
    udp.open(/*default port 0*/);
    std::cout << "bind on port==" << udp.getPort() << std::endl;
    gs.value = {udp.getPort()};
    return true;
}
