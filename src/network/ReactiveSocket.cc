//
// Created by Kévin POLOSSAT on 14/01/2018.
//

#include "ReactiveSocket.h"

lw_network::ReactiveSocket::ReactiveSocket(lw_network::Reactor &reactor): Socket(), reactor_(reactor) {
    reactor_.registerHandler(this->getImpl(), lw_network::Reactor::read);
    reactor_.registerHandler(this->getImpl(), lw_network::Reactor::write);
}

lw_network::ReactiveSocket &lw_network::ReactiveSocket::operator=(const lw_network::ReactiveSocket &other) {
    Socket::operator=(other);
    return *this;
}

lw_network::ReactiveSocket &lw_network::ReactiveSocket::operator=(lw_network::ReactiveSocket &&other) {
    Socket::operator=(other);
    return *this;
}

void lw_network::ReactiveSocket::async_read_some(Buffer b, std::function<void(size_t, lw_network::error_code)> completionHandler) {
    reactor_.submit(
            this->getImpl(),
            std::make_shared<ReadSomeOperation>(*this, b, completionHandler),
            lw_network::Reactor::OperationType::read);
}

void lw_network::ReactiveSocket::async_read(Buffer b, std::function<void(size_t, lw_network::error_code)> completionHandler) {
    reactor_.submit(
            this->getImpl(),
            std::make_shared<ReadOperation>(*this, b, completionHandler),
            lw_network::Reactor::OperationType::read);
}

void lw_network::ReactiveSocket::async_write_some(Buffer b, std::function<void(size_t, lw_network::error_code)> completionHandler) {
    reactor_.submit(
            this->getImpl(),
            std::make_shared<WriteSomeOperation>(*this, b, completionHandler),
            lw_network::Reactor::OperationType::write);
}

void lw_network::ReactiveSocket::async_write(Buffer b, std::function<void(size_t, lw_network::error_code)> completionHandler) {
    reactor_.submit(
            this->getImpl(),
            std::make_shared<WriteOperation>(*this, b, completionHandler),
            lw_network::Reactor::OperationType::write);
}

void lw_network::ReactiveSocket::close() {
        reactor_.unregisterHandler(this->getImpl(), lw_network::Reactor::read);
        reactor_.unregisterHandler(this->getImpl(), lw_network::Reactor::write);
    error_code ec = no_error;
    Socket::close(ec);
}

lw_network::ReadOperation::ReadOperation(
        lw_network::ReactiveSocket &s,
        lw_network::Buffer b,
        std::function<void(std::size_t nbyte, error_code ec)> completionHandler):
        s_(s), ec_(no_error), nbyte_(0), b_(std::move(b)), completionHandler_(std::move(completionHandler)) {}

bool lw_network::ReadOperation::handle() {
    nbyte_ = s_.recv(b_, 0, ec_);
    return b_.exhausted();
}

void lw_network::ReadOperation::complete() {
    completionHandler_(nbyte_, ec_);
}

lw_network::WriteOperation::WriteOperation(
        lw_network::ReactiveSocket &s,
        lw_network::Buffer b,
        std::function<void(size_t, lw_network::error_code)> completionHandler):
        s_(s), ec_(no_error), nbyte_(0), b_(std::move(b)), completionHandler_(std::move(completionHandler)) {}

bool lw_network::WriteOperation::handle() {
    nbyte_ = s_.send(b_, 0, ec_);
    return b_.exhausted();
}

void lw_network::WriteOperation::complete() {
    completionHandler_(nbyte_, ec_);
}

lw_network::ReadSomeOperation::ReadSomeOperation(
        lw_network::ReactiveSocket &s,
        lw_network::Buffer b,
        std::function<void(size_t, lw_network::error_code)> completionHandler):
        s_(s), ec_(no_error), nbyte_(0), b_(std::move(b)), completionHandler_(std::move(completionHandler)) {

}

bool lw_network::ReadSomeOperation::handle() {
    nbyte_ = s_.recv(b_, 0, ec_);
    return true;
}

void lw_network::ReadSomeOperation::complete() {
    completionHandler_(nbyte_, ec_);
}

lw_network::WriteSomeOperation::WriteSomeOperation(
        lw_network::ReactiveSocket &s,
        lw_network::Buffer b,
        std::function<void(size_t, lw_network::error_code)> completionHandler):
        s_(s), ec_(no_error), nbyte_(0), b_(std::move(b)), completionHandler_(std::move(completionHandler)) {}

bool lw_network::WriteSomeOperation::handle() {
    nbyte_ = s_.send(b_, 0, ec_);
    return true;
}

void lw_network::WriteSomeOperation::complete() {
    completionHandler_(nbyte_, ec_);
}
