//
// Created by Kévin POLOSSAT on 21/01/2018.
//

#ifndef RTYPE_GAMEMANAGER_H
#define RTYPE_GAMEMANAGER_H

#include <utility>
#include "GameLobby.h"
#include "GameLauncher.h"

namespace rtype {
class GameManager {
public:
    enum class JoinGameResult {
        FAILURE,
        JOINED,
        STARTED
    };

    GameManager(std::unique_ptr<GameLauncher> gl);
    GameManager(GameManager const & other) = delete;
    GameManager(GameManager && other) = delete;
    ~GameManager() = default;

    GameManager & operator = (GameManager const & other) = delete;
    GameManager & operator = (GameManager && other) = delete;

    int createGame(rtype::protocol_tcp::CreateGame const &cg);
    std::pair<JoinGameResult, std::shared_ptr<GameLobby>> joinGame(rtype::protocol_tcp::JoinGameInfo const &jgi, std::shared_ptr<Connection> cptr);
    bool leaveGame(int uid, std::shared_ptr<Connection> cptr);
    std::vector<rtype::protocol_tcp::GameInfo> getAllGameInfo() const;
    std::shared_ptr<rtype::GameLobby> getGameById(int uid);
private:
    std::vector<std::shared_ptr<GameLobby>> lobbies_;
    std::unique_ptr<GameLauncher> launcher_;
};
}


#endif //RTYPE_GAMEMANAGER_H
