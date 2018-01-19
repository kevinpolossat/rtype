#include "LoginState.h"

bool LoginState::Init(ge::GameEngine & engine) {
	engine.Load<ge::Resources::Font>("arial", "resources/arial.ttf");
	engine.Load<ge::Resources::Texture>("create", "resources/Buttons/button_create.png");
	engine.Load<ge::Resources::Texture>("join", "resources/Buttons/button_join.png");
  engine.Load<ge::Resources::Texture>("cancel", "resources/Buttons/button_cancel.png");

	ge::Vector2u size = engine.GetSize();
  world_.CreateButton(ge::Vector2f(size.x / 5, size.y / 5), "LOGIN : ", "arial", NONE);
	world_.CreateButton(ge::Vector2f(size.x / 5, size.y / 5 * 2), "", "arial", CREATE, "create");
  world_.CreateButton(ge::Vector2f(size.x / 5, size.y / 5 * 3), "", "arial", JOIN, "join");
  world_.CreateButton(ge::Vector2f(size.x / 5, size.y / 5 * 4), "", "arial", CANCEL, "cancel");

	return true;
}

void LoginState::Clear()
{
}

void LoginState::Pause() {
}

void LoginState::Resume() {
}

void LoginState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event)
{
		if (event.button == sf::Mouse::Button::Left)
		{
			for (auto const & it : world_.buttons)
			{
				if(&it->GetComponent<ge::Sprite>() != nullptr)
				{
					sf::Sprite t(engine.Texture(it->GetComponent<ge::Sprite>().textureName));
					t.setPosition(it->GetComponent<ge::Position>().getPos().x, it->GetComponent<ge::Position>().getPos().y);
					if (t.getGlobalBounds().contains(static_cast<float>(event.x), static_cast<float>(event.y)))
					{
						switch (it->GetComponent<ge::Input>().id)
						{
							case CREATE:
              engine.PopState();
              engine.PushState("Create");
							break;
							case JOIN:
              engine.PopState();
              engine.PushState("Join");
							break;
              case CANCEL:
              engine.PopState();
              engine.ChangeState("Intro");
              break;
							default:
							break;
						}
					}
				}
			}
		}
}

void LoginState::HandleEvent(ge::GameEngine & engine, sf::Event const & event) {
	switch (event.type) {
		case sf::Event::MouseButtonPressed:
			HandleClick_(engine, event.mouseButton);
		default:
			break;
	}
}

void LoginState::Update(ge::GameEngine const & game)
{
}

void LoginState::Display(ge::GameEngine & engine, const float)
{
	for (auto const & it : world_.buttons)
	{
		sf::Text t(it->GetComponent<ge::Text>().text, engine.Font(it->GetComponent<ge::Text>().fontName));
		t.setPosition(it->GetComponent<ge::Position>().getPos().x, it->GetComponent<ge::Position>().getPos().y);
		engine.Draw(std::make_shared<sf::Text>(t), ge::Layer::UI);

		if(&it->GetComponent<ge::Sprite>() != nullptr)
		{
			sf::Sprite s(engine.Texture(it->GetComponent<ge::Sprite>().textureName));
			s.setPosition(it->GetComponent<ge::Position>().getPos().x, it->GetComponent<ge::Position>().getPos().y);
			engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<ge::Sprite>().priority);
		}
	}
}
