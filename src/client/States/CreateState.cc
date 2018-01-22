#include "CreateState.h"

bool CreateState::Init(ge::GameEngine & engine)
{
	ge::Vector2u size = engine.GetSize();
	world_.CreateText(ge::Vector2f(size.x / 5.f, 0), "Name Game : ", "arial");
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f), "-","retro", MOINS);
	world_.CreateText(ge::Vector2f(size.x / 5.f * 2, size.y / 5.f), std::to_string(nbPlayers), "arial");
	world_.CreateText(ge::Vector2f(size.x / 5.f * 3, size.y / 5.f), "+", "retro", PLUS);
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f * 2), "Valid", "retro", VALID);
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f * 3), "Cancel",  "retro", CANCEL);
	world_.CreateBackground();

	return true;
}

void CreateState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) {
	if (event.button == sf::Mouse::Button::Left) {
		for (auto const & it : world_.texts) {
			if(it->GetComponent<ge::Text>())
			{
				sf::Text t(it->GetComponent<ge::Text>()->text, engine.Font(it->GetComponent<ge::Text>()->fontName));
				t.setPosition(it->GetComponent<ge::Position>()->getPos().x, it->GetComponent<ge::Position>()->getPos().y);
							if (t.getGlobalBounds().contains(static_cast<float>(event.x), static_cast<float>(event.y))) {
					switch (it->GetComponent<ge::Input>()->id) {
						case PLUS:
							if (nbPlayers < 4)
								++nbPlayers;
							break;
						case MOINS:
							if (nbPlayers > 1)
								--nbPlayers;
							break;
						case VALID:
							engine.PushState("Play");
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
