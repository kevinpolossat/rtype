#include "LoginState.h"

bool LoginState::Init(ge::GameEngine & engine)
{
	ge::Vector2u size = engine.GetSize();
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f), "Login: " + login, "retro", NONE);
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f * 2), "Create",  "retro", CREATE);
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f * 3), "Join", "retro", JOIN);
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 5.f * 4), "Cancel", "retro", CANCEL);
	world_.CreateBackground();
	return true;
}

void LoginState::HandleKey_(ge::GameEngine & engine, sf::Event::TextEvent const & event)
{
	for (auto const & it : world_.texts)
	{
			if (it->GetComponent<ge::Text>()->text == ("Login: " + login) && event.unicode < 26)
			{
				login += v[event.unicode];
				it->GetComponent<ge::Text>()->text += v[event.unicode];
			}
	}
}

void LoginState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) {
	ge::MenuValue &val = ge::MenuValue::Instance();
	if (event.button == sf::Mouse::Button::Left) {
		for (auto const & it : world_.texts) {
		if(it->GetComponent<ge::Text>())
		{
			sf::Text t(it->GetComponent<ge::Text>()->text, engine.Font(it->GetComponent<ge::Text>()->fontName));
			t.setPosition(it->GetComponent<ge::Position>()->getPos().x, it->GetComponent<ge::Position>()->getPos().y);
				if (t.getGlobalBounds().contains(static_cast<float>(event.x), static_cast<float>(event.y))) {
					switch (it->GetComponent<ge::Input>()->id) {
						case CREATE:
							val.c_game.value.playerName = login;
							login = "";
							engine.PushState("Create");
							break;
						case JOIN:
							val.j_game.value.playerName = login;
							login = "";
							val.tcpConnection->sendToServer<rtype::protocol_tcp::QueryList>(val.l_game);
							engine.PushState("Join");
							break;
						case CANCEL:
						login = "";
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
