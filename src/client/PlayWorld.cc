#include "PlayWorld.h"
using ge::Velocity;
using ge::Position;
using ge::Sprite;
using ge::Collider;
using ge::Ia;

PlayWorld::PlayWorld()
{
	iaLoader_ = std::make_unique<loadIa>("resources/ai", 1920, 1080);
}

void PlayWorld::CreatePlayer(Vector2f const & t_position, std::string const & t_textureName, Vector2f const & t_velocity)
{
	std::unique_ptr<GameObject> g = std::make_unique<GameObject>();

	g->AddComponent<Position>(t_position);
	g->AddComponent<Velocity>(t_velocity);
	g->AddComponent<Sprite>(t_textureName, 2);
	g->AddComponent<Collider>(t_position,Vector2f(60, 60),"Player");
	this->players.push_back(std::move(g));
}

void PlayWorld::CreateEnnemy(std::string const & t_textureName, const int t_id, const int x, const int y)
{
	std::unique_ptr<GameObject> g = std::make_unique<GameObject>();

	std::shared_ptr<IArtificialIntelligence> ia = iaLoader_->getIa(t_id);
	ia->setPosition({x, y});

	g->AddComponent<Ia>(ia);
	g->AddComponent<Position>(Vector2f(x, y));
	g->AddComponent<ge::Animator>();
	auto animator = g->GetComponent<ge::Animator>();
	ge::Animation anim;
	anim.priority = 2;
	for (uint32_t i = 1; i < 5; ++i) {
		anim.sprites.push_back(g->GetComponent<Ia>()->ia->getName() + std::to_string(i));
	}
	animator->AddAnimation("idle", anim);
	animator->SetAnimation("idle");
	g->AddComponent<Collider>(Vector2f(x, y), Vector2f(64,64), "Player");
	this->ennemy.push_back(std::move(g));
}


void PlayWorld::CreateShoot(Vector2f const & t_position)
{
	std::unique_ptr<GameObject> g = std::make_unique<GameObject>();

	g->AddComponent<Position>(t_position);
	g->AddComponent<Sprite>("Shoot", 2);
	g->AddComponent<Collider>(t_position, Vector2f(30, 15), "Player Shoot");
	this->projectiles.push_back(std::move(g));
}

void PlayWorld::CreateEnnemyShoot(Vector2f const & t_position, std::string const & t_textureName)
{
	std::unique_ptr<GameObject> g = std::make_unique<GameObject>();

	g->AddComponent<Position>(t_position);
	g->AddComponent<Sprite>(t_textureName, 2);
	g->AddComponent<Collider>(t_position, Vector2f(30, 15), "Player Shoot");
	this->ennemy_projectiles.push_back(std::move(g));
}
