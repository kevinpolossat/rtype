//
// Created by Kévin POLOSSAT on 02/11/2017.
//

#include <sys/ioctl.h>
#include "socket_operations.h"

socket_type lw_network::socket_operations::socket(int domain, int type, int protocol, lw_network::error_code &e) {
#if defined (__linux__) || defined (__APPLE__)
    socket_type s = ::socket(domain, type, protocol);
    if (s == socket_error) {
        e = errno;
    }
    return s;
#elif defined (_WIN32) || defined (_WIN64)
    #error "TODO DEFINE WINDOWS"
#else
#error "unknown platform"
#endif
    return 0;
}

void lw_network::socket_operations::close(socket_type s, lw_network::error_code &e) {
#if defined (__linux__) || defined (__APPLE__)
    int ret = ::close(s);
    if (ret == socket_error) {
        e = errno;
    }
#elif defined (_WIN32) || defined (_WIN64)
    #error "TODO DEFINE WINDOWS"
#else
#error "unknown platform"
#endif
}

void lw_network::socket_operations::listen(socket_type s, int backlog, lw_network::error_code &e) {
#if defined (__linux__) || defined (__APPLE__)
    int ret = ::listen(s, backlog);
    if (ret == socket_error) {
        e = errno;
    }
#elif defined (_WIN32) || defined (_WIN64)
    #error "TODO DEFINE WINDOWS"
#else
#error "unknown platform"
#endif
}

signed_size_type lw_network::socket_operations::recv(
        socket_type s, io_buffer *buff, std::size_t size, int flags, lw_network::error_code &e) {
#if defined (__linux__) || defined (__APPLE__)
    msghdr msg = {0};
    msg.msg_iov = buff;
    msg.msg_iovlen = 1;//static_cast<int>(size);
    signed_size_type ret = ::recvmsg(s, &msg, flags);
    if (ret == socket_error) {
        e = errno;
    }
    return ret;
#elif defined (_WIN32) || defined (_WIN64)
    #error "TODO DEFINE WINDOWS"
#else
#error "unknown platform"
#endif
    return 0;
}

signed_size_type lw_network::socket_operations::send(
        socket_type s, io_buffer *buff, std::size_t size, int flags, lw_network::error_code &e) {
#if defined (__linux__) || defined (__APPLE__)
    msghdr msg = {0};
    msg.msg_iov = buff;
    msg.msg_iovlen = 1;//static_cast<int>(size);
    signed_size_type ret = ::sendmsg(s, &msg, flags);
    if (ret == socket_error) {
        e = errno;
    }
    return ret;
#elif defined (_WIN32) || defined (_WIN64)
    #error "TODO DEFINE WINDOWS"
#else
#error "unknown platform"
#endif
    return 0;
}

void lw_network::socket_operations::select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds,
                                           struct timeval *timeout, lw_network::error_code &e) {
    e = ::select(nfds, readfds, writefds, errorfds, timeout);
}

void lw_network::socket_operations::nonblocking(socket_type s, bool yes, error_code &e) {
#if defined (__linux__) || defined (__APPLE__)
    e = ::ioctl(s, FIONBIO, &yes);
#elif defined (_WIN32) || defined (_WIN64)
    #error "TODO DEFINE WINDOWS"
#else
#error "unknown platform"
#endif
}

signed_size_type lw_network::socket_operations::recvfrom(
        socket_type s,
        io_buffer *buff,
        unsigned int flags,
        struct sockaddr *from,
        std::size_t *fromlen,
        lw_network::error_code &e) {
#if defined (__linux__) || defined (__APPLE__)
    msghdr msg = {0};
    msg.msg_name = static_cast<void *>(from);
    msg.msg_namelen = static_cast<int>(*fromlen);
    msg.msg_iov = buff;
    msg.msg_iovlen = 1;//static_cast<int>(size);
    signed_size_type ret = ::recvmsg(s, &msg, flags);
    if (ret == socket_error) {
        e = errno;
    }
    return ret;
#elif defined (_WIN32) || defined (_WIN64)
    #error "TODO DEFINE WINDOWS"
#else
#error "unknown platform"
#endif
}

signed_size_type lw_network::socket_operations::sendto(
        socket_type s,
        io_buffer *buff,
        unsigned int flags,
        const struct sockaddr *to,
        std::size_t tolen,
        error_code & e) {
#if defined (__linux__) || defined (__APPLE__)
    msghdr msg = {0};
    msg.msg_name = static_cast<void *>(const_cast<sockaddr *>(to));
    msg.msg_namelen = static_cast<int>(tolen);
    msg.msg_iov = buff;
    msg.msg_iovlen = 1;//static_cast<int>(size);
    signed_size_type ret = ::sendmsg(s, &msg, flags);
    if (ret == socket_error) {
        e = errno;
    }
    return ret;
#elif defined (_WIN32) || defined (_WIN64)
    #error "TODO DEFINE WINDOWS"
#else
#error "unknown platform"
#endif
}
