#ifndef GAME_H
#define GAME_H

#include <chrono>
#include "TcpProtocol.h"
#include "../client/GameEngine/Entity/Component.h"
#include "../client/GameEngine/LoopTimer.h"
#include "../loadlib/LoadIa.hpp"
using ge::Vector2f;
using ge::GameObject;
class Game {
public:
	static constexpr uint32_t width = 1920;
	static constexpr uint32_t height = 1080;

	Game();
	~Game() = default;

	void setGameInfo(rtype::protocol_tcp::GameInfo const &t_gi);
	rtype::protocol_tcp::GameInfo const & getGameInfo();
	void CreatePlayer();
	void CreateShoot(Vector2f const & t_position);
	void CreateEnnemy(int id);
	void CreateEnnemyShoot(Vector2f const & t_position, Vector2f const & t_velocity);
	void Update();


	std::vector<std::unique_ptr<GameObject>> 		players;
	std::vector<std::unique_ptr<GameObject>> 		projectiles;
	std::vector<std::unique_ptr<GameObject>> 		ennemy;
	std::vector<std::unique_ptr<GameObject>> 		ennemy_projectiles;
	ge::LoopTimer lt;
	std::chrono::time_point<std::chrono::high_resolution_clock> time_;
private:
	rtype::protocol_tcp::GameInfo gi_;
	std::unique_ptr<loadIa>			iaLoader_;

};
#endif
