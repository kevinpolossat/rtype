//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#include "Launcher.h"

bool rtype::Launcher::launch(std::shared_ptr<rtype::GameLobby> gl) {
    gls_.push_back(gl);
    return true;
}
