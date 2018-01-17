//
// Created by Kévin POLOSSAT on 16/01/2018.
//


#include "protocol.h"
#include "gtest/gtest.h"
#include "rapidjson/prettywriter.h"

using namespace rapidjson;

TEST_F(Serialization, SerializationProtocol_tests) {
    rtype::protocol_tcp::QueryList ql;
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);

    ql.serialize(sb);
    auto serialized = sb.GetString();
    std::cout << "serialized: " << serialized << std::endl;
}