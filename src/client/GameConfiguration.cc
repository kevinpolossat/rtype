//
// Created by Kévin POLOSSAT on 25/01/2018.
//

#include <fstream>
#include <serialization/cereal/archives/json.hpp>
#include "GameConfiguration.h"

GameConfiguration::GameConfiguration() {
    std::ifstream ifs("resources/configuration.json");
    if (ifs) {
        try {
            cereal::JSONInputArchive ar(ifs);
            ar(cereal::make_nvp("domain", domain_), cereal::make_nvp("port", port_));
        }
        catch (...) {}
    }
}

const std::string &GameConfiguration::domain() const {
    return domain_;
}

const std::string &GameConfiguration::port() const {
    return port_;
}
