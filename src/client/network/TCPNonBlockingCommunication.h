//
// Created by Kévin POLOSSAT on 21/01/2018.
//

#ifndef RTYPE_TCPNONBLOCKINGCOMMUNICATION_H
#define RTYPE_TCPNONBLOCKINGCOMMUNICATION_H


#include <unordered_map>
#include <array>
#include <queue>
#include "RtypeProtocol.h"
#include "NetworkCommunication.h"
#include "Socket.h"

namespace rtype {
namespace network {

class TCPNonBlockingCommunication: public NetworkCommunication {
public:
    TCPNonBlockingCommunication() = default;
    using Handle = std::function<void(std::string const & json)>;
    bool open(std::string const & host, std::string const & port);
    void send() override; // DO NOT CALL FOR THE NETWORKMANAGER
    void recv() override;
    void close() override;
    void addHandle(int packetId, Handle h);
    template<typename ProtocolPacket>
    void sendToServer(ProtocolPacket const & p) {
        this->pushToSendQueue_(rtype::protocol_tcp::transform(p));
    }

private:
    void pushToSendQueue_(std::string s);
    lw_network::Socket s_;
    std::unordered_map<int, Handle> handlers_;
    std::array<char, 1024> bufferRead_;
    std::string packet_;
    rtype::protocol_tcp::Header h_;
    std::queue<std::string> toSend_;
};
}
}


#endif //RTYPE_TCPNONBLOCKINGCOMMUNICATION_H
