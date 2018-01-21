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
    GameLobby(GameManager & gm, rtype::protocol_tcp::GameInfo const & gi, int uid);
    GameLobby(GameLobby const &) = delete;
    GameLobby(GameLobby &&) = delete;
    GameLobby & operator = (GameLobby const &) = delete;
    GameLobby & operator = (GameLobby &&) = delete;

    void joinGame(std::shared_ptr<Connection> cptr);
    void leaveGame(std::shared_ptr<Connection> cptr);

    bool isFull();
    bool isEmpty();

    int getId() const;
private:
    int id_;
    std::vector<std::shared_ptr<Connection>> cs_;
    rtype::protocol_tcp::GameInfo gi_;
    GameManager &gm_;
};
}

#endif //RTYPE_GAMELOBBY_H
