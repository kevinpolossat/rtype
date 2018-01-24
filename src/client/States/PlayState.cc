#include "PlayState.h"
#include "GameEngine.h"

using ge::Position;
using ge::Animation;
using ge::Ia;
using ge::Sprite;
using ge::Velocity;
using ge::Collider;
bool PlayState::Init(ge::GameEngine & engine) {
	engine.Load<ge::Resources::Texture>("Player1", "resources/SpaceShip.png");
	engine.Load<ge::Resources::Texture>("Shoot", "resources/Shoot.png");
	engine.Load<ge::Resources::Texture>("Mechant", "resources/mechant.png");
	world_.CreatePlayer(Vector2f(300, 300), "Player1");
	this->time_ = std::chrono::high_resolution_clock::now();
	return true;
}

void PlayState::Clear() {
}

void PlayState::Pause() {
}

void PlayState::Resume() {
}

void PlayState::HandlePlayerMovement_(ge::GameEngine const & engine, sf::Event::KeyEvent const & event)
{
			switch (event.code)
			{
				case sf::Keyboard::Key::Left:
					world_.players[0]->GetComponent<ge::Velocity>()->m_pos.x -= 10;
					break;
				case sf::Keyboard::Key::Right:
					world_.players[0]->GetComponent<ge::Velocity>()->m_pos.x += 10;
					break;
				case sf::Keyboard::Key::Up:
					world_.players[0]->GetComponent<ge::Velocity>()->m_pos.y -= 10;
					break;
				case sf::Keyboard::Key::Down:
					world_.players[0]->GetComponent<ge::Velocity>()->m_pos.y += 10;
					break;
				default:
					break;
			}
}

void PlayState::HandlePlayerAnimation_(ge::GameEngine const & engine, sf::Event::KeyEvent const & event) {
	if (event.code == sf::Keyboard::Key::Space)
	{
		//world_.players[0]->GetComponent<Animator>().DoOnce("Attack");
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->time_);
		if (static_cast<double>(ms.count() / 1000) > 0.5f) // Fire Rate 1 Shot every 0.5 sec
		{
			this->time_ = std::chrono::high_resolution_clock::now();
			Vector2f newPos = world_.players[0]->GetComponent<Position>()->getPos();
			newPos.y += 25;
			newPos.x += 70;
			world_.CreateShoot(newPos, Vector2f(10,0), "Shoot");
		}
	}
}

void PlayState::HandleQuit_(ge::GameEngine & engine, sf::Event::KeyEvent const & event) {
	if (event.code == sf::Keyboard::Key::Escape) {
		engine.PopState();
	}
}

void PlayState::HandleEvent(ge::GameEngine & engine, sf::Event const & event) {
	switch (event.type) {
		case sf::Event::KeyPressed:
			HandlePlayerMovement_(engine, event.key);
			HandlePlayerAnimation_(engine, event.key);
			HandleQuit_(engine, event.key);
			break;
		default:
			break;
	}
}

void PlayState::Update(ge::GameEngine & engine)
{
	uint32_t i = 0;
	std::vector<AIPosition> playersPos;
	std::vector<AIPosition> shoots;

	for (auto const & it : world_.players)
	{
		playersPos.push_back({static_cast<int>(it->GetComponent<Position>()->getPos().x), static_cast<int>(it->GetComponent<Position>()->getPos().y)});
		it->GetComponent<Position>()->UpdatePos(it->GetComponent<Velocity>()->getVel(), 800, 600, 60);
		it->GetComponent<Velocity>()->UpdateVel(1.1f);
		i++;
	}

	i = 0;
	for (auto const & it : world_.projectiles)
	{
		shoots.push_back({static_cast<int>(it->GetComponent<Position>()->getPos().x), static_cast<int>(it->GetComponent<Position>()->getPos().y)});
		ge::Collision col = it->GetComponent<Collider>()->CollisionPrediction(it, "Player", world_.players);
		if (col.point.x != -1) // Collision !
		{
			world_.players.erase(world_.players.begin() + col.index);
			world_.projectiles.erase(world_.projectiles.begin() + i);
		}
		else
		{
			it->GetComponent<Position>()->UpdatePos(it->GetComponent<Velocity>()->getVel(), 1000, 800, 30);
		}
		i++;
	}

	for (int k = 0; k < world_.projectiles.size(); k++)
	{
		if (world_.projectiles.at(k)->GetComponent<Position>()->getPos().x < 10
				|| world_.projectiles.at(k)->GetComponent<Position>()->getPos().x > 780
				|| world_.projectiles.at(k)->GetComponent<Position>()->getPos().y < 10
				|| world_.projectiles.at(k)->GetComponent<Position>()->getPos().y > 580)
			world_.projectiles.erase(world_.projectiles.begin() + k);
	}

	
	static int lapin = 0;
	if (world_.ennemy.size() == 0)
		world_.CreateEnnemy("Player1", (lapin++) % 5);

	i = 0;
	for (auto const & it : world_.ennemy)
	{
		Action action = it->GetComponent<Ia>()->ia->actualize(playersPos, shoots, {static_cast<int>(it->GetComponent<Position>()->getPos().x), static_cast<int>(it->GetComponent<Position>()->getPos().y)});
		Vector2f v(static_cast<double>(it->GetComponent<Ia>()->ia->getPosition().X), static_cast<double>(it->GetComponent<Ia>()->ia->getPosition().Y));
		it->GetComponent<Position>()->setPos(v);
		if (action == Action::SHOOT)
		{
			Vector2f v1(static_cast<double>(it->GetComponent<Ia>()->ia->getShootVector().X) * -10, static_cast<double>(it->GetComponent<Ia>()->ia->getShootVector().Y) * -10);
			world_.CreateShoot(it->GetComponent<Position>()->getPos(), v1, "Shoot");
		}
		else if (action == Action::DEAD)
			world_.ennemy.erase(world_.ennemy.begin() + i);
		i++;
	}
	playersPos.clear();
	shoots.clear();
}

void PlayState::Display(ge::GameEngine & engine, const float)
{
	for (auto const & it : world_.players)
	{
		/*	sf::Sprite s(engine.Texture(it->GetComponent<Animator>().GetSprite()));
			s.setPosition(it->GetComponent<Position>().getPos().x, it->GetComponent<Position>().getPos().y);
			engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<Animator>().GetPriority());
		*/
		sf::Sprite s(engine.Texture(it->GetComponent<Sprite>()->textureName));
		s.setPosition(it->GetComponent<Position>()->getPos().x, it->GetComponent<Position>()->getPos().y);
		engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<Sprite>()->priority);
	}
	for (auto const & it : world_.ennemy)
	{
		/*	sf::Sprite s(engine.Texture(it->GetComponent<Animator>().GetSprite()));
			s.setPosition(it->GetComponent<Position>().getPos().x, it->GetComponent<Position>().getPos().y);
			engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<Animator>().GetPriority());
		*/
		sf::Sprite s(engine.Texture(it->GetComponent<Sprite>()->textureName));
		s.setPosition(it->GetComponent<Position>()->getPos().x, it->GetComponent<Position>()->getPos().y);
		engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<Sprite>()->priority);
	}
	for (auto const & it : world_.projectiles)
	{
		sf::Sprite s(engine.Texture(it->GetComponent<Sprite>()->textureName));
		s.setPosition(it->GetComponent<Position>()->getPos().x, it->GetComponent<Position>()->getPos().y);
		engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<Sprite>()->priority);
	}
}
