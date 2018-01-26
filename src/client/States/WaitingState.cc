#include "WaitingState.h"

bool WaitingState::Init(ge::GameEngine & engine)
{
  std::string story = "Did you ever hear the tragedy of Darth Plagueis \"the wise\"?\nI thought not. It s not a story the Jedi would tell you.\n It s a Sith legend. Darth Plagueis was a Dark Lord of the Sith,\nso powerful and so wise he could use the Force to influence the midichlorians to create life...\nHe had such a knowledge of the dark side that he could even keep the ones he cared about from dying.\nThe dark side of the Force is a pathway to many abilities some consider to be unnatural.\nHe became so powerful...\nthe only thing he was afraid of was losing his power, which eventually, of course, he did.\nUnfortunately, he taught his apprentice everything he knew, then his apprentice killed him in his sleep.\nIt s ironic he could save others from death, but not himself.";
	ge::Vector2u size = engine.GetSize();
	world_.CreateText(ge::Vector2f(0.f, 0.f),  story , "arial", NONE);
	world_.CreateBackground();
	return true;
}

void WaitingState::HandleKey_(ge::GameEngine & engine, sf::Event::TextEvent const & event)
{
}

void WaitingState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) {
	ge::MenuValue &val = ge::MenuValue::Instance();
	if (event.button == sf::Mouse::Button::Left) {
		for (auto const & it : world_.texts) {
		if(it->GetComponent<ge::Text>())
		{
			sf::Text t(it->GetComponent<ge::Text>()->text, engine.Font(it->GetComponent<ge::Text>()->fontName));
			t.setPosition(it->GetComponent<ge::Position>()->getPos().x, it->GetComponent<ge::Position>()->getPos().y);
				if (t.getGlobalBounds().contains(static_cast<float>(event.x), static_cast<float>(event.y))) {
					switch (it->GetComponent<ge::Input>()->id) {
						case NONE:
							break;
					}
				}
			}
		}
	}
}
