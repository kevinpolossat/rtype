//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#ifndef RTYPE_RTYPEPROTOCOL_H
#define RTYPE_RTYPEPROTOCOL_H

#include <vector>

namespace rtype {
namespace protocol_udp {

struct Header {
    explicit Header(int id);
    int id;
};

struct Entity {
    Entity(int id, int type, int state, float x, float y);
    int id;
    int type;
    int state;
    float x;
    float y;
};

struct Event {
    Event(int from, int type);
    int from;
    int type;
};

template<typename T>/* T == EVENT OR ENTITY */
struct Packet {
    Header h;
    std::vector<T> t;
};

}
}
#endif //RTYPE_RTYPEPROTOCOL_H
