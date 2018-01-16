#include "IntroState.h"

bool IntroState::Init(ge::GameEngine & engine) {
	engine.LoadFont("arial", "resources/arial.ttf");
	//world_.CreateButton(engine["Button"], { 300, 0 }, { "Start", "arial" }, { START });
	//world_.CreateButton(engine["Button"], { 300, 100 }, { "Quit", "arial" }, { QUIT });
	return true;
}

void IntroState::Clear() {
}

void IntroState::Pause() {
}

void IntroState::Resume() {
}

void IntroState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event)
{
		if (event.button == sf::Mouse::Button::Left) 
		{
			if (true)//t.getGlobalBounds().contains(static_cast<float>(event.x), static_cast<float>(event.y))) 
			{
				switch (0) {
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
		/*if (engine.Match(entity, "Button")) {
			sf::Text t(text.text, engine.Font(text.fontName));
			t.setPosition(position.x, position.y);
			engine.Draw(std::make_shared<sf::Text>(t), ge::Layer::UI);
		}
		*/
}