#include "Game.h"
using ge::Velocity;
using ge::Position;
using ge::Sprite;
using ge::Collider;
using ge::Ia;

Game::Game()
{
}

Game::~Game()
{
  
}

void Game::setGameInfo(rtype::protocol_tcp::GameInfo const &t_gi)
{
	this->gi_ = t_gi;
}

rtype::protocol_tcp::GameInfo const & Game::getGameInfo()
{
	return (this->gi_);
}

void Game::CreatePlayer()
{
	std::unique_ptr<GameObject> g = std::make_unique<GameObject>();

	g->AddComponent<Position>(Vector2f(0, 300));
	g->AddComponent<Velocity>(Vector2f(0,0));
	g->AddComponent<Collider>(Vector2f(300, 0), Vector2f(60, 60), "Player");
	g->id = this->players.size();
	this->players.push_back(std::move(g));
}

void Game::Update()
{
	while (lt.Update())
	{
		for (auto const & it : players)
		{
			it->GetComponent<Position>()->UpdatePos(it->GetComponent<Velocity>()->getVel(), 800, 600, 60);
			it->GetComponent<Velocity>()->UpdateVel(1.1f);
		}
	}
}