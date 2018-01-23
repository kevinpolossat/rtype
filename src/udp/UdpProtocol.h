//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#ifndef RTYPE_RTYPEPROTOCOL_H
#define RTYPE_RTYPEPROTOCOL_H

#include <vector>
#include <array>
#include <sstream>
#include <fstream>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/vector.hpp>

namespace rtype {
namespace protocol_udp {

static constexpr int MaxPacketSize = 4096;
static constexpr int ProtcolVersion = 1;

struct Header {
    explicit Header(int id = 0, std::uint64_t seqId = 0);
    int id;
    std::uint64_t seqId;

    template <class Archive>
    void serialize(Archive & ar)
    {
        ar(id);
        ar(seqId);
    }
    bool operator == (Header const & rhs) const;
};

struct Entity {
    Entity(int id = 0, int type = 0, int state = 0, float x = 0.0f, float y = 0.0f);
    int id;
    int type;
    int state;
    float x;
    float y;

    template <class Archive>
    void serialize(Archive & ar)
    {
        ar(id, type, state, x, y);
    }
    bool operator == (Entity const & rhs) const;
};

struct Event {
    Event(int from = 0, int type = 0);
    int from;
    int type;

    template <class Archive>
    void serialize(Archive & ar)
    {
        ar(from, type);
    }
    bool operator == (Event const & rhs) const;
};

template<typename T>/* T == EVENT OR ENTITY */
struct Packet {
    Header h;
    std::vector<T> elements;
    template <class Archive>
    void serialize(Archive & ar)
    {
        ar(h, elements);
    }
    bool operator == (Packet const & rhs) const {
        return this->h == rhs.h && this->elements == rhs.elements;
    }
};

template<typename T>
Packet<T> extract(char *from, std::size_t s) {
    std::stringstream ss;
    ss.write(from, s);
    Packet<T> obj;
    {
        cereal::PortableBinaryInputArchive ia(ss);
        ia(obj);
    }
    return obj;
}

template<typename T>
std::string transform(Packet<T> const & toTransform) {
    std::stringstream ss;
    {
        cereal::PortableBinaryOutputArchive oa(ss);
        oa(toTransform);
    }
    return ss.str();
}

}
}
#endif //RTYPE_RTYPEPROTOCOL_H
