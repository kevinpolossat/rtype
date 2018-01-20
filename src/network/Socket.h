//
// Created by Kévin POLOSSAT on 08/01/2018.
//

#ifndef LW_TCP_SERVER_BASICSOCKET_H
#define LW_TCP_SERVER_BASICSOCKET_H

#include "Buffer.h"
#include "Protocol.h"
#include "EndPoint.h"

namespace lw_network {
class Socket {
#if defined (__linux__) || defined (__APPLE__)
    using SockLenType = socklen_t;
#elif defined (_WIN32) || defined (_WIN64)
	using SockLenType = int;
#else
#error "unknown platform"
#endif
public:
    Socket(socket_type s = invalid_socket);
    virtual ~Socket();

    Socket(Socket const & other);
    Socket(Socket && other);
    Socket & operator = (Socket const & other);
    Socket & operator = (socket_type s);
    Socket & operator = (Socket && other);

    void open(Protocol const & proto, error_code &e);
    bool isOpen() const;
    void close(error_code &e);
    void bind(EndPoint const & endpoint, error_code &e);
    void listen(int backlog, error_code &e);
    void connect(EndPoint const & endPoint, error_code &e);
    void accept(Socket & socket, error_code &e);
    void setOption(int level, int optname, void const *optval, std::size_t optlen, error_code &e);
    void getOption(int level, int optname, void *optval, std::size_t *optlen, error_code &e) const;
    signed_size_type recv(Buffer & buffer, int flags, error_code &e);
    signed_size_type send(Buffer & buffer, int flags, error_code &e);
    signed_size_type recvfrom(EndPoint & endPoint, Buffer & buffer, int flags, error_code &e);
    signed_size_type sendto(EndPoint const & endPoint, Buffer & buffer, int flags, error_code &e);
    EndPoint localEndPoint(error_code &e) const;
    EndPoint remoteEndPoint(error_code &e) const;
    void nonBlocking(bool yes, error_code &ec);
    socket_type getImpl() const;
private:
    socket_type s_;
};
}


#endif //LW_TCP_SERVER_BASICSOCKET_H
