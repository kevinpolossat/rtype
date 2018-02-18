#include <vector>
#include <iostream>

#include "client/States/SettingsState.h"
#include "client/States/IntroState.h"
#include "client/States/PlayState.h"
#include "client/States/CreateState.h"
#include "client/States/LoginState.h"
#include "client/States/JoinState.h"
#include "client/States/EndState.h"
#include "client/States/WaitingState.h"

int main()
{
	ge::GameEngine gameEngine;
	ge::network::NetworkManager nm;

	auto tcpConnection = std::make_shared<ge::network::TCPNonBlockingCommunication>();
	GameConfiguration conf = MenuValue::Instance().getGameConfiguration();
	if (!tcpConnection->open(conf.domain(), conf.port())) {
		std::cout << "can't connect to server" << std::endl;
		return 0;
	}
	std::shared_ptr<ge::network::UDPNonBlockingCommuncation> udp = std::make_shared<ge::network::UDPNonBlockingCommuncation>();
	auto b = udp->open();
	if (!b) {
		std::cout << "FAILED TO OPEN UDP" << std::endl;
	}
	tcpConnection->addHandle(
			rtype::protocol_tcp::LIST_ANSWER,
			[tcpConnection, &udp](std::string const & json) {
				auto a = rtype::protocol_tcp::extract<rtype::protocol_tcp::AnswerList>(json);
				if (a.value.empty()) {
					MenuValue &v = MenuValue::Instance();
					v.gi.clear();
					v.games.clear();
					//v.games.push_back("pas de game");
				}
				else {
					MenuValue &v = MenuValue::Instance();
					v.games.clear();
					v.gi.clear();
					for (auto it : a.value)
					{
						v.gi.push_back(it);
						v.games.push_back(it.playersNames[0] + " " + std::to_string(it.playersNames.size()) + "/" + std::to_string(it.nbPlayerMax));
					}
				}
			});
	tcpConnection->addHandle(
			rtype::protocol_tcp::CREATE_GAME_ANSWER,
			[](std::string const & json) {
			}
	);
	tcpConnection->addHandle(
			rtype::protocol_tcp::JOIN_GAME_ANSWER,
			[&gameEngine](std::string const & json) {
				gameEngine.ChangeState("Waiting");
				std::cout << "JOIN" << std::endl;
			}
	);
	tcpConnection->addHandle(
			rtype::protocol_tcp::GAME_STATE,
			[](std::string const & json) {
			}
	);
	tcpConnection->addHandle(
			rtype::protocol_tcp::GAME_START,
			[&udp, &gameEngine](std::string const & json) {
				auto gs = rtype::protocol_tcp::extract<rtype::protocol_tcp::GameStart>(json);
				auto p = gs.value.port;
				gameEngine.playerID = gs.value.id;
				udp->addDest(conf.domain(), gs.value.port);
				gameEngine.ChangeState("Play");
			}
	);
	MenuValue &v = MenuValue::Instance();
	v.tcpConnection = tcpConnection;
	v.Port = udp->getPort();
	rtype::protocol_tcp::QueryList ql;
	tcpConnection->sendToServer<rtype::protocol_tcp::QueryList>(ql);
	gameEngine.AddCommunication(tcpConnection);
	gameEngine.AddCommunication(udp);
	if (gameEngine.Init("R-Type", gameEngine.GetResolutionsModes().front().x, gameEngine.GetResolutionsModes().front().y, true)) {
		gameEngine.AddState("Intro", std::make_shared<IntroState>());
		gameEngine.AddState("SettingsMenu", std::make_shared<SettingsState>(false));
		gameEngine.AddState("SettingsGame", std::make_shared<SettingsState>(true));
		gameEngine.AddState("Play", std::make_shared<PlayState>(udp));
		gameEngine.AddState("Create", std::make_shared<CreateState>());
		gameEngine.AddState("Login", std::make_shared<LoginState>());
		gameEngine.AddState("Join", std::make_shared<JoinState>());
		gameEngine.AddState("Waiting", std::make_shared<WaitingState>());
		gameEngine.AddState("End", std::make_shared<EndState>());
		gameEngine.SetDefaultState("Intro");
		gameEngine.Run("Intro");
	}
	return 0;
}
