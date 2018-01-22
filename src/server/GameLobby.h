//
// Created by Kévin POLOSSAT on 21/01/2018.
//

#ifndef RTYPE_GAMELOBBY_H
#define RTYPE_GAMELOBBY_H


#include "Connection.h"


namespace rtype {
class GameManager;
class GameLobby {
public:
    GameLobby(GameManager & gm, rtype::protocol_tcp::CreateGame const & gi, int uid);
    GameLobby(GameLobby const &) = delete;
    GameLobby(GameLobby &&) = delete;
    GameLobby & operator = (GameLobby const &) = delete;
    GameLobby & operator = (GameLobby &&) = delete;

    void joinGame(rtype::protocol_tcp::JoinGameInfo const &jgi, std::shared_ptr<Connection> cptr);
    void leaveGame(std::shared_ptr<Connection> cptr);

    bool isFull();
    bool isEmpty();

    int getId() const;
    rtype::protocol_tcp::GameInfo const & getGameInfo() const;

    template<typename T>
    void notifyAll(T const & obj) const {
        auto s = rtype::protocol_tcp::transform(obj);
        for (auto c: cs_) {
            c->sendString(s);
        }
    }

private:
    std::vector<std::shared_ptr<Connection>> cs_;
    rtype::protocol_tcp::GameInfo gi_;
    GameManager &gm_;
};
}

#endif //RTYPE_GAMELOBBY_H
