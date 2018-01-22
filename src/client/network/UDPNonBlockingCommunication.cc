//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#include <iostream>
#include "Resolver.h"
#include "UDPNonBlockingCommunication.h"

void ge::network::UDPNonBlockingCommuncation::send() {

}

void ge::network::UDPNonBlockingCommuncation::recv() {

}

void ge::network::UDPNonBlockingCommuncation::close() {
    auto e = lw_network::no_error;
    s_.close(e);
}

bool ge::network::UDPNonBlockingCommuncation::open(std::string const &port) {
    s_.openAsUdp(port);
    return s_.isOpen();
}

void ge::network::UDPNonBlockingCommuncation::addHandle(
        int packetId,
        ge::network::UDPNonBlockingCommuncation::Handle h) {
    handlers_.insert(std::make_pair(packetId, h));
}

void ge::network::UDPNonBlockingCommuncation::addDest(lw_network::EndPoint const &ep) {
    dest_.push_back(ep);
}

void ge::network::UDPNonBlockingCommuncation::addDest(std::string const &hostName, std::string const &port) {
    lw_network::Resolver re;
    re
            .SetNode(hostName)
            .SetService(port)
            .SetFamily(AF_UNSPEC)
            .SetSockType(SOCK_DGRAM)
            .SetFlags(AI_PASSIVE);
    lw_network::EndPoint ep = re.Resolve().front();
    this->addDest(ep);
}

std::string ge::network::UDPNonBlockingCommuncation::getPort() const {
    auto e = lw_network::no_error;
    auto ep = s_.localEndPoint(e);
    return ep.PortStr();
}
