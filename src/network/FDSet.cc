//
// Created by Kévin POLOSSAT on 13/01/2018.
//

#include <algorithm>
#include "FDSet.h"

lw_network::FDSet::FDSet(): maxDescriptor_(invalid_socket) {
    reset();
}

lw_network::FDSet::FDSet(const lw_network::FDSet &other) {
    fdset_ = other.fdset_;
	maxDescriptor_ = other.maxDescriptor_;
}

lw_network::FDSet::FDSet(lw_network::FDSet &&other) {
    fdset_ = other.fdset_;
	maxDescriptor_ = other.maxDescriptor_;
	other.reset();
}

lw_network::FDSet &lw_network::FDSet::operator=(const lw_network::FDSet &other) {
    fdset_ = other.fdset_;
	maxDescriptor_ = other.maxDescriptor_;
	return *this;
}

lw_network::FDSet &lw_network::FDSet::operator=(lw_network::FDSet &&other) {
    fdset_ = other.fdset_;
	maxDescriptor_ = other.maxDescriptor_;
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
	if (s == maxDescriptor_) {
		while (maxDescriptor_ != invalid_socket && !this->isSet(maxDescriptor_)) {
			--maxDescriptor_;
		}
	}
}

void lw_network::FDSet::reset() {
    FD_ZERO(&fdset_);
	maxDescriptor_ = invalid_socket;
}

void lw_network::FDSet::set(socket_type s) {
	FD_SET(s, &fdset_);
	if (maxDescriptor_ == invalid_socket || s > maxDescriptor_) {
		maxDescriptor_ = s;
	}
}

bool lw_network::FDSet::isSet(socket_type s) const {
    return static_cast<bool>(FD_ISSET(s, &fdset_));
}

socket_type lw_network::FDSet::maxDescriptor() const {
	return maxDescriptor_;
}