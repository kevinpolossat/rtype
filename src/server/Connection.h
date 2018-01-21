//
// Created by Kévin POLOSSAT on 14/01/2018.
//

#ifndef LW_TCP_SERVER_CONNECTION_H
#define LW_TCP_SERVER_CONNECTION_H

#include <array>
#include <string>
#include "ReactiveSocket.h"
#include "Protocol.h"
#include "RtypeProtocol.h"

class ConnectionManager;

class Connection: public std::enable_shared_from_this<Connection> {
public:
    Connection(lw_network::ReactiveSocket s, ConnectionManager & cm);
    Connection(Connection const & other) = delete;
    Connection & operator = (Connection const & other) = delete;
    void start();
    void stop();
private:
    void doRead_();
    void doWrite_();
private:
    lw_network::ReactiveSocket s_;
    ConnectionManager &cm_;
    std::array<char, 1024> bufferRead_;
    std::string bufferWrite_;
    std::string packet_;
    rtype::protocol_tcp::Header h_;
    using Handle = void (Connection::*)(std::string const & json);
    static std::array<Handle, 9> const handles_;

    void handleUnknown(std::string const & json);
    void handleListQuery(std::string const & json);
    void handleListAnswer(std::string const & json);
    void handleCreateGameQuery(std::string const & json);
    void handleCreateGameAnswer(std::string const & json);
    void handleJoinGameQuery(std::string const & json);
    void handleJoinGameAnswer(std::string const & json);
    void handleGameState(std::string const & json);
    void handleGameStart(std::string const & json);
};


#endif //LW_TCP_SERVER_CONNECTION_H
