//
// Created by Kévin POLOSSAT on 25/01/2018.
//

#ifndef RTYPE_GAMECONFIGURATION_H
#define RTYPE_GAMECONFIGURATION_H

#include <string>

class GameConfiguration {
public:
    GameConfiguration();
    GameConfiguration(GameConfiguration const & other) = default;
    GameConfiguration(GameConfiguration && other) = default;
    GameConfiguration & operator = (GameConfiguration const & other) = default;
    GameConfiguration & operator = (GameConfiguration && other) = default;
    ~GameConfiguration() = default;

    std::string const & domain() const;
    std::string const & port() const;

private:
    std::string domain_ = "localhost";
    std::string port_ = "4242";
};


#endif //RTYPE_GAMECONFIGURATION_H
