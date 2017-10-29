#include "IntroState.h"
#include "PlayState.h"
#include "GameEngine.h"

IntroState IntroState::instance_;

IntroState::IntroState() {
}

IntroState::~IntroState() {
}

bool IntroState::Init() {
	if (!font_.loadFromFile("resources/arial.ttf")) {
		return false;
	}
	text_.setFont(font_);
	text_.setString("Hello world");
	return true;
}

void IntroState::Clear() {
}

void IntroState::Pause() {
}

void IntroState::Resume() {
}

void IntroState::HandleEvents(GameEngine & game) {
	sf::Event event;
	while (game.Window().pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			game.Window().close();
			break;
		case sf::Event::KeyPressed:
			game.ChangeState(&PlayState::Instance());
		default:
			break;
		}
	}
}

void IntroState::Update(GameEngine const & game) {
}

void IntroState::Display(GameEngine & game) {
	game.Window().draw(text_);
}

IntroState & IntroState::Instance() {
	return instance_;
}
