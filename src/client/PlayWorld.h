#ifndef PLAYWORLD_H_
#define PLAYWORLD_H_

#include "AWorld.h"
using ge::Vector2f;
using ge::GameObject;

class PlayWorld : public ge::AWorld {
public:
	PlayWorld() = default;
	PlayWorld(PlayWorld const & other) = delete;
	PlayWorld(PlayWorld && other) = delete;
	~PlayWorld() override = default;

	PlayWorld & operator=(PlayWorld const & other) = delete;
	PlayWorld & operator=(PlayWorld && other) = delete;
	

	void CreatePlayer(Vector2f const & t_position, Vector2f const & t_velocity = Vector2f(0,0));
	void CreatePlayer(Vector2f const & t_position, std::string const & t_textureName, Vector2f const & t_velocity = Vector2f(0, 0));
	void CreateShoot(Vector2f const & t_position, Vector2f const & t_velocity, std::string const & t_textureName);


	std::vector<std::unique_ptr<GameObject>> players;
	std::vector<std::unique_ptr<GameObject>> projectiles;
};

#endif /* PLAYWORLD_H_ */
