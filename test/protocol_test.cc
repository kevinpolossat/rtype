//
// Created by Kévin POLOSSAT on 16/01/2018.
//

#include "RtypeProtocol.h"
#include "gtest/gtest.h"

#include <iostream>
#include <sstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

TEST(Serialization, ProtocolQueryList) {
    rtype::protocol_tcp::QueryList ql;
    std::stringstream ss;
    {
        cereal::JSONOutputArchive oa(ss);
        oa(ql);
    }
    rtype::protocol_tcp::QueryList ql2;
    {
        cereal::JSONInputArchive ia(ss);
        ia(ql2);
    }
    ASSERT_EQ(ql, ql2);
}

TEST(Serialization, ProtocolQueryListAnswer) {
    rtype::protocol_tcp::AnswerList qla;
    qla.value.push_back(rtype::protocol_tcp::GameInfo("toto.txt", 1, 3, std::vector<std::string>{"tata", "titi"}));

    std::stringstream ss;
    {
        cereal::JSONOutputArchive oa(ss);
        oa(qla);
    }
    rtype::protocol_tcp::AnswerList qla2;
    {
        cereal::JSONInputArchive ia(ss);
        ia(qla2);
    }
    ASSERT_EQ(qla, qla2);
}

TEST(Serialization, ProtocolCreateGame) {
    rtype::protocol_tcp::QueryCreateGame qcg;
    qcg.value = {"toto.txt", "tata", 3, "4242"};

    std::stringstream ss;
    {
        cereal::JSONOutputArchive oa(ss);
        oa(qcg);
    }

    rtype::protocol_tcp::QueryCreateGame qcg2;
    {
        cereal::JSONInputArchive ia(ss);
        ia(qcg2);
    }
    ASSERT_EQ(qcg, qcg2);
}

TEST(Serialization, ProtocolAnswerCreateGame) {
    rtype::protocol_tcp::AnswerCreateGame acg;
    acg.statusOrId = 99;

    std::stringstream ss;
    {
        cereal::JSONOutputArchive oa(ss);
        oa(acg);
    }
    rtype::protocol_tcp::AnswerCreateGame acg2;
    {
        cereal::JSONInputArchive ia(ss);
        ia(acg2);
    }
    ASSERT_EQ(acg, acg2);
}

TEST(Serialization, ProtocolQueryJoinGame) {
    rtype::protocol_tcp::QueryJoinGame qjg;
    qjg.value = {99, "titi", "4242"};

    std::stringstream ss;

    {
        cereal::JSONOutputArchive oa(ss);
        oa(qjg);
    }
    rtype::protocol_tcp::QueryJoinGame qjg2;
    {
        cereal::JSONInputArchive ia(ss);
        ia(qjg2);
    }
    ASSERT_EQ(qjg, qjg2);
}

TEST(Serialization, ProtocolAnswerJoinGame) {
    rtype::protocol_tcp::AnswerJoinGame ajg;
    ajg.value = rtype::protocol_tcp::ok;

    std::stringstream ss;
    {
        cereal::JSONOutputArchive oa(ss);
        oa(ajg);
    }
    rtype::protocol_tcp::AnswerJoinGame ajg2;
    {
        cereal::JSONInputArchive ia(ss);
        ia(ajg2);
    }
    ASSERT_EQ(ajg, ajg2);
}

TEST(Serialization, ProtocolGameState) {
    rtype::protocol_tcp::GameState gs;
    gs.value = std::vector<std::string>{"tata", "toto", "titi"};

    std::stringstream ss;
    {
        cereal::JSONOutputArchive oa(ss);
        oa(gs);
    }
    rtype::protocol_tcp::GameState gs2;
    {
        cereal::JSONInputArchive ia(ss);
        ia(gs2);
    }
    ASSERT_EQ(gs, gs2);
}

TEST(Serialization, ProtocolGameStart) {
    rtype::protocol_tcp::GameStart gs;
    gs.value = {"424242"};

    std::stringstream ss;
    {
        cereal::JSONOutputArchive oa(ss);
        oa(gs);
    }
    rtype::protocol_tcp::GameStart gs2;
    {
        cereal::JSONInputArchive ia(ss);
        ia(gs2);
    }
    ASSERT_EQ(gs, gs2);
}

TEST(Serialization, ProtocolHeader) {
    rtype::protocol_tcp::Header h = {rtype::protocol_tcp::ProtocolId::LIST_ANSWER};
    rtype::protocol_tcp::Header h2;
    std::stringstream ss;
    {
        cereal::JSONOutputArchive oa(ss);
        oa(h);
    }
    {
        cereal::JSONInputArchive ia(ss);
        ia(h2);
    }
    ASSERT_EQ(h, h2);
}

TEST(Serialization, ExtractAndTransform) {
    rtype::protocol_tcp::QueryList ql;
    auto s = rtype::protocol_tcp::transform(ql);
    auto p = s.find("\r\n");
    auto hs = s.substr(0, p);
    auto qls = s.substr(p + 2/*discard \r\n*/);
    qls.pop_back();
    qls.pop_back();
    auto hql = rtype::protocol_tcp::extract<rtype::protocol_tcp::Header>(hs);
    auto ql2 = rtype::protocol_tcp::extract<rtype::protocol_tcp::QueryList>(qls);
    rtype::protocol_tcp::Header h2 = {rtype::protocol_tcp::LIST_GAME};
    ASSERT_EQ(hql, h2);
    ASSERT_EQ(ql, ql2);
}

TEST(Serialization, ProtocolLeaveGame) {
    rtype::protocol_tcp::QueryLeaveGame qlg = {42};
    rtype::protocol_tcp::QueryLeaveGame qlg2;
    std::stringstream ss;
    {
        cereal::JSONOutputArchive oa(ss);
        oa(qlg);
    }
    {
        cereal::JSONInputArchive ia(ss);
        ia(qlg2);
    }
    ASSERT_EQ(qlg, qlg2);
}
