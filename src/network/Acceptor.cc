//
// Created by Kévin POLOSSAT on 19/11/2017.
//

#include <iostream>
#include "Acceptor.h"

lw_network::Acceptor::Acceptor(lw_network::Reactor &reactor): Socket(), reactor_(reactor) {
    reactor_.registerHandler(this->getImpl(), lw_network::Reactor::OperationType::read);
}

lw_network::Acceptor::~Acceptor() {
    reactor_.unregisterHandler(this->getImpl(), Reactor::OperationType::read);
}

void lw_network::Acceptor::asyncAccept(std::function<void(lw_network::ReactiveSocket, error_code)> completionHandler) {
    reactor_.submit(
            this->getImpl(),
            std::make_shared<AcceptOperation>(
                    completionHandler,
                    *this),
            Reactor::OperationType::read);
}

lw_network::Reactor &lw_network::Acceptor::reactor() {
    return reactor_;
}

void lw_network::AcceptOperation::complete() {
    completionHandler_(s_, ec_);
}

bool lw_network::AcceptOperation::handle() {
    acceptor_.accept(s_, ec_);
    return true;
}

lw_network::AcceptOperation::AcceptOperation(
        std::function<void(lw_network::ReactiveSocket, lw_network::error_code)> completionHandler,
        lw_network::Acceptor &acceptor):
        completionHandler_(std::move(completionHandler)),
        acceptor_(acceptor),
        s_(acceptor.reactor()),
        ec_(no_error) {}
