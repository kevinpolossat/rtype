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
#include <serialization/cereal/archives/portable_binary.hpp>

namespace rtype {
namespace protocol_tcp {

enum ProtocolId {
    UNKNOWN,
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

struct Header {
    ProtocolId id;
    int size;

    template<typename Archive>
    void serialize(Archive & ar) {
        ar(id);
        ar(size);
    }
};

struct QueryList {
    int value; // EMPTY
    template <class Archive>
    void save(Archive & ar) const {
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }
    bool operator==(QueryList const & rhs) const;
};

struct GameInfo {
    std::string filename;
    int gameId;
    int nbPlayerMax;
    std::vector<std::string> playersNames;
    GameInfo() = default;
    GameInfo(std::string fileName_, int gameId_, int nbPlayerMax_, std::vector<std::string> playersNames_);

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
    bool operator==(GameInfo const & rhs) const;

};

struct QueryListAnswer {
    std::vector<GameInfo> value;
    explicit QueryListAnswer(std::vector<GameInfo> gi = std::vector<GameInfo>());

    template <class Archive>
    void save(Archive & ar) const {
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }

    bool operator==(QueryListAnswer const & rhs) const;
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

    bool operator==(CreateGame const & rhs) const;
};

struct QueryCreateGame {
    CreateGame value;

    template <class Archive>
    void save(Archive & ar) const {
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }

    bool operator==(QueryCreateGame const & rhs) const;
};

struct AnswerCreateGame {
    int statusOrId;

    template <class Archive>
    void save(Archive & ar) const {
        ar(statusOrId);
    }

    template <class Archive>
    void load(Archive & ar) { ar(statusOrId); }

    bool operator==(AnswerCreateGame const & rhs) const;
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

    bool operator==(JoinGameInfo const & rhs) const;
};

struct QueryJoinGame {
    JoinGameInfo value;

    template <class Archive>
    void save(Archive & ar) const {
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }

    bool operator==(QueryJoinGame const & rhs) const;
};

struct AnswerJoinGame {
    int value;

    template <class Archive>
    void save(Archive & ar) const {
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }

    bool operator==(AnswerJoinGame const & rhs) const;
};

struct GameState {
    std::vector<std::string> value;

    template <class Archive>
    void save(Archive & ar) const {
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }

    bool operator==(GameState const & rhs) const;
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

    bool operator==(NetInfo const & rhs) const;
};

struct GameStart {
    NetInfo value;

    template <class Archive>
    void save(Archive & ar) const {
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }

    bool operator==(GameStart const & rhs) const;
};
}
}

#endif //RTYPE_PROTOCOL_H
