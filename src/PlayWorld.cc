#include "PlayWorld.h"

void PlayWorld::CreatePlayer(Vector2D const & t_position, Vector2D const & t_velocity)
{
	std::unique_ptr<GameObject> g = std::make_unique<GameObject>();

	g->AddComponent<Position>(t_position);
	g->AddComponent<Velocity>(t_velocity);
	g->AddComponent<Animator>();
	Animation walk;
	walk.priority = 1;
	walk.speed = 50;
	for (uint32_t i = 1; i <= 10; ++i) {
		walk.sprites.push_back("resources/knight/Walk (" + std::to_string(i) + ").png");
	}
	Animation attack;
	attack.priority = 1;
	attack.speed = 75;
	for (uint32_t i = 1; i <= 10; ++i) {
		attack.sprites.push_back("resources/knight/Attack (" + std::to_string(i) + ").png");
	}
	g->GetComponent<Animator>().AddAnimation("Walk", walk);
	g->GetComponent<Animator>().AddAnimation("Attack", attack);
	g->GetComponent<Animator>().SetAnimation("Walk");
	this->players.push_back(std::move(g));
}

void PlayWorld::CreatePlayer(Vector2D const & t_position, std::string const & t_textureName, Vector2D const & t_velocity)
{
	std::unique_ptr<GameObject> g = std::make_unique<GameObject>();

	g->AddComponent<Position>(t_position);
	g->AddComponent<Velocity>(t_velocity);
	g->AddComponent<Sprite>(t_textureName, 2);
	this->players.push_back(std::move(g));
}

void PlayWorld::CreateShoot(Vector2D const & t_position, Vector2D const & t_velocity, std::string const & t_textureName)
{
	std::unique_ptr<GameObject> g = std::make_unique<GameObject>();

	g->AddComponent<Position>(t_position);
	g->AddComponent<Velocity>(t_velocity);
	g->AddComponent<Sprite>(t_textureName, 2);
	this->projectiles.push_back(std::move(g));
}

