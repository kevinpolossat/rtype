#include "IntroState.h"

bool IntroState::Init(ge::GameEngine & engine) {
	engine.Load<ge::Resources::Font>("arial", "resources/arial.ttf");
	engine.Load<ge::Resources::Font>("retro", "resources/PressStart2P.ttf");
	engine.Load<ge::Resources::Texture>("play", "resources/Buttons/button_play.png");
	engine.Load<ge::Resources::Texture>("settings", "resources/Buttons/button_settings.png");
	engine.Load<ge::Resources::Texture>("quit", "resources/Buttons/button_quit.png");

	ge::Vector2u size = engine.GetSize();
	/*
	world_.CreateButton(ge::Vector2f(size.x / 2 - 100, size.y / 5.f), "arial", START, "play");
	world_.CreateButton(ge::Vector2f(size.x / 2 - 100, size.y / 5.f * 2), "arial", SETTINGS, "settings");
	world_.CreateButton(ge::Vector2f(size.x / 2 - 100, size.y / 5.f * 3), "arial", QUIT, "quit");
	*/
	world_.CreateText(ge::Vector2f(size.x / 2 - 50, size.y / 5.f), "Play", "retro", START);
	world_.CreateText(ge::Vector2f(size.x / 2 - 100, size.y / 5.f * 2), "Settings", "retro", SETTINGS);
	world_.CreateText(ge::Vector2f(size.x / 2 - 50, size.y / 5.f * 3), "Quit", "retro", QUIT);

	world_.CreateBackground();
	engine.Load(*world_.background->GetComponent<ge::Animator>());
	return true;
}

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

void IntroState::Display(ge::GameEngine & engine, float) {
	for (auto const & it : world_.texts) {
		sf::Text t(it->GetComponent<ge::Text>()->text, engine.Font(it->GetComponent<ge::Text>()->fontName));
		t.setPosition(it->GetComponent<ge::Position>()->getPos().x, it->GetComponent<ge::Position>()->getPos().y);
		engine.Draw(std::make_shared<sf::Text>(t), ge::Layer::UI);
	}
	for (auto const & it : world_.buttons) {
		if (it->GetComponent<ge::Sprite>()) {
			sf::Sprite s(engine.Texture(it->GetComponent<ge::Sprite>()->textureName));
			s.setPosition(it->GetComponent<ge::Position>()->getPos().x, it->GetComponent<ge::Position>()->getPos().y);
			engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<ge::Sprite>()->priority);
		}
	}
	sf::Sprite s(engine.Texture(world_.background->GetComponent<ge::Animator>()->GetSprite()));
	s.setPosition(0, 0);
	s.scale(1.8f, 1.8f);
	engine.Draw(std::make_shared<sf::Sprite>(s), 2);
}