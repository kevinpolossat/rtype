/*
#include <vector>
#include <iostream>
#include "GameEngine.h"
#include "client/States/IntroState.h"
#include "client/States/PlayState.h"
#include "Entity/Component.h"
#include    "client/States/CreateState.h"
#include    "client/States/LoginState.h"
#include "client/States/JoinState.h"

*/

#include <iostream>
#include "NetworkManager.h"
#include "TCPNonBlockingCommunication.h"
#include "RtypeProtocol.h"

int main() {/*
	ge::GameEngine gameEngine;
	if (gameEngine.Init("R-Type", 800, 600, false)) {
		gameEngine.AddState("Intro", std::make_shared<IntroState>());
		gameEngine.AddState("Play", std::make_shared<PlayState>());
		gameEngine.AddState("Create", std::make_shared<CreateState>());
		gameEngine.AddState("Login", std::make_shared<LoginState>());
		gameEngine.AddState("Join", std::make_shared<JoinState>());

		gameEngine.Run("Intro");
	}*/
	// GAMELOOP
    rtype::network::NetworkManager nm;
    auto tcpConnection = std::make_shared<rtype::network::TCPNonBlockingCommunication>();
    if (!tcpConnection->open("localhost", "4242")) {
        std::cout << "can't connect to server" << std::endl;
                  return 0;
    }
/*    tcpConnection->addHandle(
            rtype::protocol_tcp::LIST_ANSWER,
            [](std::string const & json){
                std::cout << "HANDLING[" << json << "]" << std::endl;
                auto a = rtype::protocol_tcp:make:extract<rtype::protocol_tcp::AnswerList>(json);
    });*/
    nm.addCommuncation(tcpConnection);
    rtype::protocol_tcp::QueryList ql;
	for (;;) {
//        nm.handleRecvEvent();
		// process
        std::string s;
        std::cin >> s;
        tcpConnection->sendToServer<rtype::protocol_tcp::QueryList>(ql);
        nm.handleSendEvent();
	}
	return 0;
}
