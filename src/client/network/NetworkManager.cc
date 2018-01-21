//
// Created by Kévin POLOSSAT on 21/01/2018.
//

#include <algorithm>
#include "NetworkManager.h"

void rtype::network::NetworkManager::addCommuncation(std::shared_ptr<rtype::network::NetworkCommunication> c) {
    communications_.push_back(c);
}

void rtype::network::NetworkManager::removeCommuncation(std::shared_ptr<rtype::network::NetworkCommunication> c) {
    communications_.erase(
            std::remove(
                    communications_.begin(),
                    communications_.end(),
                    c),
            communications_.end());
}

void rtype::network::NetworkManager::shutdownGracefully() {
    for (auto & c: communications_) {
        c->close();
    }
}

void rtype::network::NetworkManager::handleSendEvent() {
    for (auto & c: communications_) {
        c->send();
    }
}

void rtype::network::NetworkManager::handleRecvEvent() {
    for (auto & c: communications_) {
        c->recv();
    }
}
