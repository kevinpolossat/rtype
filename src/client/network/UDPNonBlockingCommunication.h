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

    using Handle = std::function<void(void *, std::size_t size)>;

    bool open(std::string const &port = "0");
    void addDest(std::string const & hostName, std::string const & port);
    void addDest(lw_network::EndPoint const & ep);
    void addDests(std::vector<std::pair<std::string, std::string>> const & ipAndPort);
    void addHandle(Handle h);
    std::string getPort() const;

    template<typename T>
    void notifyAll(T const &toSend);

private:
    static constexpr int BufferSize = 1024;
    lw_network::Socket s_;
    std::vector<lw_network::EndPoint> dest_;
    Handle handler_;
    std::array<char, BufferSize> bRead_;
    std::array<char, BufferSize> bWrite_;
};

}
}

#endif //RTYPE_UDPNONBLOCKINGCOMMUNCATION_H
