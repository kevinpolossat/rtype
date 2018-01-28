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
	  std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	  std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - g->time_);
        auto p = rtype::protocol_udp::extract<rtype::protocol_udp::Event>(static_cast<char *>(data), nbyte);
        auto seqId = p.h.seqId;

         if (seqId > savedSeqId)
         {
           savedSeqId = seqId;
			   for (auto & it : p.elements)
			   {
				   switch (it.type)
				   {
				   case static_cast<int>(EVENTTYPE::PLAYERUP):
					   g->players[it.from -1]->GetComponent<ge::Velocity>()->m_pos.y -= 10;
					   break;
				   case static_cast<int>(EVENTTYPE::PLAYERDOWN):
					   g->players[it.from - 1]->GetComponent<ge::Velocity>()->m_pos.y += 10;
					   break;
				   case static_cast<int>(EVENTTYPE::PLAYERRIGHT):
					   g->players[it.from - 1]->GetComponent<ge::Velocity>()->m_pos.x += 10;
					   break;
				   case static_cast<int>(EVENTTYPE::PLAYERLEFT):
					   g->players[it.from - 1]->GetComponent<ge::Velocity>()->m_pos.x -= 10;
					   break;
				   case static_cast<int>(EVENTTYPE::PLAYERSHOOT) :
					   if (static_cast<double>(ms.count() / 1000) > 0.3f) // Fire Rate 1 Shot every 0.5 sec
					   {
						   g->time_ = std::chrono::high_resolution_clock::now();
						   Vector2f newPos = g->players[it.from - 1]->GetComponent<ge::Position>()->getPos();
						   newPos.y += 30;
						   newPos.x += 90;
						   g->CreateShoot(newPos);
					   }
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

		bool endGame = true;
    while (endGame)
		{
			g->lt.Start();
			while (g->lt.Update())
			{
				udp->recv();
				std::vector<rtype::protocol_udp::Entity> es;

				if (g->players.size() == 0)
				{
					endGame = false;
					es.push_back({static_cast<int>(0), static_cast<int>(ENTITYTYPE::ENDGAME), 0, 0, 0});
				}
				else
				{
					g->Update();
					for (auto const & it : g->players)
					{
						std::shared_ptr<ge::Position> p = it->GetComponent<ge::Position>();
						es.push_back({static_cast<int>(it->id), static_cast<int>(ENTITYTYPE::PLAYER), 0, p->getPos().x, p->getPos().y});
					}
					for (auto const & it : g->ennemy)
					{
						std::shared_ptr<ge::Position> p = it->GetComponent<ge::Position>();
						es.push_back({static_cast<int>(it->id), static_cast<int>(ENTITYTYPE::ENNEMY), 0, p->getPos().x, p->getPos().y});
					}
					for (auto const & it : g->ennemy_projectiles)
					{
						std::shared_ptr<ge::Position> p = it->GetComponent<ge::Position>();
						es.push_back({static_cast<int>(it->id), static_cast<int>(ENTITYTYPE::ENNEMYSHOOT), 0, p->getPos().x, p->getPos().y});
					}
					for (auto const & it : g->projectiles)
					{
						std::shared_ptr<ge::Position> p = it->GetComponent<ge::Position>();
						es.push_back({static_cast<int>(it->id), static_cast<int>(ENTITYTYPE::PLAYERSHOOT), 0, p->getPos().x, p->getPos().y});
					}
				}
				udp->notifyAll(es);
				udp->send();
			}
    }
    udp->close();
		exit(0);
    });
    t.detach();
    return true;
}
