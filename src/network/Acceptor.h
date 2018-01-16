//
// Created by Kévin POLOSSAT on 19/11/2017.
//

#ifndef LW_TCP_SERVER_SOCKETACCEPTOR_H
#define LW_TCP_SERVER_SOCKETACCEPTOR_H

#include <functional>
#include <memory>
#include "socket_operations.h"
#include "ReactiveSocket.h"
#include "Reactor.h"
#include "Operation.h"

namespace lw_network {

class Acceptor: public lw_network::Socket {
public:
    explicit Acceptor(Reactor & reactor);
    Acceptor(Acceptor const & other) = delete;
    Acceptor(Acceptor && other) = delete;
    ~Acceptor();
    Acceptor & operator = (Acceptor const & other) = delete;
    Acceptor & operator = (Acceptor && other) = delete;
    void asyncAccept(std::function<void(ReactiveSocket, error_code)> completionHandler);
    Reactor & reactor();
private:
    Reactor &reactor_;
};

class AcceptOperation: public Operation {
public:
    AcceptOperation(std::function<void(lw_network::ReactiveSocket, error_code)> completionHandler, lw_network::Acceptor & acceptor);
    void complete();
    bool handle();
private:
    std::function<void(ReactiveSocket, error_code)> completionHandler_;
    Acceptor & acceptor_;
    ReactiveSocket s_;
    error_code ec_;
};
}

#endif //LW_TCP_SERVER_SOCKETACCEPTOR_H
