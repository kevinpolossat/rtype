#ifndef PLAYWORLD_H_
#define PLAYWORLD_H_

#include "AWorld.h"
#include "ia/IArtificialIntelligence.hpp"
#include "../../loadlib/LoadIa.hpp"

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
	void CreateShoot(Vector2f const & t_position);
	void CreateEnnemy(std::string const & t_textureName, const int t_id);


	std::vector<std::unique_ptr<GameObject>> 		players;
	std::vector<std::unique_ptr<GameObject>> 		projectiles;
	std::vector<std::unique_ptr<GameObject>> 		ennemy;

	private:
		loadIa			*iaLoader_;
};

#endif /* PLAYWORLD_H_ */
