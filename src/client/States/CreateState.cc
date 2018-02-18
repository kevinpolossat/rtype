#include "CreateState.h"

bool CreateState::Init(ge::GameEngine & engine)
{
	ge::Vector2f size = engine.GetSize();
	world_.CreateText(ge::Vector2f(size.x / 2.f, size.y / 5.f), "Number of players :", "retro", NONE, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f, size.y / 5.f * 2), "-", "retro", LESS, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 2, size.y / 5.f * 2), std::to_string(nbPlayers), "retro", NONE, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3, size.y / 5.f * 2), "+", "retro", PLUS, true);
	world_.CreateText(ge::Vector2f(size.x / 2.f, size.y / 5.f * 3), "Valid", "retro", VALID, true);
	world_.CreateText(ge::Vector2f(size.x / 2.f, size.y / 5.f * 4), "Cancel",  "retro", CANCEL, true);
	world_.CreateBackground();
	nameGame = "";
	nbPlayers = 1;

	return true;
}

void CreateState::HandleClickOnText_(ge::GameEngine & engine, ge::GameObject & obj) {
	MenuState::HandleClickOnText_(engine, obj);
	MenuValue &val = MenuValue::Instance();
	switch (obj.GetComponent<ge::Input>()->id) {
		case PLUS:
			if (nbPlayers < 4) {
				for (auto const & it : world_.texts) {
					if(it->GetComponent<ge::Text>()->text == std::to_string(nbPlayers)) {
						++nbPlayers;
						it->GetComponent<ge::Text>()->text = std::to_string(nbPlayers);
					}
				}
			}
			break;
		case LESS:
			if (nbPlayers > 1) {
				for (auto const & it : world_.texts) {
					if(it->GetComponent<ge::Text>()->text == std::to_string(nbPlayers)) {
						--nbPlayers;
						it->GetComponent<ge::Text>()->text = std::to_string(nbPlayers);
					}
				}
			}
			break;
		case VALID:
			val.c_game.value.nameGame = nameGame;
			val.c_game.value.nbPlayerMax = nbPlayers;
			val.c_game.value.port = val.Port;
			val.tcpConnection->sendToServer(val.c_game);
			engine.PushState("Waiting");
			break;
		case CANCEL:
			HandleQuit_(engine);
			break;
		default:
			break;
	}
}
