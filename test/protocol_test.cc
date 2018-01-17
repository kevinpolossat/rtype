//
// Created by Kévin POLOSSAT on 16/01/2018.
//


#include "protocol.h"
#include "gtest/gtest.h"

#include <sstream>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

TEST(Serialization, ProtocolQueryList) {
    rtype::protocol_tcp::QueryList ql;
    std::stringstream ss;
    cereal::PortableBinaryOutputArchive oa(ss);

    oa(ql);
    cereal::PortableBinaryInputArchive ia(ss);
    rtype::protocol_tcp::QueryList ql2;
    rtype::protocol_tcp::TCPHeader header;
    ia(header);
    ia(ql2);
    ASSERT_EQ(header.pId, rtype::protocol_tcp::LIST_GAME);
    ASSERT_EQ(ql, ql2);
}

TEST(Serialization, ProtocolQueryListAnswer) {
    rtype::protocol_tcp::QueryListAnswer qla;
    qla.value.push_back(rtype::protocol_tcp::GameInfo("toto.txt", 1, 3, std::vector<std::string>{"tata", "titi"}));

    std::stringstream ss;
    cereal::PortableBinaryOutputArchive oa(ss);

    oa(qla);
    cereal::PortableBinaryInputArchive ia(ss);
    rtype::protocol_tcp::QueryListAnswer qla2;
    rtype::protocol_tcp::TCPHeader header;
    ia(header);
    ia(qla2);
    ASSERT_EQ(header.pId, rtype::protocol_tcp::LIST_ANSWER);
    ASSERT_EQ(qla, qla2);
}

TEST(Serialization, ProtocolCreateGame) {
    rtype::protocol_tcp::QueryCreateGame qcg;
    qcg.value = {"toto.txt", "tata", 3};

    std::stringstream ss;
    cereal::PortableBinaryOutputArchive oa(ss);

    oa(qcg);
    cereal::PortableBinaryInputArchive ia(ss);
    rtype::protocol_tcp::QueryCreateGame qcg2;
    rtype::protocol_tcp::TCPHeader header;
    ia(header);
    ia(qcg2);
    ASSERT_EQ(header.pId, rtype::protocol_tcp::CREATE_GAME);
    ASSERT_EQ(qcg, qcg2);
}

TEST(Serialization, ProtocolAnswerCreateGame) {
    rtype::protocol_tcp::AnswerCreateGame acg;
    acg.statusOrId = 99;

    std::stringstream ss;
    cereal::PortableBinaryOutputArchive oa(ss);

    oa(acg);
    cereal::PortableBinaryInputArchive ia(ss);
    rtype::protocol_tcp::AnswerCreateGame acg2;
    rtype::protocol_tcp::TCPHeader header;
    ia(header);
    ia(acg2);
    ASSERT_EQ(header.pId, rtype::protocol_tcp::CREATE_GAME_ANSWER);
    ASSERT_EQ(acg, acg2);
}

TEST(Serialization, ProtocolQueryJoinGame) {
    rtype::protocol_tcp::QueryJoinGame qjg;
    qjg.value = {99, "titi"};

    std::stringstream ss;
    cereal::PortableBinaryOutputArchive oa(ss);

    oa(qjg);
    cereal::PortableBinaryInputArchive ia(ss);
    rtype::protocol_tcp::QueryJoinGame qjg2;
    rtype::protocol_tcp::TCPHeader header;
    ia(header);
    ia(qjg2);
    ASSERT_EQ(header.pId, rtype::protocol_tcp::JOIN_GAME);
    ASSERT_EQ(qjg, qjg2);
}

TEST(Serialization, ProtocolAnswerJoinGame) {
    rtype::protocol_tcp::AnswerJoinGame ajg;
    ajg.value = rtype::protocol_tcp::ok;

    std::stringstream ss;
    cereal::PortableBinaryOutputArchive oa(ss);

    oa(ajg);
    cereal::PortableBinaryInputArchive ia(ss);
    rtype::protocol_tcp::AnswerJoinGame ajg2;
    rtype::protocol_tcp::TCPHeader header;
    ia(header);
    ia(ajg2);
    ASSERT_EQ(header.pId, rtype::protocol_tcp::JOIN_GAME_ANSWER);
    ASSERT_EQ(ajg, ajg2);
}

TEST(Serialization, ProtocolGameState) {
    rtype::protocol_tcp::GameState gs;
    gs.value = std::vector<std::string>{"tata", "toto", "titi"};

    std::stringstream ss;
    cereal::PortableBinaryOutputArchive oa(ss);

    oa(gs);
    cereal::PortableBinaryInputArchive ia(ss);
    rtype::protocol_tcp::GameState gs2;
    rtype::protocol_tcp::TCPHeader header;
    ia(header);
    ia(gs2);
    ASSERT_EQ(header.pId, rtype::protocol_tcp::GAME_STATE);
    ASSERT_EQ(gs, gs2);
}

TEST(Serialization, ProtocolGameStart) {
    rtype::protocol_tcp::GameStart gs;
    gs.value = {"localhost", "424242"};

    std::stringstream ss;
    cereal::PortableBinaryOutputArchive oa(ss);

    oa(gs);
    cereal::PortableBinaryInputArchive ia(ss);
    rtype::protocol_tcp::GameStart gs2;
    rtype::protocol_tcp::TCPHeader header;
    ia(header);
    ia(gs2);
    ASSERT_EQ(header.pId, rtype::protocol_tcp::GAME_START);
    ASSERT_EQ(gs, gs2);
}