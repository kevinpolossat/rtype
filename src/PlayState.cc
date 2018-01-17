#include "PlayState.h"
#include "GameEngine.h"

bool PlayState::Init(ge::GameEngine & engine) {
	engine.LoadTexture("nyancat", "resources/nyancat.png");
	world_.CreatePlayer(Vector2D(300, 300));
	engine.LoadTextures(world_.players[0]->GetComponent<Animator>());

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
					world_.players[0]->GetComponent<Velocity>().m_pos.x -= 10;
					break;
				case sf::Keyboard::Key::Right:
					world_.players[0]->GetComponent<Velocity>().m_pos.x += 10;
					break;
				case sf::Keyboard::Key::Up:
					world_.players[0]->GetComponent<Velocity>().m_pos.y -= 10;
					break;
				case sf::Keyboard::Key::Down:
					world_.players[0]->GetComponent<Velocity>().m_pos.y += 10;
					break;
				default:
					break;
			}
}

void PlayState::HandlePlayerAnimation_(ge::GameEngine const & engine, sf::Event::KeyEvent const & event) {
	if (event.code == sf::Keyboard::Key::Space) 
	{
		world_.players[0]->GetComponent<Animator>().DoOnce("Attack");
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

void PlayState::Update(ge::GameEngine const & engine) 
{
	for (auto it : world_.players)
	{
		it->GetComponent<Position>().UpdatePos(it->GetComponent<Velocity>().getVel());
		it->GetComponent<Velocity>().UpdateVel(1.1f);
	}
}

void PlayState::Display(ge::GameEngine & engine, const float) 
{
	for (auto it : world_.players)
	{
		sf::Sprite s(engine.Texture(it->GetComponent<Animator>().GetSprite()));
		s.setPosition(it->GetComponent<Position>().getPos().x, it->GetComponent<Position>().getPos().y);
		engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<Animator>().GetPriority());
	}
}