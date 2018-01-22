//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#include "Launcher.h"

bool rtype::Launcher::launch(std::shared_ptr<rtype::GameLobby> gl) {
    rtype::protocol_tcp::GameStart gs;
    gs.value = {"localhost", "66666"};
    gl->notifyAll(gs);
    return true;
}
