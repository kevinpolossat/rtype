#include "PlayState.h"
#include "GameEngine.h"

using ge::Position;
using ge::Animation;
using ge::Ia;
using ge::Sprite;
using ge::Velocity;
using ge::Collider;

PlayState::PlayState(std::shared_ptr<ge::network::UDPNonBlockingCommuncation> & t_udp)
{
	this->udp_ = t_udp;
	this->udp_->addHandle(std::bind(&PlayState::HandleUdp_, this, std::placeholders::_1, std::placeholders::_2));
	this->playersSprites_.push_back("Player1");
	this->playersSprites_.push_back("Player2");
	this->playersSprites_.push_back("Player3");
	this->playersSprites_.push_back("Player4");
}

bool PlayState::Init(ge::GameEngine & engine) {
	engine.Load<ge::Resources::Texture>("Player1", "resources/blue.png");
	engine.Load<ge::Resources::Texture>("Player2", "resources/red.png");
	engine.Load<ge::Resources::Texture>("Player3", "resources/yellow.png");
	engine.Load<ge::Resources::Texture>("Player4", "resources/green.png");

	engine.Load<ge::Resources::Texture>("Shoot", "resources/Shoot.png");
	engine.Load<ge::Resources::Texture>("Mechant", "resources/mechant.png");
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
					events_.emplace_back(engine.playerID, static_cast<int>(EVENTTYPE::PLAYERLEFT));
					break;
				case sf::Keyboard::Key::Right:
					events_.emplace_back(engine.playerID, static_cast<int>(EVENTTYPE::PLAYERRIGHT));
					break;
				case sf::Keyboard::Key::Up:
					events_.emplace_back(engine.playerID, static_cast<int>(EVENTTYPE::PLAYERUP));
					break;
				case sf::Keyboard::Key::Down:
					events_.emplace_back(engine.playerID, static_cast<int>(EVENTTYPE::PLAYERDOWN));
					break;
				case sf::Keyboard::Key::Space:
					events_.emplace_back(engine.playerID, static_cast<int>(EVENTTYPE::PLAYERSHOOT));
					break;
				default:
					break;
			}
}

void PlayState::HandlePlayerAnimation_(ge::GameEngine const & engine, sf::Event::KeyEvent const & event) {
	
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

void PlayState::HandleUdp_(void *data, std::size_t nbyte)
{
	auto p = rtype::protocol_udp::extract<rtype::protocol_udp::Entity>(static_cast<char *>(data), nbyte);
	world_.players.clear();
	world_.projectiles.clear();
	for (auto it : p.elements)
	{
			switch (it.type)
			{
			case static_cast<int>(ENTITYTYPE::PLAYER) :
				world_.CreatePlayer(Vector2f(it.x, it.y), playersSprites_[it.id]);
				break;
			case static_cast<int>(ENTITYTYPE::PLAYERSHOOT) :
				world_.CreateShoot(Vector2f(it.x, it.y));
				break;
			default:
				break;
			}
		//std::cout << "ID=" << it.id << " Type=" << it.type << " State=" << it.state << " X=" << it.x << " Y=" << it.y << std::endl;
	}
	auto seqId = p.h.seqId;
}

void PlayState::Update(ge::GameEngine & engine)
{
	if (events_.size() != 0)
	{
		this->udp_->notifyAll(events_);
		events_.clear();
	}
	/*
	uint32_t i = 0;
	std::vector<AIPosition> playersPos;
	std::vector<AIPosition> shoots;

	for (auto const & it : world_.players)
	{
		playersPos.push_back({static_cast<int>(it->GetComponent<Position>()->tgePos().x), static_cast<int>(it->GetComponent<Position>()->getPos().y)});
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
	*/
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
