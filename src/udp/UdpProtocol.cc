//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#include "UdpProtocol.h"

rtype::protocol_udp::Header::Header(int id, std::uint64_t seqId): id(id), seqId(seqId) {}

bool rtype::protocol_udp::Header::operator==(const rtype::protocol_udp::Header &rhs) const {
    return this->id == rhs.id && this->seqId == rhs.seqId;
}

rtype::protocol_udp::Entity::Entity(
        int id, int type, int state, float x, float y):
        id(id), type(type), state(state), x(x), y (y) {}

bool rtype::protocol_udp::Entity::operator==(const rtype::protocol_udp::Entity &rhs) const {
    return  this->id == rhs.id &&
            this->type == rhs.type &&
            this->state == rhs.state &&
            this->x == rhs.x &&
            this->y == rhs.y;
}

rtype::protocol_udp::Event::Event(int from, int type): from(from), type(type) {}

bool rtype::protocol_udp::Event::operator==(const rtype::protocol_udp::Event &rhs) const {
    return this->type == rhs.type && this->from == rhs.from;
}
