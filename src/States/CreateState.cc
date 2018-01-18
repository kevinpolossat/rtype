#include "CreateState.h"

bool CreateState::Init(ge::GameEngine & engine) {
	engine.Load<ge::Resources::Font>("arial", "resources/arial.ttf");
	engine.Load<ge::Resources::Texture>("moins", "resources/Buttons/button_moins.png");
	engine.Load<ge::Resources::Texture>("plus", "resources/Buttons/button_plus.png");
	engine.Load<ge::Resources::Texture>("valid", "resources/Buttons/button_validg.png");
  engine.Load<ge::Resources::Texture>("cancel", "resources/Buttons/button_cancel.png");

	ge::Vector2u size = engine.GetSize();
  world_.CreateButton(ge::Vector2f(size.x / 5, 0), "Name Game : ", "arial", PLUS);
	world_.CreateButton(ge::Vector2f(size.x / 5, size.y / 5), "", "arial", PLUS, "moins");
  world_.CreateButton(ge::Vector2f(size.x / 5 * 2, size.y / 5), std::to_string(nbPlayers), "arial", NONE);
  world_.CreateButton(ge::Vector2f(size.x / 5 * 3, size.y / 5), "", "arial", MOINS, "plus");
	world_.CreateButton(ge::Vector2f(size.x / 5, size.y / 5 * 2), "", "arial", VALID, "valid");
  world_.CreateButton(ge::Vector2f(size.x / 5, size.y / 5 * 3), "", "arial", CANCEL, "cancel");
	return true;
}

void CreateState::Clear()
{
}

void CreateState::Pause() {
}

void CreateState::Resume() {
}

void CreateState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event)
{
		if (event.button == sf::Mouse::Button::Left)
		{
			for (auto const & it : world_.buttons)
			{
				if(&it->GetComponent<ge::Sprite>() != NULL)
				{
					sf::Sprite t(engine.Texture(it->GetComponent<ge::Sprite>().textureName));
					t.setPosition(it->GetComponent<ge::Position>().getPos().x, it->GetComponent<ge::Position>().getPos().y);
					if (t.getGlobalBounds().contains(static_cast<float>(event.x), static_cast<float>(event.y)))
					{
						switch (it->GetComponent<ge::Input>().id)
						{
							case PLUS:
              if (nbPlayers < 4)
              {
                nbPlayers++;
              }
							break;
							case MOINS:
                if (nbPlayers > 1)
                {
                  nbPlayers--;
                }
							break;
              case VALID:
              engine.PushState("Play");
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

void CreateState::HandleEvent(ge::GameEngine & engine, sf::Event const & event) {
	switch (event.type) {
		case sf::Event::MouseButtonPressed:
			HandleClick_(engine, event.mouseButton);
		default:
			break;
	}
}

void CreateState::Update(ge::GameEngine const & game)
{
}

void CreateState::Display(ge::GameEngine & engine, const float)
{
	for (auto const & it : world_.buttons)
	{
		sf::Text t(it->GetComponent<ge::Text>().text, engine.Font(it->GetComponent<ge::Text>().fontName));
		t.setPosition(it->GetComponent<ge::Position>().getPos().x, it->GetComponent<ge::Position>().getPos().y);
		engine.Draw(std::make_shared<sf::Text>(t), ge::Layer::UI);

		if(&it->GetComponent<ge::Sprite>() != NULL)
		{
			sf::Sprite s(engine.Texture(it->GetComponent<ge::Sprite>().textureName));
			s.setPosition(it->GetComponent<ge::Position>().getPos().x, it->GetComponent<ge::Position>().getPos().y);
			engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<ge::Sprite>().priority);
		}
	}
}
