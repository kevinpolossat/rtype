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
			if (event.key.code == sf::Keyboard::Key::Escape) {
				HandleQuit_(engine);
			}
		break;
		default:
			break;
	}
}

void MenuState::Update(ge::GameEngine & game) {
}

void MenuState::Display(ge::GameEngine & engine, float) {
	//int i = 0;
	MenuValue &val = MenuValue::Instance();
	for (auto const & it : world_.texts) {
		engine.Draw(std::make_shared<sf::Text>(ToSFMLText_(engine, *it)), ge::Layer::UI);
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
			s.scale(4.6f, 4.6f);
			engine.Draw(std::make_shared<sf::Sprite>(s), 2);
		}
	}
}

void MenuState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) {
	if (event.button == sf::Mouse::Button::Left) {
		for (auto const & it : world_.texts) {
			if(it->GetComponent<ge::Text>()) {
				sf::Text t(ToSFMLText_(engine, *it));
				if (t.getGlobalBounds().contains(engine.GetCoord(static_cast<uint32_t >(event.x), static_cast<uint32_t >(event.y)))) {
					HandleClickOnText_(engine, *it);
				}
			}
		}
	}
}

void MenuState::HandleClickOnText_(ge::GameEngine & engine, ge::GameObject & obj) {
	if (obj.GetComponent<ge::Input>()->id != CANCEL && obj.GetComponent<ge::Input>()->id != QUIT) {
		engine.Play("menu_accept");
	}
}

void MenuState::HandleKey_(ge::GameEngine &engine, sf::Event::TextEvent const &event) {
}

void MenuState::HandleQuit_(ge::GameEngine & engine) {
	engine.Play("menu_cancel");
	engine.PopState();
}

sf::Text MenuState::ToSFMLText_(ge::GameEngine & engine, ge::GameObject & obj) const {
	sf::Text t(obj.GetComponent<ge::Text>()->text, engine.Font(obj.GetComponent<ge::Text>()->fontName));
	t.setPosition(obj.GetComponent<ge::Position>()->getPos().x, obj.GetComponent<ge::Position>()->getPos().y);
	if (obj.GetComponent<ge::Text>()->centered) {
		t.setOrigin(t.getGlobalBounds().width / 2, t.getGlobalBounds().height / 2);
	}
	return t;
}
