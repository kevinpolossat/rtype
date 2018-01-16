//
// Created by Kévin POLOSSAT on 16/01/2018.
//

#ifndef RTYPE_PROTOCOL_H
#define RTYPE_PROTOCOL_H

/**
 * LIST
 * {
 *      protocolId: LIST_GAME,
 *      value: ""
 * }
 * LIST_ANSWER
 * {
 *      protocolId: LIST_ANSWER,
 *      value: [
 *          {
 *              fileName: filename,
 *              gameId: id,
 *              playersMax: nbPlayerMax,
 *              players: [playerName]
 *          }
 *      ]
 * }
 * CREAGE_GAME
 * {
 *      protocolId: CREATE_GAME,
 *      value: {
 *          name: fileName,
 *          nbPlayer : nbPlayer,
 *          playerName: name
 *      }
 * }
 * CREATE_GAME_ANSWER
 * {
 *      protocolId: CREATE_GAME_ANSWER,
 *      value: NOT_OK / ID_GAME
 * }
 * JOIN_GAME
 * {
 *      protocolId: CREATE_GAME_ANSWER,
 *      value: {
 *          id: gameId,
 *          playerName: name
 *      }
 * }
 * JOIN_GAME_ANSWER
 * {
 *      protocolId: JOIN_GAME_ANSWER,
 *      value: NOT_OK / OK
 * }
 * GAME_STATE
 * {
 *      protocolId: GAME_STATE,
 *      value: [playerName]
 * }
 * GAME_START
 * {
 *      protocolId: GAME_START,
 *      value: {
 *          ip: ip,
 *          port: port
 *      }
 * }
 */

#include <vector>
#include <string>

namespace rtype {
namespace protocol_tcp {

enum ProtocolId {
    LIST_GAME,
    LIST_ANSWER,
    CREATE_GAME,
    CREATE_GAME_ANSWER,
    JOIN_GAME,
    JOIN_GAME_ANSWER,
    GAME_STATE,
    GAME_START
};

static constexpr int not_ok = -1;
static constexpr int ok = 0;

struct QueryList {
    ProtocolId protocolId = LIST_GAME;
    int value; // EMPTY
};

struct GameInfo {
    std::string filename;
    int gameId;
    int nbPlayerMax;
    std::vector<std::string> playersNames;
};

struct QueryListAnswer {
    ProtocolId protocolId = LIST_ANSWER;
    std::vector<GameInfo> value;
};

struct CreateGame {
    std::string fileName;
    std::string playerName;
    int nbPlayerMax;
};

struct QueryCreateGame {
    ProtocolId protocolId = CREATE_GAME;
    CreateGame value;
};

struct AnswerCreateGame {
    ProtocolId protocolId = CREATE_GAME_ANSWER;
    int statusOrId;
};

struct JoinGameInfo {
    int gameId;
    std::string playerName;
};

struct QueryJoinGame {
    ProtocolId protocolId = JOIN_GAME;
    JoinGameInfo value;
};

struct AnswerJoinGame {
    ProtocolId protocolId = JOIN_GAME_ANSWER;
    int value;
};

struct GameState {
    ProtocolId protocolId = GAME_STATE;
    std::vector<std::string> value;
};

struct NetInfo {
    std::string ip;
    std::string port;
};

struct GameStart {
    ProtocolId protocolId = GAME_START;
    NetInfo value;
};

}
}

#endif //RTYPE_PROTOCOL_H
