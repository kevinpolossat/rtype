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
        std::cout << "HANDLING PACKET WITH SEQID=" << p.h.seqId << std::endl;
        auto seqId = p.h.seqId; // STORE SEQID TO TREAT ONLY THE MOST RECENT PACKET
        // COMPARE IT WITH PREVIOUSLY TESTED
        // if (seqId > savedSeqId) {
        //treat packet
        // }
        // else {
        // discard
        //}
    });
    gl->notifyAll(gs);
    auto t = std::thread([udp]() { // GAME HERE // add own class ?
        std::vector<rtype::protocol_udp::Entity> es;
        es.emplace_back(55, 0, 42, 42.0f, 42.0f);
        es.emplace_back(56, 0, 42, 42.0f, 42.0f);
        es.emplace_back(57, 0, 42, 42.0f, 42.0f);
        for (;;) {
            udp->recv(); // DO NOT USE DIRECTLY USE NOTIFYALL AND NETWORK MANAGER
            udp->notifyAll(es);
            udp->send(); // DO NOT USE DIRECTLY USE NOTIFYALL AND NETWORK MANAGER
        }
        udp->close(); // DO NOT USE DIRECTLY USE NOTIFYALL AND NETWORK MANAGER
    });
    t.detach();
    return true;
}
