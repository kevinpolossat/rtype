//
// Created by Kévin POLOSSAT on 14/01/2018.
//

#ifndef LW_TCP_SERVER_SERVER_H
#define LW_TCP_SERVER_SERVER_H


#include <Reactor.h>
#include <Acceptor.h>
#include "ConnectionManager.h"
#include "GameManager.h"

class Server {
public:
    Server();
    void run();
private:
    void doAccept_();

private:
    lw_network::Reactor reactor_;
    lw_network::Acceptor acceptor_;
    ConnectionManager connectionManager_;
    rtype::GameManager gameManager_;

};


#endif //LW_TCP_SERVER_SERVER_H
