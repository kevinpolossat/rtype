#include "Game.h"
using ge::Velocity;
using ge::Position;
using ge::Sprite;
using ge::Collider;
using ge::Ia;

Game::Game()
{
	time_ = std::chrono::high_resolution_clock::now();
	iaLoader_ = std::make_unique<loadIa>("resources/ai", 800, 600);
	endGame_ = false;
	idxennemy_ = 5;
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

void Game::CreateEnnemy(const int t_id)
{
	std::unique_ptr<GameObject> g = std::make_unique<GameObject>();

	std::shared_ptr<IArtificialIntelligence> ia = iaLoader_->getIa(t_id);
	Vector2f v(static_cast<double>(ia->getPosition().X), static_cast<double>(ia->getPosition().Y));

	g->AddComponent<Ia>(ia);
	g->AddComponent<Position>(v);
	g->AddComponent<Collider>(v, Vector2f(60,60), "Player");
	g->id = t_id;
	this->ennemy.push_back(std::move(g));
}

void Game::CreateEnnemyShoot(Vector2f const & t_position, Vector2f const & t_velocity)
{
	std::unique_ptr<GameObject> g = std::make_unique<GameObject>();

	g->AddComponent<Position>(t_position);
	g->AddComponent<Velocity>(t_velocity);
	g->AddComponent<Collider>(t_position, Vector2f(30, 15), "Player Shoot");
	g->id = 0;
	this->ennemy_projectiles.push_back(std::move(g));
}


void Game::Update()
{
		if (players.size() == 0)
			return;

		std::vector<AIPosition> playersPos;
		std::vector<AIPosition> shoots;

		for (auto const & it : players)
		{
			playersPos.push_back({static_cast<int>(it->GetComponent<Position>()->getPos().x), static_cast<int>(it->GetComponent<Position>()->getPos().y)});
			it->GetComponent<Position>()->UpdatePos(it->GetComponent<Velocity>()->getVel(), 800, 600, 60);
			it->GetComponent<Velocity>()->UpdateVel(1.1f);
		}
		for (auto const & it : projectiles)
		{
			shoots.push_back({static_cast<int>(it->GetComponent<Position>()->getPos().x), static_cast<int>(it->GetComponent<Position>()->getPos().y)});
			it->GetComponent<Position>()->UpdatePos(it->GetComponent<Velocity>()->getVel(), 1000, 800, 30);
		}

		bool f = true;
		int i = 0;

		while (f)
		{
			f = false;
			i = 0;
			for (auto const & it : projectiles)
			{
				ge::Collision col = it->GetComponent<Collider>()->CollisionPrediction(it, "Player", ennemy);
				if (col.point.x != -1)
				{
					ennemy.at(i)->GetComponent<Ia>()->ia->setDamages(1);
					projectiles.erase(projectiles.begin() + i);
					f = true;
					break;
				}
				i++;
			}
		}

		for (auto const & it : ennemy_projectiles)
			it->GetComponent<Position>()->UpdatePos(it->GetComponent<Velocity>()->getVel(), 1000, 800, 30);

		f = true;
		while (f && players.size() > 0)
		{
			f = false;
			i = 0;
			for (auto const & it : ennemy_projectiles)
			{
				ge::Collision col = it->GetComponent<Collider>()->CollisionPrediction(it, "Player", players);
				if (col.point.x != -1)
				{
					f = true;
					players.erase(players.begin() + col.index);
					ennemy_projectiles.erase(ennemy_projectiles.begin() + i);
					break;
				}
				i++;
			}
		}
		f = true;
		while (f)
		{
			f = false;
			for (int k = 0; k < projectiles.size(); k++)
			{
				if (projectiles.at(k)->GetComponent<Position>()->getPos().x <= 0
				|| projectiles.at(k)->GetComponent<Position>()->getPos().x > 800
				|| projectiles.at(k)->GetComponent<Position>()->getPos().y <= 0
				|| projectiles.at(k)->GetComponent<Position>()->getPos().y > 600)
				{
					f = true;
					projectiles.erase(projectiles.begin() + k);
				}
			}
		}
		f = true;
		while (f)
		{
			f = false;
			for (int k = 0; k < ennemy_projectiles.size(); k++)
			{
				if (ennemy_projectiles.at(k)->GetComponent<Position>()->getPos().x <= 0
				|| ennemy_projectiles.at(k)->GetComponent<Position>()->getPos().x > 800
				|| ennemy_projectiles.at(k)->GetComponent<Position>()->getPos().y <= 0
				|| ennemy_projectiles.at(k)->GetComponent<Position>()->getPos().y > 600)
				{
					f = true;
					ennemy_projectiles.erase(ennemy_projectiles.begin() + k);
				}
			}
		}

		if (idxennemy_ == -1 && ennemy.size() == 0)
			endGame_ = true;

		if (ennemy.size() == 0 && idxennemy_ >= 0)
			CreateEnnemy((idxennemy_--));

		i = 0;
		for (auto const & it : ennemy)
		{
			Action action = it->GetComponent<Ia>()->ia->actualize(playersPos, shoots, {static_cast<int>(it->GetComponent<Position>()->getPos().x), static_cast<int>(it->GetComponent<Position>()->getPos().y)});
			Vector2f v(static_cast<double>(it->GetComponent<Ia>()->ia->getPosition().X), static_cast<double>(it->GetComponent<Ia>()->ia->getPosition().Y));

			it->GetComponent<Position>()->setPos(v);
			if (action == Action::SHOOT)
			{
				Vector2f v1(static_cast<double>(it->GetComponent<Ia>()->ia->getShootVector().X) * -10, static_cast<double>(it->GetComponent<Ia>()->ia->getShootVector().Y) * -10);
				CreateEnnemyShoot(it->GetComponent<Position>()->getPos(), v1);
			}
			else if (action == Action::DEAD)
				ennemy.erase(ennemy.begin() + i);
			i++;
		}
		playersPos.clear();
		shoots.clear();
}
