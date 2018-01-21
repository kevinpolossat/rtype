//
// Created by Kévin POLOSSAT on 21/01/2018.
//

#include "GameLobby.h"

rtype::GameLobby::GameLobby(
        GameManager &gm,
        rtype::protocol_tcp::GameInfo const &gi,
        int uid): gm_(gm), gi_(gi), id_(uid) {}

void rtype::GameLobby::joinGame(std::shared_ptr<Connection> cptr) {
    cs_.push_back(cptr);
    gi_.playersNames.push_back(cptr->getName());
}

void rtype::GameLobby::leaveGame(std::shared_ptr<Connection> cptr) {
    cs_.erase(std::remove(cs_.begin(), cs_.end(), cptr), cs_.end());
    gi_.playersNames.erase(
            std::remove(
                    gi_.playersNames.begin(),
                    gi_.playersNames.end(),
                    cptr->getName()),
            gi_.playersNames.end());
}

bool rtype::GameLobby::isFull() {
    return gi_.nbPlayerMax == cs_.size();
}

bool rtype::GameLobby::isEmpty() {
    return cs_.empty();
}

int rtype::GameLobby::getId() const {
    return id_;
}
