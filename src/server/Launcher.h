//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#ifndef RTYPE_LAUNCHER_H
#define RTYPE_LAUNCHER_H

#include <vector>
#include "GameLauncher.h"

namespace rtype {
class Launcher: public rtype::GameLauncher {
public:
    bool launch(std::shared_ptr<GameLobby> gl) override;
private:
    std::vector<std::shared_ptr<GameLobby>> gls_; // TODO TO REMOVE TMP
};
}


#endif //RTYPE_LAUNCHER_H
