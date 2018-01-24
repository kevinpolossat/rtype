#ifndef GAME_H
#define GAME_H

#include "TcpProtocol.h"
#include "../client/GameEngine/Entity/Component.h"
using ge::Vector2f;
using ge::GameObject;
class Game
{
	public:
		Game();
		~Game();
		void setGameInfo(rtype::protocol_tcp::GameInfo const &t_gi);
		rtype::protocol_tcp::GameInfo const & getGameInfo();
		void CreatePlayer();
		void Update();
		std::vector<std::unique_ptr<GameObject>> 		players;
		std::vector<std::unique_ptr<GameObject>> 		projectiles;
		std::vector<std::unique_ptr<GameObject>> 		ennemy;
	private:
		rtype::protocol_tcp::GameInfo gi_;
};
#endif
