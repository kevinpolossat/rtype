#include "LoginState.h"

bool LoginState::Init(ge::GameEngine & engine)
{
	ge::Vector2f size = engine.GetSize();
	world_.CreateText(ge::Vector2f(size.x / 2.f, size.y / 6.f), "Enter your login :", "retro", true);
	world_.CreateText(ge::Vector2f(size.x / 2.f, size.y / 6.f * 2), login, "retro", true);
	world_.CreateText(ge::Vector2f(size.x / 4.f, size.y / 6.f * 3), "Create",  "retro", CREATE, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3, size.y / 6.f * 3), "Join", "retro", JOIN, true);
	world_.CreateText(ge::Vector2f(size.x / 2.f, size.y / 6.f * 4), "Cancel", "retro", CANCEL, true);
	world_.CreateBackground();
	return true;
}

void LoginState::HandleKey_(ge::GameEngine & engine, sf::Event::TextEvent const & event)
{
	for (auto const & it : world_.texts)
	{
		if (it->GetComponent<ge::Text>()->text == login && event.unicode < 26)
		{
			login += v[event.unicode];
			it->GetComponent<ge::Text>()->text += v[event.unicode];
		}
	}
}

void LoginState::HandleClickOnText_(ge::GameEngine &engine, ge::GameObject &obj) {
	ge::MenuValue &val = ge::MenuValue::Instance();
	switch (obj.GetComponent<ge::Input>()->id) {
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
