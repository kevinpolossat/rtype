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
#include <ostream>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

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
static constexpr int headerSize = 9;

struct Header {
    ProtocolId id = UNKNOWN;

    template<typename Archive>
    void serialize(Archive & ar) {
        ar(id);
    }
    bool operator==(Header const & rhs) const;
};

struct QueryList {
    static ProtocolId const Id;
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

struct AnswerList {
    static ProtocolId const Id;
    std::vector<GameInfo> value;
    explicit AnswerList(std::vector<GameInfo> gi = std::vector<GameInfo>());

    template <class Archive>
    void save(Archive & ar) const {
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }

    bool operator==(AnswerList const & rhs) const;
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
    static ProtocolId const Id;
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
    static ProtocolId const Id;
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
    static ProtocolId const Id;
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
    static ProtocolId const Id;
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
    static ProtocolId const Id;
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
    static ProtocolId const Id;
    NetInfo value;

    template <class Archive>
    void save(Archive & ar) const {
        ar(value);
    }

    template <class Archive>
    void load(Archive & ar) { ar(value); }

    bool operator==(GameStart const & rhs) const;
};

template<typename T>
T extract(std::string const & s) {
    T t;
    std::stringstream ss;
    ss << s;
    {
        cereal::JSONOutputArchive oa(ss);
        oa(t);
    }
    return t;
}

}
}

#endif //RTYPE_PROTOCOL_H
