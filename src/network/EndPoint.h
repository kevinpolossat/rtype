//
// Created by Kévin POLOSSAT on 10/01/2018.
//

#ifndef LW_TCP_SERVER_ENDPOINT_H
#define LW_TCP_SERVER_ENDPOINT_H

#include <cstddef>
#include <string>
#include "Protocol.h"
#include "socket_operations.h"

namespace lw_network {

class EndPoint {
public:
    EndPoint();
    EndPoint(addrinfo const *addrinfo, std::string const & hostName, std::string const & service);
    EndPoint(EndPoint const &other);
    EndPoint(EndPoint &&other);

    EndPoint &operator=(EndPoint const &other);
    EndPoint &operator=(EndPoint &&other);

    const std::string &HostName() const;
    void SetHostName(const std::string &hostName_);
    const std::string &Service() const;
    void SetService(const std::string &service_);
    std::size_t Size() const;
    void SetSize(std::size_t s);
    sockaddr *Data();
    sockaddr const *Data() const;
    Protocol const & protocol() const;
    void setProtocol(Protocol const & p);
    std::string PortStr() const;
	std::string HostNameStr() const;
private:
    std::size_t size_ = sizeof(sockaddr_storage);
    std::string hostName_;
    std::string service_;
    Protocol protocol_;
    sockaddr_storage addr_;
};
}
#endif //LW_TCP_SERVER_ENDPOINT_H
