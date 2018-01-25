
#include <vector>
#include <iostream>
#include "GameEngine.h"
#include "client/States/IntroState.h"
#include "client/States/PlayState.h"
#include "Entity/Component.h"
#include "client/States/CreateState.h"
#include "client/States/LoginState.h"
#include "client/States/JoinState.h"
#include "NetworkManager.h"
#include "TCPNonBlockingCommunication.h"
#include "UDPNonBlockingCommunication.h"
#include "TcpProtocol.h"
#include	"MenuValue.h"

int main() {
	ge::GameEngine gameEngine;

    ge::network::NetworkManager nm;
	auto tcpConnection = std::make_shared<ge::network::TCPNonBlockingCommunication>();
	if (!tcpConnection->open("localhost"/*SERVER HOSTNAME*/, "4242")) {
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
	//	std::cout << "port=" << udp->getPort() << std::endl;
		std::cout << a.value.size() << std::endl;
		if (a.value.empty()) {
			ge::MenuValue &v = ge::MenuValue::Instance();
			v.games.clear();
			v.games.push_back("pas de game");
		}
		else {
			ge::MenuValue &v = ge::MenuValue::Instance();
			v.games.clear();
			for (auto it : a.value)
				v.games.push_back(it.filename);
		}
	});
	tcpConnection->addHandle(
		rtype::protocol_tcp::CREATE_GAME_ANSWER,
		[](std::string const & json) {
	}
	);
	tcpConnection->addHandle(
		rtype::protocol_tcp::JOIN_GAME_ANSWER,
		[](std::string const & json) {
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
		udp->addDest("localhost"/* SERVER HOST NAME*/, gs.value.port);
	}
	);
	ge::MenuValue &v = ge::MenuValue::Instance();
	v.tcpConnection = tcpConnection;
	v.Port = udp->getPort();
	rtype::protocol_tcp::QueryList ql;
	tcpConnection->sendToServer<rtype::protocol_tcp::QueryList>(ql);
	gameEngine.AddCommunication(tcpConnection);
	gameEngine.AddCommunication(udp);
	if (gameEngine.Init("R-Type", 800, 600, false)) {
		gameEngine.AddState("Intro", std::make_shared<IntroState>());
		gameEngine.AddState("Play", std::make_shared<PlayState>(udp));
		gameEngine.AddState("Create", std::make_shared<CreateState>());
		gameEngine.AddState("Login", std::make_shared<LoginState>());
		gameEngine.AddState("Join", std::make_shared<JoinState>());

		gameEngine.Run("Intro");
	}
	return 0;
}
