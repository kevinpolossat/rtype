#include "IntroState.h"

bool IntroState::Init(ge::GameEngine & engine) {
	engine.Load<ge::Resources::Font>("arial", "resources/arial.ttf");
	world_.CreateButton(ge::Vector2f(300, 0), "Start", "arial", START);
	world_.CreateButton(ge::Vector2f(300, 100), "Quit", "arial", QUIT);
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
			for (auto const & it : world_.buttons)
			{
				sf::Text t(it->GetComponent<ge::Text>().text, engine.Font(it->GetComponent<ge::Text>().fontName));
				t.setPosition(it->GetComponent<ge::Position>().getPos().x, it->GetComponent<ge::Position>().getPos().y);
				if (t.getGlobalBounds().contains(static_cast<float>(event.x), static_cast<float>(event.y)))
				{
					switch (it->GetComponent<ge::Input>().id)
					{
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

void IntroState::Update(ge::GameEngine const & game) 
{
}

void IntroState::Display(ge::GameEngine & engine, const float) 
{
	for (auto const & it : world_.buttons)
	{
		sf::Text t(it->GetComponent<ge::Text>().text, engine.Font(it->GetComponent<ge::Text>().fontName));
		t.setPosition(it->GetComponent<ge::Position>().getPos().x, it->GetComponent<ge::Position>().getPos().y);
		engine.Draw(std::make_shared<sf::Text>(t), ge::Layer::UI);
	}
}