//
// Created by Kévin POLOSSAT on 14/01/2018.
//

#ifndef LW_TCP_SERVER_CONNECTIONMANAGER_H
#define LW_TCP_SERVER_CONNECTIONMANAGER_H

#include <vector>
#include "ReactiveSocket.h"
#include "Connection.h"

class ConnectionManager {
public:
    ConnectionManager() = default;
    ConnectionManager(ConnectionManager const & other) = delete;
    ConnectionManager & operator = (ConnectionManager const & other) = delete;
    void start(std::shared_ptr<Connection> cptr);
    void stop(std::shared_ptr<Connection> cptr);
    void stopAll();
private:
    std::vector<std::shared_ptr<Connection>> connections_;
};


#endif //LW_TCP_SERVER_CONNECTIONMANAGER_H
