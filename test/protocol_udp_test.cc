//
// Created by Kévin POLOSSAT on 23/01/2018.
//

#include "UdpProtocol.h"
#include "gtest/gtest.h"

#include <random>

TEST(Serialization, ProtocolUdpEvent) {
    rtype::protocol_udp::Packet<rtype::protocol_udp::Event> pe1;
    for (int i = 0; i < 100; ++i) {
        pe1.elements.push_back(rtype::protocol_udp::Event(i, i));
    }
    pe1.h.id = 42;
    auto s = rtype::protocol_udp::transform(pe1);
    std::array<char, rtype::protocol_udp::MaxPacketSize> a_;
    std::copy(s.begin(), s.end(), a_.begin());
    auto pe2 = rtype::protocol_udp::extract<rtype::protocol_udp::Event>(a_, s.size());
    ASSERT_EQ(pe1, pe2);

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 1000);
    rtype::protocol_udp::Packet<rtype::protocol_udp::Event> pe3;
    for (int i = 0; i < 100; ++i) {
        pe3.elements.push_back(rtype::protocol_udp::Event(uniform_dist(e1), uniform_dist(e1)));
    }
    auto s2 = rtype::protocol_udp::transform(pe3);
    std::array<char, rtype::protocol_udp::MaxPacketSize> a_2;
    std::copy(s2.begin(), s2.end(), a_2.begin());
    auto pe4 = rtype::protocol_udp::extract<rtype::protocol_udp::Event>(a_2, s.size());
    ASSERT_EQ(pe3, pe4);
}

TEST(Serialization, ProtocolUdpEntity) {
    rtype::protocol_udp::Packet<rtype::protocol_udp::Entity> pe1;
    for (int i = 0; i < 100; ++i) {
        pe1.elements.push_back(rtype::protocol_udp::Entity(777, 3232, 42, 0.5, 0.7));
    }
    pe1.h.id = 42;
    auto s = rtype::protocol_udp::transform(pe1);
    std::array<char, rtype::protocol_udp::MaxPacketSize> a_;
    std::copy(s.begin(), s.end(), a_.begin());
    auto pe2 = rtype::protocol_udp::extract<rtype::protocol_udp::Entity>(a_, s.size());
    ASSERT_EQ(pe1, pe2);

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_distInt(1, 1000);
    std::uniform_int_distribution<float> uniform_distFloat(0.0, 42.0);
    rtype::protocol_udp::Packet<rtype::protocol_udp::Entity> pe3;
    for (int i = 0; i < 100; ++i) {
        pe3.elements.push_back(
                rtype::protocol_udp::Entity(
                        uniform_distInt(e1),
                        uniform_distInt(e1),
                        uniform_distInt(e1),
                        uniform_distFloat(e1),
                        uniform_distFloat(e1)));
    }
    auto s2 = rtype::protocol_udp::transform(pe3);
    std::array<char, rtype::protocol_udp::MaxPacketSize> a_2;
    std::copy(s2.begin(), s2.end(), a_2.begin());
    auto pe4 = rtype::protocol_udp::extract<rtype::protocol_udp::Entity>(a_2, s.size());
    ASSERT_EQ(pe3, pe4);
}
