//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#include "Launcher.h"
#include "UDPNonBlockingCommunication.h"

bool rtype::Launcher::launch(std::shared_ptr<rtype::GameLobby> gl) {
    rtype::protocol_tcp::GameStart gs;
    auto udp = ge::network::UDPNonBlockingCommuncation();
    udp.open(/*default port 0*/);
    gs.value = {udp.getPort()};
    for (auto const & p : gl->getEndPoints()) {
        std::cout << "ip=" << p.first << " port=" << p.second << std::endl;
    }
    gl->notifyAll(gs);
    return true;
}
