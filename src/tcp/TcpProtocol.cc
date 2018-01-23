//
// Created by Kévin POLOSSAT on 20/01/2018.
//

#include "TcpProtocol.h"
#include <cereal/archives/json.hpp>

using namespace rtype::protocol_tcp;

rtype::protocol_tcp::ProtocolId const QueryList::Id = LIST_GAME;
rtype::protocol_tcp::ProtocolId const AnswerList::Id = LIST_ANSWER;
rtype::protocol_tcp::ProtocolId const QueryCreateGame::Id = CREATE_GAME;
rtype::protocol_tcp::ProtocolId const AnswerCreateGame::Id = CREATE_GAME_ANSWER;
rtype::protocol_tcp::ProtocolId const QueryJoinGame::Id = JOIN_GAME;
rtype::protocol_tcp::ProtocolId const AnswerJoinGame::Id = JOIN_GAME_ANSWER;
rtype::protocol_tcp::ProtocolId const QueryLeaveGame::Id = LEAVE_GAME;
rtype::protocol_tcp::ProtocolId const GameState::Id = GAME_STATE;
rtype::protocol_tcp::ProtocolId const GameStart::Id = GAME_START;

bool QueryList::operator==(QueryList const & rhs) const { return this->value == rhs.value; }

GameInfo::GameInfo(
        std::string fileName_,
        int gameId_,
        int nbPlayerMax_,
        std::vector<std::string> playersNames_):
        filename(std::move(fileName_)),
        gameId(gameId_),
        nbPlayerMax(nbPlayerMax_),
        playersNames(std::move(playersNames_)) {}

bool GameInfo::operator==(GameInfo const & rhs) const {
    return
            this->filename == rhs.filename
            && this->gameId == rhs.gameId
            && this->nbPlayerMax == rhs.nbPlayerMax
            && this->playersNames == rhs.playersNames;
}

AnswerList::AnswerList(std::vector<GameInfo> gi): value(std::move(gi)) {}

bool AnswerList::operator==(AnswerList const & rhs) const { return this->value == rhs.value; }

bool CreateGame::operator==(CreateGame const & rhs) const {
    return
            this->fileName == rhs.fileName
            && this->playerName == rhs.playerName
            && this->nbPlayerMax == rhs.nbPlayerMax
            && this->port == rhs.port;
}

bool QueryCreateGame::operator==(QueryCreateGame const & rhs) const {
    return this->value == rhs.value;
}

bool AnswerCreateGame::operator==(AnswerCreateGame const & rhs) const {
    return this->statusOrId == rhs.statusOrId;
}


bool JoinGameInfo::operator==(JoinGameInfo const & rhs) const {
    return this->gameId == rhs.gameId && this->playerName == rhs.playerName && this->port == rhs.port;
}

bool QueryJoinGame::operator==(QueryJoinGame const & rhs) const {
    return this->value == rhs.value;
}

bool AnswerJoinGame::operator==(AnswerJoinGame const & rhs) const {
    return this->value == rhs.value;
}

bool GameState::operator==(GameState const & rhs) const {
    return this->value == rhs.value;
}

bool NetInfo::operator==(NetInfo const & rhs) const {
    return this->port == rhs.port && this->id == rhs.id;
}

bool GameStart::operator==(GameStart const & rhs) const {
    return this->value == rhs.value;
}

bool Header::operator==(Header const &rhs) const {
    return this->id == rhs.id;
}

bool QueryLeaveGame::operator==(QueryLeaveGame const &rhs) const {
    return this->value == rhs.value;
}
