//
// Created by Kévin POLOSSAT on 14/01/2018.
//

#include <functional>
#include <iostream>
#include <sstream>
#include "Buffer.h"
#include "Connection.h"
#include "ConnectionManager.h"
#include "GameManager.h"

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

Connection::Connection(
        lw_network::ReactiveSocket s,
        ConnectionManager &cm,
        rtype::GameManager & gameManager):
        s_(std::move(s)),
        cm_(cm),
        gm_(gameManager) {}

void Connection::start() {
    doRead_();
}

void Connection::stop() {
    s_.close();
}

void Connection::onSend_(std::shared_ptr<std::string> toSend, std::size_t nbyte, lw_network::error_code ec) {
//TODO HANDLE ERROR
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

void Connection::handleListQuery(std::string const &) {
    rtype::protocol_tcp::AnswerList qla;
    qla.value = std::move(gm_.getAllGameInfo());
    sendString(std::move(rtype::protocol_tcp::transform(qla)));
}

void Connection::handleListAnswer(std::string const &) {}

void Connection::handleCreateGameQuery(std::string const &json) {
    auto a = rtype::protocol_tcp::extract<rtype::protocol_tcp::QueryCreateGame>(json);
    idGame_ = gm_.createGame(a.value, shared_from_this());
    rtype::protocol_tcp::AnswerCreateGame acg;
    acg.statusOrId = idGame_;
    sendString(std::move(rtype::protocol_tcp::transform(acg)));
}

void Connection::handleCreateGameAnswer(std::string const &) {}

void Connection::handleJoinGameQuery(std::string const &json) {
    auto a = rtype::protocol_tcp::extract<rtype::protocol_tcp::QueryJoinGame>(json);
    rtype::protocol_tcp::GameInfo gi;
    std::shared_ptr<rtype::GameLobby> gl;
    rtype::GameManager::JoinGameResult res;
    std::tie(res, gl) = gm_.joinGame(a.value, shared_from_this());
    rtype::protocol_tcp::AnswerJoinGame ajg;
    ajg.value = res  == rtype::GameManager::JoinGameResult::FAILURE ? rtype::protocol_tcp::not_ok : rtype::protocol_tcp::ok;
    sendString(std::move(rtype::protocol_tcp::transform(ajg)));
    if (res  != rtype::GameManager::JoinGameResult::FAILURE) {
        if (gl) {
            rtype::protocol_tcp::GameState gs;
            gs.value = gl->getGameInfo().playersNames;
            gl->notifyAll(gs);
            if (res == rtype::GameManager::JoinGameResult::STARTED) {
                rtype::protocol_tcp::GameStart gs;
                gs.value = {"", ""}; // TODO GET PORT AND IP HERE HERE
                gl->notifyAll(gs);
            }
        }
    }
}

void Connection::handleJoinGameAnswer(std::string const &) {}

void Connection::handleLeaveGame(std::string const &json) {
    auto a = rtype::protocol_tcp::extract<rtype::protocol_tcp::QueryLeaveGame>(json);
    gm_.leaveGame(a.value, shared_from_this());
    idGame_ = 0;
}

void Connection::handleGameState(std::string const &) {}

void Connection::handleGameStart(std::string const &) {}

int Connection::getIdGame() const {
    return idGame_;
}

void Connection::setIdGame(int idGame) {
    idGame_ = idGame;
}


void Connection::sendString(std::string s) {
    auto obj = std::make_shared<std::string>(std::move(s));
    s_.async_write(
            lw_network::Buffer(static_cast<void *>(const_cast<char *>(obj->data())), obj->size()),
            std::bind(&Connection::onSend_, this, obj, std::placeholders::_1, std::placeholders::_2));
}
