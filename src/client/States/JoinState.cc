#include "JoinState.h"

bool JoinState::Init(ge::GameEngine & engine)
{
	UpdateList(engine.GetSize());

	world_.CreateBackground();
	return true;
}
void JoinState::HandleKey_(ge::GameEngine & engine, sf::Event::TextEvent const & event){}

void JoinState::UpdateList(ge::Vector2u const & size)
{
	if (world_.texts.size() > 0)
		world_.texts.clear();
	ge::MenuValue &val = ge::MenuValue::Instance();
	_games = val.games;
	int i = 2;
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 10.f), "GAMES : ", "retro", NONE);
	for (auto const & it : _games)
	{
		world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 10.f * i), it, "retro", NONE + i - 1);
		i++;
	}
	world_.CreateText(ge::Vector2f(size.x / 5.f, size.y / 10.f * i + 2), "Cancel", "retro", CANCEL);
}

void JoinState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) {
	ge::MenuValue &val = ge::MenuValue::Instance();

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
							case NONE:
							break;
						default:
							val.j_game.value.gameId = val.gi[it->GetComponent<ge::Input>()->id - 10].gameId;
							val.j_game.value.port = val.Port;
							val.tcpConnection->sendToServer(val.j_game);
						_gamechose = _games[it->GetComponent<ge::Input>()->id - 10];
						std::cout << _gamechose << std::endl;
							break;
					}
				}
			}
		}
	}
}
