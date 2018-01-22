//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#include "UdpProtocol.h"
rtype::protocol_udp::Header::Header(int id): id(id) {}

rtype::protocol_udp::Entity::Entity(
        int id, int type, int state, float x, float y):
        id(id), type(type), state(state), x(x), y (y) {}

rtype::protocol_udp::Event::Event(int from, int type): from(from), type(type) {}
