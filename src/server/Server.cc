//
// Created by Kévin POLOSSAT on 14/01/2018.
//


#include <memory>
#include <iostream>
#include "Server.h"
#include "Resolver.h"

Server::Server(): reactor_(), acceptor_(reactor_) {
    lw_network::Reactor reactor;
    lw_network::Resolver re;
	re
            .SetService("4242")
            .SetFamily(AF_UNSPEC)
            .SetSockType(SOCK_STREAM)
            .SetFlags(AI_PASSIVE);
    int yes = 1;
    lw_network::error_code e = lw_network::no_error;
    auto p = re.Resolve();
    for (auto const & endPoint : p) {
        e = lw_network::no_error;
        acceptor_.open(endPoint.protocol(), e);
		if (e) {
            continue;
        }
        acceptor_.setOption(SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int), e);
        acceptor_.bind(endPoint, e);
        if (e) {
            acceptor_.close(e);
            continue;
        }
		break;
    }
    if (!acceptor_.isOpen()) {
        std::cerr << "FAIL" << std::endl;
        return ;
    }
    acceptor_.listen(SOMAXCONN, e);
    if (e) {
        std::cerr << "FAIL listen" << std::endl;
        return ;
    }
	doAccept_();
}

void Server::run() {
    reactor_.handleEvents();
}

void Server::doAccept_() {
	acceptor_.asyncAccept(
            [this](lw_network::ReactiveSocket peer, lw_network::error_code ec) {
                connectionManager_.start(std::make_shared<Connection>(std::move(peer), connectionManager_));
                this->doAccept_();
            }
    );
}
