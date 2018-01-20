#include "MenuState.h"

void MenuState::Clear() {
}

void MenuState::Pause() {
}

void MenuState::Resume() {
}

void MenuState::HandleEvent(ge::GameEngine & engine, sf::Event const & event) {
	switch (event.type) {
		case sf::Event::MouseButtonPressed:
			HandleClick_(engine, event.mouseButton);
		default:
			break;
	}
}

void MenuState::Update(ge::GameEngine & game) {
}

void MenuState::Display(ge::GameEngine & engine, float) {
	for (auto const & it : world_.texts) {
		sf::Text t(it->GetComponent<ge::Text>()->text, engine.Font(it->GetComponent<ge::Text>()->fontName));
		t.setPosition(it->GetComponent<ge::Position>()->getPos().x, it->GetComponent<ge::Position>()->getPos().y);
		engine.Draw(std::make_shared<sf::Text>(t), ge::Layer::UI);
	}
	for (auto const & it : world_.buttons) {
		if(it->GetComponent<ge::Sprite>()) {
			sf::Sprite s(engine.Texture(it->GetComponent<ge::Sprite>()->textureName));
			s.setPosition(it->GetComponent<ge::Position>()->getPos().x, it->GetComponent<ge::Position>()->getPos().y);
			engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<ge::Sprite>()->priority);
		}
	}
}
