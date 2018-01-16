//
// Created by Kévin POLOSSAT on 13/01/2018.
//

#include "FDSet.h"

lw_network::FDSet::FDSet() {
    reset();
}

lw_network::FDSet::FDSet(const lw_network::FDSet &other) {
    fdset_ = other.fdset_;
}

lw_network::FDSet::FDSet(lw_network::FDSet &&other) {
    fdset_ = other.fdset_;
    other.reset();
}

lw_network::FDSet &lw_network::FDSet::operator=(const lw_network::FDSet &other) {
    fdset_ = other.fdset_;
    return *this;
}

lw_network::FDSet &lw_network::FDSet::operator=(lw_network::FDSet &&other) {
    fdset_ = other.fdset_;
    other.reset();
    return *this;
}

lw_network::FDSet &lw_network::FDSet::operator-=(socket_type s) {
    clear(s);
    return *this;
}

lw_network::FDSet &lw_network::FDSet::operator+=(socket_type s) {
    set(s);
    return *this;
}

fd_set *lw_network::FDSet::data() {
    return &fdset_;
}

void lw_network::FDSet::clear(socket_type s) {
    FD_CLR(s, &fdset_);
}

void lw_network::FDSet::reset() {
    FD_ZERO(&fdset_);
}

void lw_network::FDSet::set(socket_type s) {
    FD_SET(s, &fdset_);
}

bool lw_network::FDSet::isSet(socket_type s) const {
    return static_cast<bool>(FD_ISSET(s, &fdset_));
}
