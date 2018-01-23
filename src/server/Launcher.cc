//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#include <thread>
#include "Launcher.h"
#include "UDPNonBlockingCommunication.h"

bool rtype::Launcher::launch(std::shared_ptr<rtype::GameLobby> gl) {
    rtype::protocol_tcp::GameStart gs;
    auto udp = std::make_shared<ge::network::UDPNonBlockingCommuncation>(); // TODO PUT IN NETWORK MANAGER
    udp->open(/*default port 0*/);
    gs.value = {udp->getPort()};
    udp->addDests(gl->getIpAndPorts());
    udp->addHandle([](void *data, std::size_t nbyte) {
        auto p = rtype::protocol_udp::extract<rtype::protocol_udp::Event/*recieving event only*/>(static_cast<char *>(data), nbyte);
    });
    gl->notifyAll(gs);
    auto t = std::thread([udp]() { // GAME HERE // add own class ?
        udp->recv(); // DO NOT USE DIRECTLY USE NOTIFYALL AND NETWORK MANAGER
        udp->send(); // DO NOT USE DIRECTLY USE NOTIFYALL AND NETWORK MANAGER
        udp->close(); // DO NOT USE DIRECTLY USE NOTIFYALL AND NETWORK MANAGER
    });
    t.detach();
    return true;
}
