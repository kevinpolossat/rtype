//
// Created by Kévin POLOSSAT on 21/01/2018.
//

#include <network/Resolver.h>
#include <iostream>
#include "TCPNonBlockingCommunication.h"

void rtype::network::TCPNonBlockingCommunication::send() {
    while (!toSend_.empty()) {
        std::string & s = toSend_.front();
        auto ec = lw_network::no_error;
        auto b = lw_network::Buffer(const_cast<char *>(s.c_str()), s.size());
        //std::cout << "sending : "  << packet_  << std::endl;
        while (!b.exhausted()) {
            auto nbyte = s_.send(b, 0, ec);
            //std::cout << "send=" << nbyte << std::endl;
            if (nbyte < 0 || ec != lw_network::no_error) {
                break;
            }
            if (nbyte == 0) { // CONNECTION CLOSED BY SERVER HANDLE
                break;
            }
            b += nbyte;
        }
        if (b.exhausted()) {
            toSend_.pop();
        }
        else {
            s.assign(static_cast<char *>(b.Data()));
            break;
        }
    }
}

void rtype::network::TCPNonBlockingCommunication::recv() {
    auto ec = lw_network::no_error;
    auto b = lw_network::Buffer(bufferRead_.data(), bufferRead_.size());
    auto nbyte = s_.recv(b, 0, ec);
    if (nbyte <= 0) { // TODO HANDLE ERROR HERE ?
        //std::cout << "nbyte=" << nbyte << " err=" << ec  << " EWOULDBLOCK=" << EWOULDBLOCK << std::endl;
        return ;
    }
    packet_.append(bufferRead_.data(), nbyte);
    std::size_t p;
//    std::cout << "before process[" << packet_ << "]" << std::endl;
    while ((p = packet_.find("\r\n")) != std::string::npos) {
        if (h_.id == rtype::protocol_tcp::UNKNOWN) {
            h_ = rtype::protocol_tcp::extract<rtype::protocol_tcp::Header>(packet_.substr(0, p));
        }
        else {
            auto handleIt = handlers_.find(h_.id);
            if (handleIt != handlers_.end()) {
                handlers_[h_.id](packet_.substr(0, p));
            }
            h_.id = rtype::protocol_tcp::UNKNOWN;
        }
        packet_ = packet_.substr(p + 2/*discard \r\n*/);
        //std::cout << "remaining[" << packet_ << "]" << std::endl;
    }
}

void rtype::network::TCPNonBlockingCommunication::close() {
    auto e = lw_network::no_error;
    s_.close(e);
}

bool rtype::network::TCPNonBlockingCommunication::open(std::string const &host, std::string const &port) {
    lw_network::Resolver re;
    re
            .SetNode(host)
            .SetService(port)
            .SetFamily(AF_UNSPEC)
            .SetSockType(SOCK_STREAM);
    for (auto & endPoint: re.Resolve()) {
        auto e = lw_network::no_error;
        s_.open(endPoint.protocol(), e);
        if (e) {
            continue;
        }
        s_.connect(endPoint, e);
        if (e) {
            s_.close(e);
            continue;
        }
        break;
    }
    auto isOpen = s_.isOpen();
    if (isOpen) {
        auto err = lw_network::no_error;
        s_.nonBlocking(true, err);
        //std::cout << "::::IS CONNECTED::: nonblocking=" << err << std::endl;
    }
    return isOpen;
}

void rtype::network::TCPNonBlockingCommunication::pushToSendQueue_(std::string s) {
    //std::cout << s << std::endl;
    toSend_.push(std::move(s));
}

void rtype::network::TCPNonBlockingCommunication::addHandle(int packetId,
                                                            rtype::network::TCPNonBlockingCommunication::Handle h) {
        handlers_.insert(std::make_pair(packetId, h));
}
