#include "LoginState.h"

bool LoginState::Init(ge::GameEngine & engine) {
	engine.Load<ge::Resources::Font>("arial", "resources/arial.ttf");
	engine.Load<ge::Resources::Texture>("create", "resources/Buttons/button_create.png");
	engine.Load<ge::Resources::Texture>("join", "resources/Buttons/button_join.png");
	engine.Load<ge::Resources::Texture>("cancel", "resources/Buttons/button_cancel.png");

	ge::Vector2u size = engine.GetSize();
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f), "LOGIN : ", "arial");
	world_.CreateButton(ge::Vector2f(size.x / 5.f, size.y / 5.f * 2), "arial", CREATE, "create");
	world_.CreateButton(ge::Vector2f(size.x / 5.f, size.y / 5.f * 3), "arial", JOIN, "join");
	world_.CreateButton(ge::Vector2f(size.x / 5.f, size.y / 5.f * 4), "arial", CANCEL, "cancel");

	return true;
}

void LoginState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) {
	if (event.button == sf::Mouse::Button::Left) {
		for (auto const & it : world_.buttons) {
			if (it->GetComponent<ge::Sprite>()) {
				sf::Sprite t(engine.Texture(it->GetComponent<ge::Sprite>()->textureName));
				t.setPosition(it->GetComponent<ge::Position>()->getPos().x, it->GetComponent<ge::Position>()->getPos().y);
				if (t.getGlobalBounds().contains(static_cast<float>(event.x), static_cast<float>(event.y))) {
					switch (it->GetComponent<ge::Input>()->id) {
						case CREATE:
							engine.PushState("Create");
							break;
						case JOIN:
							engine.PushState("Join");
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