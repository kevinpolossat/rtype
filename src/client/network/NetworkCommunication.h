//
// Created by Kévin POLOSSAT on 21/01/2018.
//

#ifndef RTYPE_INETWORKCOMMUNICATION_H
#define RTYPE_INETWORKCOMMUNICATION_H

#include <string>

namespace rtype {
namespace network {
class NetworkCommunication {
public:
    virtual ~NetworkCommunication() = default;

    virtual void send() = 0;
    virtual void recv() = 0;
    virtual void close() = 0;
};
}
}


#endif //RTYPE_INETWORKCOMMUNICATION_H
