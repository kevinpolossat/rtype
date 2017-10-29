#include "PlayState.h"
#include "GameEngine.h"

PlayState PlayState::instance_;

PlayState::PlayState()
	: circle_(100.f) {
	circle_.setFillColor(sf::Color::Green);
}

PlayState::~PlayState() {
}

bool PlayState::Init() {
	return true;
}

void PlayState::Clear() {
}

void PlayState::Pause() {
}

void PlayState::Resume() {
}

void PlayState::HandleEvents(GameEngine & game) {
	sf::Event event;
	while (game.Window().pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				game.Window().close();
				break;
			default:
				break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		circle_.move(-1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		circle_.move(1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		circle_.move(0, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		circle_.move(0, 1);
	}
}

void PlayState::Update(GameEngine const & game) {
}

void PlayState::Display(GameEngine & game) {
	game.Window().draw(circle_);
}

PlayState & PlayState::Instance() {
	return instance_;
}

