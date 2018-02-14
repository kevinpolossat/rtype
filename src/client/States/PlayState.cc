#include "PlayState.h"
#include "RandomGenerator.h"

using ge::Position;
using ge::Animation;
using ge::Ia;
using ge::Sprite;
using ge::Velocity;
using ge::Collider;

PlayState::PlayState(std::shared_ptr<ge::network::UDPNonBlockingCommuncation> & t_udp) {
	this->udp_ = t_udp;
	this->udp_->addHandle(std::bind(&PlayState::HandleUdp_, this, std::placeholders::_1, std::placeholders::_2));
	this->playersSprites_.emplace_back("Player1");
	this->playersSprites_.emplace_back("Player2");
	this->playersSprites_.emplace_back("Player3");
	this->playersSprites_.emplace_back("Player4");
}

bool PlayState::Init(ge::GameEngine & engine) {
	engine.Load<ge::Resources::Texture>("Player1", "resources/blue.png");
	engine.Load<ge::Resources::Texture>("Player2", "resources/red.png");
	engine.Load<ge::Resources::Texture>("Player3", "resources/yellow.png");
	engine.Load<ge::Resources::Texture>("Player4", "resources/green.png");

	engine.Load<ge::Resources::Texture>("Shoot", "resources/Shoot.png");
	engine.Load<ge::Resources::Texture>("Star", "resources/star2.png");
	engine.Load<ge::Resources::Texture>("Ennemy", "resources/mechant.png");
	engine.Load<ge::Resources::Texture>("ShootEnnemy", "resources/mechantshoot.png");
	this->time_ = std::chrono::high_resolution_clock::now();
	this->endGame_ = false;
	return true;
}

void PlayState::Clear() {
}

void PlayState::Pause() {
}

void PlayState::Resume() {
}

void PlayState::HandlePlayerMovement_(ge::GameEngine const & engine, sf::Event::KeyEvent const & event) {
	switch (event.code) {
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
		engine.PushState("SettingsGame");
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

void PlayState::HandleUdp_(void *data, std::size_t nbyte) {
	auto p = rtype::protocol_udp::extract<rtype::protocol_udp::Entity>(static_cast<char *>(data), nbyte);
	world_.players.clear();
	world_.ennemy.clear();
	world_.ennemy_projectiles.clear();
	world_.projectiles.clear();
	for (auto it : p.elements) {
		switch (it.type) {
			case static_cast<int>(ENTITYTYPE::PLAYER) :
				world_.CreatePlayer(Vector2f(it.x, it.y), playersSprites_[it.id]);
				break;
			case static_cast<int>(ENTITYTYPE::PLAYERSHOOT) :
				world_.CreateShoot(Vector2f(it.x, it.y));
				break;
			case static_cast<int>(ENTITYTYPE::ENNEMY) :
				world_.CreateEnnemy("Ennemy", it.id, static_cast<int>(it.x), static_cast<int>(it.y));
				break;
			case static_cast<int>(ENTITYTYPE::ENNEMYSHOOT) :
				world_.CreateEnnemyShoot(Vector2f(it.x, it.y), "ShootEnnemy");
				break;
			case static_cast<int>(ENTITYTYPE::ENDGAME) :
				this->endGame_ = true;
			default:
				break;
		}
	}
	auto seqId = p.h.seqId;
}

void PlayState::Update(ge::GameEngine & engine) {
	if (!events_.empty()) {
		this->udp_->notifyAll(events_);
		events_.clear();
	}
}

void PlayState::Display(ge::GameEngine & engine, const float) {
	if (this->endGame_) {
		engine.ChangeState("End");
		return;
	}
	ge::Vector2f size = engine.GetSize();

	if (RandomGenerator::Rand() % 600 == 0)
		starpos_.emplace_back(Vector2f(size.x, RandomGenerator::Rand() % static_cast<int>(size.y)));

	for (auto & it : starpos_) {
		it.x -= 0.2;
		sf::Sprite s(engine.Texture("Star"));
		s.setPosition(it.x, it.y);
		engine.Draw(std::make_shared<sf::Sprite>(s), 5);
	}
	bool f = true;
	while (f) {
		f = false;
		int i = 0;
		for (auto const & it : starpos_) {
			if (it.x < 0) {
				starpos_.erase(starpos_.begin() + i);
				f = true;
				break;
			}
			i += 1;
		}
	}
	for (auto const & it : world_.players) {
		sf::Sprite s(engine.Texture(it->GetComponent<Sprite>()->textureName));
		s.setPosition(it->GetComponent<Position>()->getPos().x, it->GetComponent<Position>()->getPos().y);
		engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<Sprite>()->priority);
	}
	for (auto const & it : world_.ennemy) {
		sf::Sprite s(engine.Texture(it->GetComponent<Sprite>()->textureName));
		s.setPosition(it->GetComponent<Position>()->getPos().x, it->GetComponent<Position>()->getPos().y);
		engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<Sprite>()->priority);
	}
	for (auto const & it : world_.projectiles) {
		sf::Sprite s(engine.Texture(it->GetComponent<Sprite>()->textureName));
		s.setPosition(it->GetComponent<Position>()->getPos().x, it->GetComponent<Position>()->getPos().y);
		engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<Sprite>()->priority);
	}
	for (auto const & it : world_.ennemy_projectiles) {
		sf::Sprite s(engine.Texture(it->GetComponent<Sprite>()->textureName));
		s.setPosition(it->GetComponent<Position>()->getPos().x, it->GetComponent<Position>()->getPos().y);
		engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<Sprite>()->priority);
	}
}
