#include "JoinState.h"

bool JoinState::Init(ge::GameEngine & engine) {
	engine.Load<ge::Resources::Font>("arial", "resources/arial.ttf");
	engine.Load<ge::Resources::Texture>("valid", "resources/Buttons/button_validg.png");
	engine.Load<ge::Resources::Texture>("cancel", "resources/Buttons/button_cancel.png");

	ge::Vector2u size = engine.GetSize();
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f), "GAMES : ", "arial");
	for(auto const & it : _games) {
		world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f), it, "arial");
	}
	world_.CreateButton(ge::Vector2f(size.x / 5.f, size.y / 5.f * 4), "arial", VALID, "valid");
	world_.CreateButton(ge::Vector2f(size.x / 5.f * 3, size.y / 5.f * 4), "arial", CANCEL, "cancel");
	world_.CreateBackground();


	return true;
}

void JoinState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) {
	if (event.button == sf::Mouse::Button::Left) {
		for (auto const & it : world_.buttons) {
			if(it->GetComponent<ge::Sprite>()) {
				sf::Sprite t(engine.Texture(it->GetComponent<ge::Sprite>()->textureName));
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