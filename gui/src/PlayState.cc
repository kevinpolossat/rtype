#include "PlayState.h"
#include "GameEngine.h"

PlayState::PlayState()
	: AGameState() {
}

bool PlayState::Init(GameEngine & engine) {
	world_.CreatePlayer({ 300, 300 }, { 0, 0 });
	return true;
}

void PlayState::Clear() {
	world_.Reset();
}

void PlayState::Pause() {
}

void PlayState::Resume() {
}

void PlayState::HandlePlayerMovement_(sf::Event::KeyEvent const & event) {
	for (uint32_t id = 0; id < settings::ENTITY_COUNT; ++id) {
		Entity & entity = world_.Entities(id);
		Velocity & velocity = world_.Velocities(id);
		if ((entity & component::player) == component::player) {
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

void PlayState::HandleQuit_(GameEngine & engine, sf::Event::KeyEvent const & event) {
	if (event.code == sf::Keyboard::Key::Escape) {
		engine.PopState();
	}
}

void PlayState::HandleEvents(GameEngine & engine) {
	sf::Event event;
	while (engine.Window().pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				engine.Window().close();
				break;
			case sf::Event::KeyPressed:
				HandlePlayerMovement_(event.key);
				HandleQuit_(engine, event.key);
				break;
			default:
				break;
		}
	}
}

void PlayState::Update(GameEngine const & game) {
	for (uint32_t id = 0; id < settings::ENTITY_COUNT; ++id) {
		Entity & entity = world_.Entities(id);
		Velocity & velocity = world_.Velocities(id);
		Position & position = world_.Positions(id);
		if ((entity & component::player) == component::player) {
			position.x += velocity.x;
			position.y += velocity.y;
			velocity.x /= 1.1f;
			velocity.y /= 1.1f;
		}
	}
}

void PlayState::Display(GameEngine & engine, const float interpolation) {
	for (uint32_t id = 0; id < settings::ENTITY_COUNT; ++id) {
		Entity & entity = world_.Entities(id);
		Velocity & velocity = world_.Velocities(id);
		Position & position = world_.Positions(id);
		if ((entity & component::player) == component::player) {
			sf::CircleShape c(100);
			c.setPosition(position.x, position.y);
			engine.Window().draw(c);
		}
	}
}