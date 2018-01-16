//
// Created by Kévin POLOSSAT on 11/01/2018.
//

#include "Protocol.h"

lw_network::Protocol::Protocol(int family, int type, int protocol): family_(family), type_(type), protocol_(protocol) {

}

lw_network::Protocol::Protocol(Protocol const &other): family_(other.family_), type_(other.type_), protocol_(other.protocol_) {

}

lw_network::Protocol::Protocol(Protocol &&other): family_(other.family_), type_(other.type_), protocol_(other.protocol_) {

}

lw_network::Protocol &lw_network::Protocol::operator=(lw_network::Protocol const &other) {
    family_ = other.family_;
    type_ = other.type_;
    protocol_ = other.protocol_;
    return *this;
}

lw_network::Protocol &lw_network::Protocol::operator=(lw_network::Protocol &&other) {
    family_ = other.family_;
    type_ = other.type_;
    protocol_ = other.protocol_;
    return *this;
}

int lw_network::Protocol::family() const {
    return family_;
}

void lw_network::Protocol::setFamily(int f) {
    family_ = f;
}

int lw_network::Protocol::type() const {
    return type_;
}

void lw_network::Protocol::setType(int t) {
    type_ = t;
}

int lw_network::Protocol::protocol() const {
    return protocol_;
}

void lw_network::Protocol::setProtocol(int p) {
    protocol_ = p;
}
