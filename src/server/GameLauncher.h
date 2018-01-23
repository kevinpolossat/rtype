//
// Created by Kévin POLOSSAT on 21/01/2018.
//

#ifndef RTYPE_GAMELAUNCHER_H
#define RTYPE_GAMELAUNCHER_H

#include "GameLobby.h"

namespace rtype {
class GameLauncher {
public:
    virtual ~GameLauncher() = default;
    virtual bool launch(std::shared_ptr<GameLobby> gl) = 0;
};
}
#endif //RTYPE_GAMELAUNCHER_H
