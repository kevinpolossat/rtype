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

struct TCPHeader {
    ProtocolId pId;

    template <class Archive>
    void load(Archive & ar) {
        ar(pId);
    }
};

struct QueryList {
    int value; // EMPTY
    template <class Archive>
    void save(Archive & ar) const {
        ar(LIST_GAME);
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }
    bool operator==(QueryList const & rhs) const { return this->value == rhs.value; }
};

struct GameInfo {
    std::string filename;
    int gameId;
    int nbPlayerMax;
    std::vector<std::string> playersNames;
    GameInfo() = default;
    GameInfo(std::string fileName_, int gameId_, int nbPlayerMax_, std::vector<std::string> playersNames_):
            filename(std::move(fileName_)),
            gameId(gameId_),
            nbPlayerMax(nbPlayerMax_),
            playersNames(std::move(playersNames_)) {}

    template <class Archive>
    void save(Archive & ar) const {
        ar(filename);
        ar(gameId);
        ar(nbPlayerMax);
        ar(playersNames);
    }

    template <class Archive>
    void load(Archive & ar) {
        ar(filename);
        ar(gameId);
        ar(nbPlayerMax);
        ar(playersNames);
    }
    bool operator==(GameInfo const & rhs) const {
        return
                this->filename == rhs.filename
                && this->gameId == rhs.gameId
                && this->nbPlayerMax == rhs.nbPlayerMax
                && this->playersNames == rhs.playersNames;
    }

};

struct QueryListAnswer {
    std::vector<GameInfo> value;
    QueryListAnswer(std::vector<GameInfo> gi = std::vector<GameInfo>()): value(std::move(gi)) {}

    template <class Archive>
    void save(Archive & ar) const {
        ar(LIST_ANSWER);
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }

    bool operator==(QueryListAnswer const & rhs) const { return this->value == rhs.value; }
};

struct CreateGame {
    std::string fileName;
    std::string playerName;
    int nbPlayerMax;

    template <class Archive>
    void save(Archive & ar) const {
        ar(fileName);
        ar(playerName);
        ar(nbPlayerMax);
    }

    template <class Archive>
    void load(Archive & ar) {
        ar(fileName);
        ar(playerName);
        ar(nbPlayerMax);
    }

    bool operator==(CreateGame const & rhs) const {
        return
                this->fileName == rhs.fileName
                && this->playerName == rhs.playerName
                && this->nbPlayerMax == rhs.nbPlayerMax;
    }
};

struct QueryCreateGame {
    CreateGame value;

    template <class Archive>
    void save(Archive & ar) const {
        ar(CREATE_GAME);
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }

    bool operator==(QueryCreateGame const & rhs) const {
        return this->value == rhs.value;
    }
};

struct AnswerCreateGame {
    int statusOrId;

    template <class Archive>
    void save(Archive & ar) const {
        ar(CREATE_GAME_ANSWER);
        ar(statusOrId);
    }

    template <class Archive>
    void load(Archive & ar) { ar(statusOrId); }

    bool operator==(AnswerCreateGame const & rhs) const {
        return this->statusOrId == rhs.statusOrId;
    }
};

struct JoinGameInfo {
    int gameId;
    std::string playerName;

    template <class Archive>
    void save(Archive & ar) const {
        ar(gameId);
        ar(playerName);
    }

    template <class Archive>
    void load(Archive & ar) {
        ar(gameId);
        ar(playerName);
    }

    bool operator==(JoinGameInfo const & rhs) const {
        return this->gameId == rhs.gameId && this->playerName == rhs.playerName;
    }
};

struct QueryJoinGame {
    JoinGameInfo value;

    template <class Archive>
    void save(Archive & ar) const {
        ar(JOIN_GAME);
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }

    bool operator==(QueryJoinGame const & rhs) const {
        return this->value == rhs.value;
    }
};

struct AnswerJoinGame {
    int value;

    template <class Archive>
    void save(Archive & ar) const {
        ar(JOIN_GAME_ANSWER);
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }

    bool operator==(AnswerJoinGame const & rhs) const {
        return this->value == rhs.value;
    }
};

struct GameState {
    std::vector<std::string> value;

    template <class Archive>
    void save(Archive & ar) const {
        ar(GAME_STATE);
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }

    bool operator==(GameState const & rhs) const {
        return this->value == rhs.value;
    }
};

struct NetInfo {
    std::string ip;
    std::string port;

    template <class Archive>
    void save(Archive & ar) const {
        ar(ip);
        ar(port);
    }

    template <class Archive>
    void load(Archive & ar) {
        ar(ip);
        ar(port);
    }

    bool operator==(NetInfo const & rhs) const {
        return this->ip == rhs.ip && this->port == rhs.port;
    }
};

struct GameStart {
    NetInfo value;

    template <class Archive>
    void save(Archive & ar) const {
        ar(GAME_START);
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }

    bool operator==(GameStart const & rhs) const {
        return this->value == rhs.value;
    }
};

}
}

#endif //RTYPE_PROTOCOL_H
