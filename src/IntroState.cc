#include "IntroState.h"

bool IntroState::Init(ge::GameEngine & engine) {
	engine.Rm().LoadFont("arial", "resources/arial.ttf");
	world_.CreateButton(engine.Cm()["Button"], { 300, 0 }, { "Start", "arial" }, { START });
	world_.CreateButton(engine.Cm()["Button"], { 300, 100 }, { "Quit", "arial" }, { QUIT });
	return true;
}

void IntroState::Clear() {
	world_.Reset();
}

void IntroState::Pause() {
}

void IntroState::Resume() {
}

void IntroState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) {
	for (uint32_t id = 0; id < ge::Settings::EntitiesCount; ++id) {
		ge::Entity & entity = world_.Entities(id);
		Text & text = world_.Texts(id);
		Input & input = world_.Inputs(id);
		Position & position = world_.Positions(id);
		if (event.button == sf::Mouse::Button::Left && (entity & engine.Cm()["Button"]) == engine.Cm()["Button"]) {
			sf::Text t(text.text, engine.Rm().Font(text.fontName));
			t.setPosition(position.x, position.y);
			if (t.getGlobalBounds().contains(static_cast<float>(event.x), static_cast<float>(event.y))) {
				switch (input.id) {
					case START:
						engine.PushState("Play");
						break;
					case QUIT:
						engine.Quit();
						break;
					default:
						break;
				}
			}
		}
	}
}

void IntroState::HandleEvent(ge::GameEngine & engine, sf::Event const & event) {
	switch (event.type) {
		case sf::Event::MouseButtonPressed:
			HandleClick_(engine, event.mouseButton);
		default:
			break;
	}
}

void IntroState::Update(ge::GameEngine const & game) {
}

void IntroState::Display(ge::GameEngine & engine, const float) {
	for (uint32_t id = 0; id < ge::Settings::EntitiesCount; ++id) {
		ge::Entity & entity = world_.Entities(id);
		Text & text = world_.Texts(id);
		Position & position = world_.Positions(id);
		if ((entity & engine.Cm()["Button"]) == engine.Cm()["Button"]) {
			sf::Text t(text.text, engine.Rm().Font(text.fontName));
			t.setPosition(position.x, position.y);
			engine.Draw(std::make_shared<sf::Text>(t), ge::Layer::UI);
		}
	}
}