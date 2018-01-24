#ifndef GAME_H
#define GAME_H

#include <chrono>
#include "TcpProtocol.h"
#include "../client/GameEngine/Entity/Component.h"
#include "../client/GameEngine/LoopTimer.h"
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
		void CreateShoot(Vector2f const & t_position);
		void Update();
		std::vector<std::unique_ptr<GameObject>> 		players;
		std::vector<std::unique_ptr<GameObject>> 		projectiles;
		std::vector<std::unique_ptr<GameObject>> 		ennemy;
		ge::LoopTimer lt;
		std::chrono::time_point<std::chrono::high_resolution_clock> time_;
	private:
		rtype::protocol_tcp::GameInfo gi_;
	
};
#endif
