//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#include <thread>
#include "Launcher.h"
#include "Game.h"
#include "UDPNonBlockingCommunication.h"
#include "Events.h"

bool rtype::Launcher::launch(std::shared_ptr<rtype::GameLobby> gl) 
{
	std::shared_ptr<Game> g = std::make_shared<Game>();

    rtype::protocol_tcp::GameStart gs;
    auto udp = std::make_shared<ge::network::UDPNonBlockingCommuncation>(); // TODO PUT IN NETWORK MANAGER
    udp->open(/*default port 0*/);
    gs.value = {udp->getPort()};
    udp->addDests(gl->getIpAndPorts());
    udp->addHandle([g](void *data, std::size_t nbyte) {
      static auto savedSeqId = 0;
        auto p = rtype::protocol_udp::extract<rtype::protocol_udp::Event>(static_cast<char *>(data), nbyte);
        auto seqId = p.h.seqId; 
		std::cout << "PACKET" << std::endl;

         if (seqId > savedSeqId)
         {
           savedSeqId = seqId;
		   std::cout << "ici" << std::endl;
			   for (auto & it : p.elements)
			   {
				   std::cout << "elements" << std::endl;
				   switch (static_cast<EVENTTYPE>(it.type))
				   {
				   case EVENTTYPE::PLAYERUP:
					   std::cout << "UP" << std::endl;
					   g->players[it.from]->GetComponent<ge::Velocity>()->m_pos.y -= 10;
					   break;
				   case EVENTTYPE::PLAYERDOWN:
					   std::cout << "DOWN" << std::endl;
					   g->players[it.from]->GetComponent<ge::Velocity>()->m_pos.y += 10;
					   break;
				   case EVENTTYPE::PLAYERRIGHT:
					   g->players[it.from]->GetComponent<ge::Velocity>()->m_pos.x += 10;
					   break;
				   case EVENTTYPE::PLAYERLEFT:
					   g->players[it.from]->GetComponent<ge::Velocity>()->m_pos.x -= 10;
					   break;
				   default:
					   break;
				   }
			   }
         }
        else
        {
          //discard
        }
    });
    gl->notifyAllGameStart(gs);
	
    auto t = std::thread([udp, gl, g]() 
	{ 

		g->setGameInfo(gl->getGameInfo());
		for (int i = 0; i < g->getGameInfo().nbPlayerMax; i++)
			g->CreatePlayer();
        for (;;) {
            udp->recv(); // DO NOT USE DIRECTLY USE NOTIFYALL AND NETWORK MANAGER
			g->Update();
			std::vector<rtype::protocol_udp::Entity> es;
			for (auto const & it : g->players)
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
