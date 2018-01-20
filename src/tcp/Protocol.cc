//
// Created by Kévin POLOSSAT on 20/01/2018.
//

#include "Protocol.h"

using namespace rtype::protocol_tcp;

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

QueryListAnswer::QueryListAnswer(std::vector<GameInfo> gi): value(std::move(gi)) {}

bool QueryListAnswer::operator==(QueryListAnswer const & rhs) const { return this->value == rhs.value; }

bool CreateGame::operator==(CreateGame const & rhs) const {
    return
            this->fileName == rhs.fileName
            && this->playerName == rhs.playerName
            && this->nbPlayerMax == rhs.nbPlayerMax;
}

bool QueryCreateGame::operator==(QueryCreateGame const & rhs) const {
    return this->value == rhs.value;
}

bool AnswerCreateGame::operator==(AnswerCreateGame const & rhs) const {
    return this->statusOrId == rhs.statusOrId;
}


bool JoinGameInfo::operator==(JoinGameInfo const & rhs) const {
    return this->gameId == rhs.gameId && this->playerName == rhs.playerName;
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
    return this->ip == rhs.ip && this->port == rhs.port;
}

bool GameStart::operator==(GameStart const & rhs) const {
    return this->value == rhs.value;
}