#include "MenuState.h"

void MenuState::Clear()
{
	world_.buttons.clear();
	world_.texts.clear();
}

void MenuState::Pause() {
}

void MenuState::Resume() {
}

void MenuState::HandleEvent(ge::GameEngine & engine, sf::Event const & event) {
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
			HandleClick_(engine, event.mouseButton);
		break;
		case sf::Event::KeyPressed:
			HandleKey_(engine, event.text);
		break;
		default:
			break;
	}
}

void MenuState::Update(ge::GameEngine & game)
{

}

void MenuState::Display(ge::GameEngine & engine, float) {
	int i = 0;
	ge::MenuValue &val = ge::MenuValue::Instance();
	for (auto const & it : world_.texts) {
		sf::Text t(it->GetComponent<ge::Text>()->text, engine.Font(it->GetComponent<ge::Text>()->fontName));
		if(it->GetComponent<ge::Input>()->id > NONE)
		{
			if (i < val.games.size())
			{
				it->GetComponent<ge::Text>()->text = val.games[i];
				t.setPosition(it->GetComponent<ge::Position>()->getPos().x, it->GetComponent<ge::Position>()->getPos().y);
				engine.Draw(std::make_shared<sf::Text>(t), ge::Layer::UI);
			}
			else
				it->GetComponent<ge::Text>()->text = "";
			i++;
		}
		else
		 {
			 t.setPosition(it->GetComponent<ge::Position>()->getPos().x, it->GetComponent<ge::Position>()->getPos().y);
			 engine.Draw(std::make_shared<sf::Text>(t), ge::Layer::UI);
		 }
	}
	for (auto const & it : world_.buttons) {
		if(it->GetComponent<ge::Sprite>()) {
			sf::Sprite s(engine.Texture(it->GetComponent<ge::Sprite>()->textureName));
			s.setPosition(it->GetComponent<ge::Position>()->getPos().x, it->GetComponent<ge::Position>()->getPos().y);
			engine.Draw(std::make_shared<sf::Sprite>(s), it->GetComponent<ge::Sprite>()->priority);
		}
	}
	if (world_.background)
	{
		if (world_.background->GetComponent<ge::Animator>())
		{
			sf::Sprite s(engine.Texture(world_.background->GetComponent<ge::Animator>()->GetSprite()));
			s.setPosition(0, 0);
			s.scale(1.8f, 1.8f);
			engine.Draw(std::make_shared<sf::Sprite>(s), 2);
		}
	}
}
