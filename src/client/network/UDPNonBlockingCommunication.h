//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#ifndef RTYPE_UDPNONBLOCKINGCOMMUNCATION_H
#define RTYPE_UDPNONBLOCKINGCOMMUNCATION_H

#include "Socket.h"
#include <array>
#include <vector>
#include <functional>
#include <unordered_map>

#include "NetworkCommunication.h"

namespace ge {
namespace network {

class UDPNonBlockingCommuncation: public NetworkCommunication {
public:
    void send() override; // DO NOT CALL FOR THE NETWORKMANAGER
    void recv() override;
    void close() override;

    using Handle = std::function<void(std::vector<std::string> const & json)>;

    bool open(std::string const &port = "0");
    void addDest(std::string const & hostName, std::string const & port);
    void addDest(lw_network::EndPoint const & ep);
    void addDests(std::vector<std::pair<std::string, std::string>> const & ipAndPort);
    void addHandle(Handle h);
    std::string getPort() const;
private:
    lw_network::Socket s_;
    std::vector<lw_network::EndPoint> dest_;
    Handle handler_;
    std::array<char, 1024> bRead_;
};

}
}

#endif //RTYPE_UDPNONBLOCKINGCOMMUNCATION_H
