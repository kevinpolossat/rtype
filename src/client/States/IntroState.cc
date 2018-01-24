#include "IntroState.h"

bool IntroState::Init(ge::GameEngine & engine) {
	engine.Load<ge::Resources::Font>("arial", "resources/arial.ttf");
	engine.Load<ge::Resources::Font>("retro", "resources/PressStart2P.ttf");

	ge::Vector2u size = engine.GetSize();
	world_.CreateText(ge::Vector2f(size.x / 2 - 50, size.y / 5.f), "Play", "retro", START);
	world_.CreateText(ge::Vector2f(size.x / 2 - 100, size.y / 5.f * 2), "Settings", "retro", SETTINGS);
	world_.CreateText(ge::Vector2f(size.x / 2 - 50, size.y / 5.f * 3), "Quit", "retro", QUIT);

	world_.CreateBackground();
	engine.Load(*world_.background->GetComponent<ge::Animator>());
	return true;
}
void IntroState::HandleKey_(ge::GameEngine & engine, sf::Event::TextEvent const & event){}
void IntroState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) {
	if (event.button == sf::Mouse::Button::Left) {
		for (auto const & it : world_.texts)
		{
			if(it->GetComponent<ge::Text>())
			{
				sf::Text t(it->GetComponent<ge::Text>()->text, engine.Font(it->GetComponent<ge::Text>()->fontName));
				t.setPosition(it->GetComponent<ge::Position>()->getPos().x, it->GetComponent<ge::Position>()->getPos().y);
				if (t.getGlobalBounds().contains(static_cast<float>(event.x), static_cast<float>(event.y)))
				{
					switch (it->GetComponent<ge::Input>()->id)
					{
						case START:
							engine.PushState("Login");
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
}
