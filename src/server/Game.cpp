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

void Game::CreateShoot(Vector2f const & t_position)
{
	std::unique_ptr<GameObject> g = std::make_unique<GameObject>();

	g->AddComponent<Position>(t_position);
	g->AddComponent<Velocity>(Vector2f(10,0));
	g->AddComponent<Collider>(t_position, Vector2f(30, 15), "Player Shoot");
	g->id = 0;
	this->projectiles.push_back(std::move(g));
}


void Game::Update()
{
		for (auto const & it : players)
		{
			it->GetComponent<Position>()->UpdatePos(it->GetComponent<Velocity>()->getVel(), 800, 600, 60);
			it->GetComponent<Velocity>()->UpdateVel(1.1f);
		}

		for (auto const & it : projectiles)
		{
			ge::Collision col = it->GetComponent<Collider>()->CollisionPrediction(it, "Player", players);
			if (col.point.x != -1) // Collision !
			{
		
			}
			else
			{ 
				it->GetComponent<Position>()->UpdatePos(it->GetComponent<Velocity>()->getVel(), 1000, 800, 30);
			}
		}
}