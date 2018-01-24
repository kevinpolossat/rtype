#ifndef PLAYWORLD_H_
#define PLAYWORLD_H_

#include <memory>
#include "AWorld.h"
#include "IArtificialIntelligence.hpp"
#include "loadlib/LoadIa.hpp"
using ge::Vector2f;
using ge::GameObject;

class PlayWorld : public ge::AWorld {
public:
	PlayWorld();
	PlayWorld(PlayWorld const & other) = delete;
	PlayWorld(PlayWorld && other) = delete;
	~PlayWorld() override = default;

	PlayWorld & operator=(PlayWorld const & other) = delete;
	PlayWorld & operator=(PlayWorld && other) = delete;


	void CreatePlayer(Vector2f const & t_position, Vector2f const & t_velocity = Vector2f(0,0));
	void CreatePlayer(Vector2f const & t_position, std::string const & t_textureName, Vector2f const & t_velocity = Vector2f(0, 0));
	void CreateShoot(Vector2f const & t_position, Vector2f const & t_velocity, std::string const & t_textureName);
	void CreateEnnemyShoot(Vector2f const & t_position, Vector2f const & t_velocity, std::string const & t_textureName);
	void CreateEnnemy(std::string const & t_textureName, const int t_id);


	std::vector<std::unique_ptr<GameObject>> 		players;
	std::vector<std::unique_ptr<GameObject>> 		projectiles;
	std::vector<std::unique_ptr<GameObject>> 		ennemy_projectiles;
	std::vector<std::unique_ptr<GameObject>> 		ennemy;

	private:
		std::unique_ptr<loadIa>			iaLoader_;
};

#endif /* PLAYWORLD_H_ */
