//
// Created by Kévin POLOSSAT on 02/11/2017.
//

#ifndef LW_TCP_SERVER_SOCKET_DEF_H
#define LW_TCP_SERVER_SOCKET_DEF_H

#if defined (__linux__) || defined (__APPLE__)

#include <cstddef>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>

#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)

using socket_type = int;
using io_buffer = iovec;
using signed_size_type = ssize_t;

#elif defined (_WIN32) || defined (_WIN64)

#error "TODO DEFINE WINDOWS"

#else

#error "unknown platform"

#endif

static constexpr socket_type invalid_socket = INVALID_SOCKET;
static constexpr int socket_error = SOCKET_ERROR;
namespace lw_network {
using error_code = int;
static constexpr error_code no_error = 0;

namespace socket_operations { // Low level socket function defined in according with the os.

socket_type socket(int domain, int type, int protocol, lw_network::error_code &e);

void close(socket_type s, lw_network::error_code &e);

template<typename SockLenType>
void bind(socket_type s, const struct sockaddr *addr, std::size_t addrlen, lw_network::error_code &e) {
#if defined (__linux__) || defined (__APPLE__)
    int ret = ::bind(s, addr, static_cast<SockLenType>(addrlen));
    if (ret == socket_error) {
        e = errno;
    }
#elif defined (_WIN32) || defined (_WIN64)
    #error "TODO DEFINE WINDOWS"
#else
#error "unknown platform"
#endif
}

void listen(socket_type s, int backlog, lw_network::error_code &e);

template<typename SockLenType>
void connect(socket_type s, const struct sockaddr *addr, std::size_t addrlen, lw_network::error_code &e) {
#if defined (__linux__) || defined (__APPLE__)
    int ret = ::connect(s, addr, static_cast<SockLenType>(addrlen));
    if (ret == socket_error) {
        e = errno;
    }
#elif defined (_WIN32) || defined (_WIN64)
    #error "TODO DEFINE WINDOWS"
#else
#error "unknown platform"
#endif
}

template<typename SockLenType>
socket_type accept(socket_type s, struct sockaddr *addr, std::size_t *addrlen, lw_network::error_code &e) {
#if defined (__linux__) || defined (__APPLE__)
    auto len = addrlen ? static_cast<SockLenType>(*addrlen) : 0;
    socket_type accepted = ::accept(s, addr, &len);
    if (accepted == invalid_socket) {
        e = errno;
    }
    if (addrlen) {
        *addrlen = static_cast<std::size_t>(len);
    }
    return accepted;
#elif defined (_WIN32) || defined (_WIN64)
    #error "TODO DEFINE WINDOWS"
#else
#error "unknown platform"
#endif
    return 0;
}

signed_size_type recv(socket_type s, io_buffer *buff, std::size_t size, int flags, lw_network::error_code &e);

signed_size_type send(socket_type s, io_buffer *buff, std::size_t size, int flags, lw_network::error_code &e);

signed_size_type recvfrom(
        socket_type s,
        io_buffer *buff,
        unsigned int flags,
        struct sockaddr *to,
        std::size_t *fromlen,
        error_code &e);

signed_size_type sendto(
        socket_type s,
        io_buffer *buff,
        unsigned int flags,
        const struct sockaddr *to,
        std::size_t tolen,
        error_code & e);

template<typename SockLenType>
void setsockopt(
        socket_type s,
        int level,
        int optname,
        void const *optval,
        std::size_t optlen,
        lw_network::error_code &e) {
#if defined (__linux__) || defined (__APPLE__)
    int ret = ::setsockopt(s, level, optname, optval, static_cast<SockLenType>(optlen));
    if (ret == socket_error) {
        e = errno;
    }
#elif defined (_WIN32) || defined (_WIN64)
    #error "TODO DEFINE WINDOWS"
#else
#error "unknown platform"
#endif
}

template<typename SockLenType>
void getsockopt(socket_type s, int level, int optname, void *optval, std::size_t *optlen, lw_network::error_code &e) {
#if defined (__linux__) || defined (__APPLE__)
    auto len = optlen ? static_cast<SockLenType>(*optlen) : 0;
    int ret = ::getsockopt(s, level, optname, optval, &len);
    if (ret == socket_error) {
        e = errno;
    }
    *optlen = static_cast<std::size_t>(len);
#elif defined (_WIN32) || defined (_WIN64)
    #error "TODO DEFINE WINDOWS"
#else
#error "unknown platform"
#endif
}

template<typename SockLenType>
void getsockname(socket_type s, struct sockaddr *addr, std::size_t *addrlen, lw_network::error_code &e) {
#if defined (__linux__) || defined (__APPLE__)
    auto len = addrlen ? static_cast<SockLenType>(*addrlen) : 0;
    int ret = ::getsockname(s, addr, &len);
    if (ret == socket_error) {
        e = errno;
    }
    *addrlen = static_cast<std::size_t>(len);
#elif defined (_WIN32) || defined (_WIN64)
    #error "TODO DEFINE WINDOWS"
#else
#error "unknown platform"
#endif
}

template<typename SockLenType>
void getpeername(socket_type s, struct sockaddr *addr, std::size_t *addrlen, lw_network::error_code &e) {
#if defined (__linux__) || defined (__APPLE__)
    auto len = addrlen ? static_cast<SockLenType>(*addrlen) : 0;
    int ret = ::getpeername(s, addr, &len);
    if (ret == socket_error) {
        e = errno;
    }
    *addrlen = static_cast<std::size_t>(len);
#elif defined (_WIN32) || defined (_WIN64)
    #error "TODO DEFINE WINDOWS"
#else
#error "unknown platform"
#endif
}

void select(
        int nfds,
        fd_set *readfds,
        fd_set *writefds,
        fd_set *errorfds,
        struct timeval *timeout,
        lw_network::error_code &e);

void nonblocking(socket_type s, bool yes, error_code &e);

} // socket_operations
} // lw_network

#endif //LW_TCP_SERVER_SOCKET_DEF_H
