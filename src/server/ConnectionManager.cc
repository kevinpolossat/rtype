//
// Created by Kévin POLOSSAT on 14/01/2018.
//

#include <algorithm>
#include "ConnectionManager.h"

void ConnectionManager::start(std::shared_ptr<Connection> cptr) {
    connections_.push_back(cptr);
    cptr->start();
}

void ConnectionManager::stop(std::shared_ptr<Connection> cptr) {
    connections_.erase(std::remove(connections_.begin(), connections_.end(), cptr));
    cptr->stop();
}

void ConnectionManager::stopAll() {
    for (auto & c : connections_) {
        c->stop();
    }
    connections_.clear();
}
