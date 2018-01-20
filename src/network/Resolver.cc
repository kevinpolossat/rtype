//
// Created by Kévin POLOSSAT on 01/11/2017.
//

#include "lw_network_error.h"
#include "Resolver.h"

lw_network::Resolver::Resolver():
        family_(0), sock_type_(0), protocol_(0), flags_(0) {

}

lw_network::Resolver::Resolver(
        std::string const &node,
        std::string const &service,
        int family,
        int sock_type,
        int protocol,
        int flags):
        node_(node),
        service_(service),
        family_(family),
        sock_type_(sock_type),
        protocol_(protocol),
        flags_(flags) {}

lw_network::Resolver::Resolver(Resolver &&other) noexcept:
        node_(std::move(other.node_)),
        service_(std::move(other.service_)),
        family_(other.family_),
        sock_type_(other.sock_type_),
        protocol_(other.protocol_),
        flags_(other.flags_) {}

lw_network::Resolver &lw_network::Resolver::operator=(Resolver &&other) noexcept {
    node_ = std::move(other.node_);
    service_ = std::move(other.service_);
    family_ = other.family_;
    sock_type_ = other.sock_type_;
    protocol_ = other.protocol_;
    flags_ = other.flags_;
    other.family_ = -1;
    other.sock_type_ = -1;
    other.protocol_ = -1;
    other.flags_ = -1;
    return *this;
}

std::string const &lw_network::Resolver::Node() const {
    return node_;
}

lw_network::Resolver & lw_network::Resolver::SetNode(std::string const &node) {
    node_ = node;
    return *this;
}

std::string const &lw_network::Resolver::Service() const {
    return service_;
}

lw_network::Resolver & lw_network::Resolver::SetService(std::string const &service) {
    service_ = service;
    return *this;
}

int lw_network::Resolver::Family() const {
    return family_;
}

lw_network::Resolver & lw_network::Resolver::SetFamily(int family) {
    family_ = family;
    return *this;
}

int lw_network::Resolver::SockType() const {
    return sock_type_;
}

lw_network::Resolver & lw_network::Resolver::SetSockType(int sock_type) {
    sock_type_ = sock_type;
    return *this;
}

int lw_network::Resolver::Protocol() const {
    return protocol_;
}

lw_network::Resolver & lw_network::Resolver::SetProtocol(int protocol) {
    protocol_ = protocol;
    return *this;
}

int lw_network::Resolver::Flags() const {
    return flags_;
}

lw_network::Resolver & lw_network::Resolver::SetFlags(int flags) {
    flags_ = flags;
    return *this;
}

std::vector<lw_network::EndPoint> lw_network::Resolver::Resolve(
        std::string const &node,
        std::string const &service,
        int family,
        int sock_type,
        int protocol,
        int flags) {
    node_ = node;
    service_ = service;
    family_ = family;
    sock_type_ = sock_type;
    protocol_ = protocol;
    flags_ = flags;
    return Resolve();
}

std::vector<lw_network::EndPoint> lw_network::Resolver::Resolve() const {
    addrinfo hints = {0};
    addrinfo * res = nullptr;
    int status;

    hints.ai_family = family_;
    hints.ai_socktype = sock_type_;
    hints.ai_protocol = protocol_;
    hints.ai_flags = flags_;
    if ((status = getaddrinfo(
            node_.empty() ? nullptr : node_.c_str(),
            service_.empty() ? nullptr : service_.c_str(),
            &hints,
            &res)) != 0) {
        throw ResolveError(gai_strerror(status));
    }
    addrinfo *it = res;
    std::vector<lw_network::EndPoint> endPoints;
    std::string hostName = it->ai_canonname ? it->ai_canonname : node_;
    for (; it; it = it->ai_next) {
        endPoints.emplace_back(it, hostName, service_);
    }
    freeaddrinfo(res);
    return endPoints;
}

