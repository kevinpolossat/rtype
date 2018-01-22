//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#ifndef RTYPE_UDPNONBLOCKINGCOMMUNCATION_H
#define RTYPE_UDPNONBLOCKINGCOMMUNCATION_H

#include "Socket.h"
#include <vector>
#include <functional>
#include <unordered_map>

#include "NetworkCommunication.h"

namespace rtype {
namespace network {

class UDPNonBlockingCommuncation: public NetworkCommunication {
public:
    void send() override; // DO NOT CALL FOR THE NETWORKMANAGER
    void recv() override;
    void close() override;

    using Handle = std::function<void(std::vector<std::string> const & json)>;

    bool open(std::string const &port);
    void addDest(std::string const & hostName, std::string const & port);
    void addDest(lw_network::EndPoint const & ep);
    void addHandle(int packetId, Handle h);
    std::string const & getPort() const;
private:
    lw_network::Socket s_;
    std::vector<lw_network::EndPoint> dest_;
    std::unordered_map<int, Handle> handlers_;
    std::string port_;
};

}
}

#endif //RTYPE_UDPNONBLOCKINGCOMMUNCATION_H
