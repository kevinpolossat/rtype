//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#include <thread>
#include "Launcher.h"
#include "Game.h"
#include "UDPNonBlockingCommunication.h"

bool rtype::Launcher::launch(std::shared_ptr<rtype::GameLobby> gl) {
    rtype::protocol_tcp::GameStart gs;
    auto udp = std::make_shared<ge::network::UDPNonBlockingCommuncation>(); // TODO PUT IN NETWORK MANAGER
    udp->open(/*default port 0*/);
    gs.value = {udp->getPort()};
    udp->addDests(gl->getIpAndPorts());
    udp->addHandle([](void *data, std::size_t nbyte) {
      static auto savedSeqId = 0;
        auto p = rtype::protocol_udp::extract<rtype::protocol_udp::Event/*recieving event only*/>(static_cast<char *>(data), nbyte);
        //std::cout << "HANDLING PACKET WITH SEQID=" << p.h.seqId << std::endl;
        auto seqId = p.h.seqId; // STORE SEQID TO TREAT ONLY THE MOST RECENT PACKET
         if (seqId > savedSeqId)
         {
           savedSeqId = seqId;
         }
        else
        {
          //discard
        }
    });
    gl->notifyAllGameStart(gs);
	
    auto t = std::thread([udp, gl]() 
	{ 
		Game g;

		g.setGameInfo(gl->getGameInfo());
		for (int i = 0; i < g.getGameInfo().nbPlayerMax; i++)
			g.CreatePlayer();
        for (;;) {
            udp->recv(); // DO NOT USE DIRECTLY USE NOTIFYALL AND NETWORK MANAGER
			std::vector<rtype::protocol_udp::Entity> es;
			for (auto const & it : g.players)
			{
				std::shared_ptr<ge::Position> p = it->GetComponent<ge::Position>();
				es.emplace_back(it->id,0, 0, p->getPos().x, p->getPos().y);
			}
            udp->notifyAll(es);
            udp->send(); // DO NOT USE DIRECTLY USE NOTIFYALL AND NETWORK MANAGER
        }
        udp->close(); // DO NOT USE DIRECTLY USE NOTIFYALL AND NETWORK MANAGER
    });
    t.detach();
    return true;
}
