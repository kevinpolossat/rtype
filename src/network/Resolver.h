//
// Created by Kévin POLOSSAT on 01/11/2017.
//

#ifndef LW_TCP_SERVER_RESOLVER_H
#define LW_TCP_SERVER_RESOLVER_H

#include <vector>
#include <string>
#include <functional>
#include "EndPoint.h"

namespace lw_network {
    class Resolver {
    public:
        explicit Resolver();
        Resolver(
                std::string const &node,
                std::string const & service,
                int family,
                int sock_type,
                int protocol,
                int flags);
        Resolver(Resolver const & other) = delete;
        Resolver(Resolver && other) noexcept;
        ~Resolver() = default;
        Resolver & operator = (Resolver const & other) = delete;
        Resolver & operator = (Resolver && other) noexcept;

        std::string const & Node() const;
        Resolver & SetNode(std::string const & node);

        std::string const & Service() const;
        Resolver & SetService(std::string const & service);

        int Family() const;
        Resolver & SetFamily(int family);

        int SockType() const;
        Resolver & SetSockType(int sock_type);

        int Protocol() const;
        Resolver & SetProtocol(int protocol);

        int Flags() const;
        Resolver & SetFlags(int flags);

        std::vector<EndPoint> Resolve(
                std::string const & node,
                std::string const & service,
                int family,
                int sock_type,
                int protocol,
                int flags);

        std::vector<EndPoint> Resolve() const;

    private:
        std::string node_;
        std::string service_;
        int family_;
        int sock_type_;
        int protocol_;
        int flags_;
    };
}


#endif //LW_TCP_SERVER_RESOLVER_H
