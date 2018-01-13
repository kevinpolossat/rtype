#include "PlayState.h"
#include "GameEngine.h"

bool PlayState::Init(ge::GameEngine & engine) {
	engine.LoadTexture("nyancat", "resources/nyancat.png");
	engine.LoadTexture("red_cross", "resources/red_cross.png");
	world_.CreatePlayer(engine["Player"], { 300, 300 }, { 0, 0 }, { "nyancat", 1 });
	world_.CreateCross(engine["Drawable"], { 30, 30 }, { "red_cross", 2 });
	return true;
}

void PlayState::Clear() {
	world_.Reset();
}

void PlayState::Pause() {
}

void PlayState::Resume() {
}

void PlayState::HandlePlayerMovement_(ge::GameEngine const & engine, sf::Event::KeyEvent const & event) {
	for (uint32_t id = 0; id < ge::Settings::EntitiesCount; ++id) {
		ge::Entity & entity = world_.Entities(id);
		Velocity & velocity = world_.Velocities(id);
		if ((entity & engine["Player"]) == engine["Player"]) {
			switch (event.code) {
				case sf::Keyboard::Key::Left:
					velocity.x -= 10;
					break;
				case sf::Keyboard::Key::Right:
					velocity.x += 10;
					break;
				case sf::Keyboard::Key::Up:
					velocity.y -= 10;
					break;
				case sf::Keyboard::Key::Down:
					velocity.y += 10;
					break;
				default:
					break;
			}
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
			HandleQuit_(engine, event.key);
			break;
		default:
			break;
	}
}

void PlayState::Update(ge::GameEngine const & engine) {
	for (uint32_t id = 0; id < ge::Settings::EntitiesCount; ++id) {
		ge::Entity & entity = world_.Entities(id);
		Velocity & velocity = world_.Velocities(id);
		Position & position = world_.Positions(id);
		if ((entity & engine.Cm()["Player"]) == engine.Cm()["Player"]) {
			position.x += velocity.x;
			position.y += velocity.y;
			velocity.x /= 1.1f;
			velocity.y /= 1.1f;
		}
	}
}

void PlayState::Display(ge::GameEngine & engine, const float) {
	for (uint32_t id = 0; id < ge::Settings::EntitiesCount; ++id) {
		ge::Entity & entity = world_.Entities(id);
		Sprite & sprite = world_.Sprites(id);
		Position & position = world_.Positions(id);
		if ((entity & engine["Drawable"]) == engine["Drawable"]) {
			sf::Sprite s(engine.Texture(sprite.textureName));
			s.setPosition(position.x, position.y);
			engine.Draw(std::make_shared<sf::Sprite>(s), sprite.priority);
		}
	}
}