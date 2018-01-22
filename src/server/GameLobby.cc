//
// Created by Kévin POLOSSAT on 21/01/2018.
//

#include "GameLobby.h"

rtype::GameLobby::GameLobby(
        GameManager &gm,
        rtype::protocol_tcp::CreateGame const &cg,
        int uid):
        gm_(gm) {
    gi_.gameId = uid;
    gi_.nbPlayerMax = cg.nbPlayerMax;
    gi_.filename = cg.fileName;
}

void rtype::GameLobby::joinGame(rtype::protocol_tcp::JoinGameInfo const &jgi, std::shared_ptr<Connection> cptr) {
    cs_.push_back(cptr);
    gi_.playersNames.push_back(jgi.playerName);
}

void rtype::GameLobby::leaveGame(std::shared_ptr<Connection> cptr) {
    auto it = std::find(cs_.begin(), cs_.end(), cptr);
    if (it != cs_.end()) {
        auto i = it - cs_.begin();
        cs_.erase(it);
        gi_.playersNames.erase(gi_.playersNames.begin() + i);
    }
}

bool rtype::GameLobby::isFull() {
    return gi_.nbPlayerMax == cs_.size();
}

bool rtype::GameLobby::isEmpty() {
    return cs_.empty();
}

int rtype::GameLobby::getId() const {
    return gi_.gameId;
}

rtype::protocol_tcp::GameInfo const &rtype::GameLobby::getGameInfo() const {
    return gi_;
}