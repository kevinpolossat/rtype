//
// Created by Kévin POLOSSAT on 14/01/2018.
//

#include <iostream>
#include <sstream>
#include "Buffer.h"
#include "Connection.h"
#include "ConnectionManager.h"

std::array<Connection::Handle, 10> const Connection::handles_ = {
        &Connection::handleUnknown,
        &Connection::handleListQuery,
        &Connection::handleListAnswer,
        &Connection::handleCreateGameQuery,
        &Connection::handleCreateGameAnswer,
        &Connection::handleJoinGameQuery,
        &Connection::handleJoinGameAnswer,
        &Connection::handleLeaveGame,
        &Connection::handleGameState,
        &Connection::handleGameStart
};

Connection::Connection(lw_network::ReactiveSocket s, ConnectionManager &cm) : s_(std::move(s)), cm_(cm) {}

void Connection::start() {
    doRead_();
}

void Connection::stop() {
    s_.close();
}

void Connection::doWrite_() {
    s_.async_write(
            lw_network::Buffer(const_cast<void *>(reinterpret_cast<void const *>(bufferWrite_.data())),
                               bufferWrite_.size()),
            [this](std::size_t, lw_network::error_code) {
                doRead_();
            }
    );
}

void Connection::doRead_() {
    s_.async_read_some(
            lw_network::Buffer(bufferRead_.data(), bufferRead_.size()),
            [this](std::size_t nbyte, lw_network::error_code ec) {
                if (nbyte > 0 && ec == lw_network::no_error) {
                    packet_.append(bufferRead_.data(), nbyte);
                    std::size_t p;
                    while ((p = packet_.find("\r\n")) != std::string::npos) {
                        auto hId = h_.id;
                        (this->*handles_[h_.id])(packet_.substr(0, p));
                        if (hId != rtype::protocol_tcp::UNKNOWN) {
                            h_.id = rtype::protocol_tcp::UNKNOWN;
                        }
                        packet_ = packet_.substr(p + 2/*discard \r\n*/);
                    }
                    doRead_();
                }
                else if (nbyte == 0) {
                    cm_.stop(shared_from_this());
                }
            }
    );
}

void Connection::handleUnknown(std::string const &json) {
    h_ = rtype::protocol_tcp::extract<rtype::protocol_tcp::Header>(json);
}

void Connection::handleListQuery(std::string const &json) {
    auto a = rtype::protocol_tcp::extract<rtype::protocol_tcp::QueryList>(json);
}

void Connection::handleListAnswer(std::string const &json) {
    auto a = rtype::protocol_tcp::extract<rtype::protocol_tcp::AnswerList>(json);
}

void Connection::handleCreateGameQuery(std::string const &json) {
    auto a = rtype::protocol_tcp::extract<rtype::protocol_tcp::QueryCreateGame>(json);
}

void Connection::handleCreateGameAnswer(std::string const &json) {
    auto a = rtype::protocol_tcp::extract<rtype::protocol_tcp::AnswerCreateGame>(json);
}

void Connection::handleJoinGameQuery(std::string const &json) {
    auto a = rtype::protocol_tcp::extract<rtype::protocol_tcp::QueryJoinGame>(json);
}

void Connection::handleJoinGameAnswer(std::string const &json) {
    auto a = rtype::protocol_tcp::extract<rtype::protocol_tcp::AnswerJoinGame>(json);
}

void Connection::handleGameState(std::string const &json) {
    auto a = rtype::protocol_tcp::extract<rtype::protocol_tcp::GameState>(json);
}

void Connection::handleGameStart(std::string const &json) {
    auto a = rtype::protocol_tcp::extract<rtype::protocol_tcp::GameStart>(json);
}

std::string const &Connection::getName() const {
    return name_;
}

void Connection::setName(std::string name) {
    name_ = std::move(name);
}

int Connection::getIdGame() const {
    return idGame_;
}

void Connection::setIdGame(int idGame) {
    idGame_ = idGame;
}

void Connection::handleLeaveGame(std::string const &json) {
    auto a = rtype::protocol_tcp::extract<rtype::protocol_tcp::QueryLeaveGame>(json);
}
