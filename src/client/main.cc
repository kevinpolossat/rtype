
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
	auto tcpConnection = std::make_shared<ge::network::TCPNonBlockingCommunication>();
	if (!tcpConnection->open("localhost"/*SERVER HOSTNAME*/, "4242")) {
		std::cout << "can't connect to server" << std::endl;
		return 0;
	}
	ge::network::UDPNonBlockingCommuncation udp;
	auto b = udp.open();
	if (!b) {
		std::cout << "FAILED TO OPEN UDP" << std::endl;
	}
	tcpConnection->addHandle(
		rtype::protocol_tcp::LIST_ANSWER,
		[tcpConnection, &udp](std::string const & json) {
		std::cout << "HANDLE LIST HANDLING[" << json << "]" << std::endl;
		auto a = rtype::protocol_tcp::extract<rtype::protocol_tcp::AnswerList>(json);
		std::cout << "port=" << udp.getPort() << std::endl;
		if (a.value.empty()) {
			rtype::protocol_tcp::QueryCreateGame cg;
			cg.value.fileName = "toto.txt";
			cg.value.nbPlayerMax = 1;
			cg.value.playerName = "nonmame";
			cg.value.port = udp.getPort();
			tcpConnection->sendToServer(cg);
		}
		else {
			rtype::protocol_tcp::QueryJoinGame jg;
			jg.value.port = udp.getPort();
			jg.value.playerName = "nino";
			jg.value.gameId = 1;
			tcpConnection->sendToServer(jg);
		}
	});
	tcpConnection->addHandle(
		rtype::protocol_tcp::CREATE_GAME_ANSWER,
		[](std::string const & json) {
		std::cout << "HANDLE CREATE HANDLING[" << json << "]" << std::endl;
	}
	);
	tcpConnection->addHandle(
		rtype::protocol_tcp::JOIN_GAME_ANSWER,
		[](std::string const & json) {
		std::cout << "HANDLE JOIN HANDLING[" << json << "]" << std::endl;
	}
	);
	tcpConnection->addHandle(
		rtype::protocol_tcp::GAME_STATE,
		[](std::string const & json) {
		std::cout << "HANDLE STATE HANDLING[" << json << "]" << std::endl;
	}
	);
	tcpConnection->addHandle(
		rtype::protocol_tcp::GAME_START,
		[&udp](std::string const & json) {
		std::cout << "HANDLE START HANDLING[" << json << "]" << std::endl;
		auto gs = rtype::protocol_tcp::extract<rtype::protocol_tcp::GameStart>(json);
		auto p = gs.value.port;
		auto idPlayer = gs.value.id; // ID TO MATCH THE GAME ENGINE ID SEND IT IN EVENTS
		udp.addDest("localhost"/* SERVER HOST NAME*/, gs.value.port);
		//gameEngine.PushState("Play");
		udp.addHandle([](void *data, std::size_t nbyte) {
			auto p = rtype::protocol_udp::extract<rtype::protocol_udp::Entity/*recieving event only*/>(static_cast<char *>(data), nbyte);
			//std::cout << "HANDLING PACKET WITH SEQID=" << p.h.seqId << std::endl;
			for (auto it : p.elements)
			{
				//std::cout << "ID=" << it.id << " Type=" << it.type << " State=" << it.state << " X=" << it.x << " Y=" << it.y << std::endl;
			}
			auto seqId = p.h.seqId; // STORE SEQID TO TREAT ONLY THE MOST RECENT PACKET
		});
		std::vector<rtype::protocol_udp::Event> events;
		events.emplace_back(idPlayer, 0);
		events.emplace_back(idPlayer, 1);
		for (;;) {
			udp.recv(); // DO NOT CALL DIRECRTY USE NETWORK MANAGEr
			udp.notifyAll(events);
			udp.send(); // DO NOT CALL DIRECRTY USE NETWORK MANAGEr
		}
		udp.close(); // DO NOT CALL DIRECRTY USE NETWORK MANAGEr
	}
	);
	rtype::protocol_tcp::QueryList ql;
	tcpConnection->sendToServer<rtype::protocol_tcp::QueryList>(ql);
	gameEngine.AddCommunication(tcpConnection);
	if (gameEngine.Init("R-Type", 800, 600, false)) {
		gameEngine.AddState("Intro", std::make_shared<IntroState>());
		gameEngine.AddState("Play", std::make_shared<PlayState>());
		gameEngine.AddState("Create", std::make_shared<CreateState>());
		gameEngine.AddState("Login", std::make_shared<LoginState>());
		gameEngine.AddState("Join", std::make_shared<JoinState>());

		gameEngine.Run("Intro");
	}
	for (;;) {
        //nm.handleRecvEvent();
        std::string s;
        std::cout << ">" << std::endl;
        std::cin >> s;
        //nm.handleSendEvent();
	}
	return 0;
}
