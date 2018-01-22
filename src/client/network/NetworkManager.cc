//
// Created by Kévin POLOSSAT on 21/01/2018.
//

#include <algorithm>
#include "NetworkManager.h"

void ge::network::NetworkManager::addCommuncation(std::shared_ptr<ge::network::NetworkCommunication> c) {
    communications_.push_back(c);
}

void ge::network::NetworkManager::removeCommuncation(std::shared_ptr<ge::network::NetworkCommunication> c) {
    communications_.erase(
            std::remove(
                    communications_.begin(),
                    communications_.end(),
                    c),
            communications_.end());
}

void ge::network::NetworkManager::shutdownGracefully() {
    for (auto & c: communications_) {
        c->close();
    }
}

void ge::network::NetworkManager::handleSendEvent() {
    for (auto & c: communications_) {
        c->send();
    }
}

void ge::network::NetworkManager::handleRecvEvent() {
    for (auto & c: communications_) {
        c->recv();
    }
}
