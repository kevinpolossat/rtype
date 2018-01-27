#include "JoinState.h"

bool JoinState::Init(ge::GameEngine & engine)
{
	UpdateList(engine.GetSize());

	world_.CreateBackground();
	return true;
}

void JoinState::UpdateList(ge::Vector2f const & size)
{
	if (world_.texts.size() > 0)
		world_.texts.clear();
	ge::MenuValue &val = ge::MenuValue::Instance();
	_games = val.games;
	int i = 2;
	world_.CreateText(ge::Vector2f(size.x / 2.f, size.y / 10.f), "GAMES :", "retro", true);
	for (auto const & it : _games)
	{
		world_.CreateText(ge::Vector2f(size.x / 2.f, size.y / 10.f * i), it, "retro", NONE + i - 1, true);
		i++;
	}
	world_.CreateText(ge::Vector2f(size.x / 2.f, size.y / 10.f * i + 2), "Cancel", "retro", CANCEL, true);
}

void JoinState::HandleClickOnText_(ge::GameEngine & engine, ge::GameObject & obj) {
	ge::MenuValue &val = ge::MenuValue::Instance();
	switch (obj.GetComponent<ge::Input>()->id) {
		case VALID:
			break;
		case CANCEL:
			engine.PopState();
			break;
		case NONE:
			break;
		default:
			val.j_game.value.gameId = val.gi[obj.GetComponent<ge::Input>()->id - 10].gameId;
			val.j_game.value.port = val.Port;
			val.tcpConnection->sendToServer(val.j_game);
			_gamechose = _games[obj.GetComponent<ge::Input>()->id - 10];
			std::cout << _gamechose << std::endl;
			break;
	}
}
