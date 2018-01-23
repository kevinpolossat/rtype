//
// Created by Kévin POLOSSAT on 10/01/2018.
//

#include <cstring>
#include "EndPoint.h"

lw_network::EndPoint::EndPoint() {

}

lw_network::EndPoint::EndPoint(
        addrinfo const *addrinfo,
        std::string const & hostName,
        std::string const & service):
        size_(static_cast<std::size_t>(addrinfo->ai_addrlen)),
        hostName_(hostName),
        service_(service),
        protocol_(addrinfo->ai_family, addrinfo->ai_socktype, addrinfo->ai_protocol) {
    std::memcpy(&addr_, addrinfo->ai_addr, size_);
}

lw_network::EndPoint::EndPoint(const lw_network::EndPoint &other):
        size_(other.size_),
        hostName_(other.hostName_),
        service_(other.service_),
        protocol_(other.protocol_) {
    std::memcpy(&addr_, &other.addr_, size_);
}

lw_network::EndPoint::EndPoint(lw_network::EndPoint &&other):
        size_(other.size_),
        hostName_(std::move(other.hostName_)),
        service_(std::move(other.service_)),
        protocol_(std::move(other.protocol_)){
    std::memcpy(&addr_, &other.addr_, size_);
}

lw_network::EndPoint &lw_network::EndPoint::operator=(const lw_network::EndPoint &other) {
    size_ = other.size_;
    hostName_ = other.hostName_;
    service_ = other.service_;
    protocol_ = other.protocol_;
    std::memcpy(&addr_, &other.addr_, size_);
    return *this;
}

lw_network::EndPoint &lw_network::EndPoint::operator=(lw_network::EndPoint &&other) {
    size_ = other.size_;
    hostName_ = std::move(other.hostName_);
    service_ = std::move(other.service_);
    protocol_ = std::move(other.protocol_);
    std::memcpy(&addr_, &other.addr_, size_);
    return *this;
}

const std::string &lw_network::EndPoint::HostName() const {
    return hostName_;
}

void lw_network::EndPoint::SetHostName(const std::string &hostName_) {
    EndPoint::hostName_ = hostName_;
}

const std::string &lw_network::EndPoint::Service() const {
    return service_;
}

void lw_network::EndPoint::SetService(const std::string &service_) {
    EndPoint::service_ = service_;
}

std::size_t lw_network::EndPoint::Size() const {
    return size_;
}

void lw_network::EndPoint::SetSize(std::size_t s) {
    size_ = s;
}

sockaddr *lw_network::EndPoint::Data() {
    return reinterpret_cast<sockaddr *>(&addr_);
}

sockaddr const *lw_network::EndPoint::Data() const {
    return reinterpret_cast<sockaddr const *>(&addr_);
}

const lw_network::Protocol &lw_network::EndPoint::protocol() const {
    return protocol_;
}

void lw_network::EndPoint::setProtocol(Protocol const & p) {
    protocol_ = p;
}

std::string lw_network::EndPoint::PortStr() const {
    char hoststr[NI_MAXHOST];
    char servstr[NI_MAXSERV];
    auto e = lw_network::no_error;
    socket_operations::getnameinfo(
            this->Data(),
            this->Size(),
            hoststr,
            sizeof(hoststr),
            servstr,
            sizeof(servstr),
            0,
            e);
    return std::string(servstr);
}

std::string lw_network::EndPoint::HostNameStr() const {
	char hoststr[NI_MAXHOST];
	char servstr[NI_MAXSERV];
	auto e = lw_network::no_error;
	socket_operations::getnameinfo(
		this->Data(),
		this->Size(),
		hoststr,
		sizeof(hoststr),
		servstr,
		sizeof(servstr),
		0,
		e);
	return std::string(hoststr);
}