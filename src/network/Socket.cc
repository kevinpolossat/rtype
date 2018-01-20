//
// Created by Kévin POLOSSAT on 08/01/2018.
//

#include "Socket.h"

lw_network::Socket::Socket(socket_type s): s_(s) {}

lw_network::Socket::~Socket() {}

lw_network::Socket::Socket(lw_network::Socket &&other) {
    s_ = other.s_;
    other.s_ = invalid_socket;
}

lw_network::Socket &lw_network::Socket::operator=(lw_network::Socket &&other) {
    s_ = other.s_;
    other.s_ = invalid_socket;
    return *this;
}

lw_network::Socket::Socket(const lw_network::Socket &other): s_(other.s_) {}

lw_network::Socket &lw_network::Socket::operator=(const lw_network::Socket &other) {
    s_ = other.s_;
    return *this;
}

lw_network::Socket &lw_network::Socket::operator=(socket_type s) {
    s_ = s;
    return *this;
}

void lw_network::Socket::open(const lw_network::Protocol &proto, error_code &e) {
    s_ = socket_operations::socket(proto.family(), proto.type(), proto.protocol(), e);
}

void lw_network::Socket::close(error_code &e) {
    socket_operations::close(s_, e);
    s_ = invalid_socket;
}

void lw_network::Socket::bind(const lw_network::EndPoint &endpoint, error_code &e) {
    socket_operations::bind<SockLenType>(s_, endpoint.Data(), endpoint.Size(), e);
}

void lw_network::Socket::listen(int backlog, error_code &e) { socket_operations::listen(s_, backlog, e); }

void lw_network::Socket::connect(const lw_network::EndPoint &endPoint, error_code &e) {
    socket_operations::connect<SockLenType>(s_, endPoint.Data(), endPoint.Size(), e);
}

void lw_network::Socket::accept(lw_network::Socket &socket, error_code &e) {
    EndPoint endPoint;
    std::size_t size = endPoint.Size();
    socket = socket_operations::accept<SockLenType>(s_, endPoint.Data(), &size, e);
}

void lw_network::Socket::setOption(int level, int optname, void const *optval, std::size_t optlen, error_code &e) {
    socket_operations::setsockopt<SockLenType>(s_, level, optname, optval, optlen, e);
}

void lw_network::Socket::getOption(int level, int optname, void *optval, std::size_t *optlen, error_code &e) const {
    socket_operations::getsockopt<SockLenType>(s_, level, optname, optval, optlen, e);
}

signed_size_type lw_network::Socket::recv(Buffer &buffer, int flags, error_code &e) {
    auto b = buffer.toIoBuffer();
    auto s = socket_operations::recv(getImpl(), &b, buffer.Size(), flags, e);
    if (!e) {
        buffer += s;
    }
    return s;
}

signed_size_type lw_network::Socket::send(Buffer &buffer, int flags, error_code &e) {
	auto b = buffer.toIoBuffer();
	auto s = socket_operations::send(getImpl(), &b, buffer.Size(), flags, e);
    if (!e) {
        buffer += s;
    }
    return s;
}

socket_type lw_network::Socket::getImpl() const { return s_; }

lw_network::EndPoint lw_network::Socket::localEndPoint(lw_network::error_code &e) const {
    EndPoint ep;

    std::size_t s = ep.Size();
    socket_operations::getsockname<SockLenType>(getImpl(), ep.Data(), &s, e);
    if (e != no_error) {
        return EndPoint();
    }
    ep.SetSize(s);
    return ep;
}

lw_network::EndPoint lw_network::Socket::remoteEndPoint(lw_network::error_code &e) const {
    EndPoint ep;

    std::size_t s = ep.Size();
    socket_operations::getpeername<SockLenType>(getImpl(), ep.Data(), &s, e);
    if (e != no_error) {
        return EndPoint();
    }
    ep.SetSize(s);
    return ep;
}

bool lw_network::Socket::isOpen() const { return s_ != invalid_socket; }

void lw_network::Socket::nonBlocking(bool yes, error_code &ec) {
    socket_operations::nonblocking(getImpl(), yes, ec);
}

signed_size_type lw_network::Socket::recvfrom(
        lw_network::EndPoint & endPoint,
        lw_network::Buffer &buffer,
        int flags,
        lw_network::error_code &e) {
	auto b = buffer.toIoBuffer();
	std::size_t size = endPoint.Size();
    auto s = socket_operations::recvfrom(getImpl(), &b, flags, endPoint.Data(), &size, e);
    endPoint.SetSize(size);
    if (!e) {
        buffer += s;
    }
    return s;
}

signed_size_type lw_network::Socket::sendto(
        lw_network::EndPoint const & endPoint,
        lw_network::Buffer &buffer,
        int flags,
        lw_network::error_code &e) {
	auto b = buffer.toIoBuffer();
	auto s = socket_operations::sendto(this->getImpl(), &b, flags, endPoint.Data(), endPoint.Size(), e);
    if (!e) {
        buffer += s;
    }
    return s;
}