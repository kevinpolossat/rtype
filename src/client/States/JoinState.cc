#include "JoinState.h"

bool JoinState::Init(ge::GameEngine & engine) {
	ge::Vector2u size = engine.GetSize();
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f), "GAMES : ", "retro");
	for(auto const & it : _games) {
		world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f), it, "arial");
	}
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f * 4), "Valid", "retro", VALID);
	world_.CreateText(ge::Vector2f(size.x / 5.f * 3, size.y / 5.f * 4), "Cancel", "retro", CANCEL);
	world_.CreateBackground();
	return true;
}

void JoinState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) {
	if (event.button == sf::Mouse::Button::Left) {
			for (auto const & it : world_.texts) {
				if(it->GetComponent<ge::Text>())
				{
					sf::Text t(it->GetComponent<ge::Text>()->text, engine.Font(it->GetComponent<ge::Text>()->fontName));
					t.setPosition(it->GetComponent<ge::Position>()->getPos().x, it->GetComponent<ge::Position>()->getPos().y);
					if (t.getGlobalBounds().contains(static_cast<float>(event.x), static_cast<float>(event.y))) {
					switch (it->GetComponent<ge::Input>()->id) {
						case VALID:
							break;
						case CANCEL:
							engine.PopState();
							break;
						default:
							break;
					}
				}
			}
		}
	}
}
