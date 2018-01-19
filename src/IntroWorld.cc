#include "IntroWorld.h"

void IntroWorld::CreateText(ge::Vector2f const & pos, std::string const & text, std::string const & font)
{
	std::unique_ptr<ge::GameObject> g = std::make_unique<ge::GameObject>();

	g->AddComponent<ge::Position>(pos);
	g->AddComponent<ge::Text>(text, font);

	this->texts.push_back(std::move(g));
}

void IntroWorld::CreateButton(ge::Vector2f const & pos, std::string const & font, int input, std::string imgName)
{
	std::unique_ptr<ge::GameObject> g = std::make_unique<ge::GameObject>();

	g->AddComponent<ge::Position>(pos);
	g->AddComponent<ge::Input>(input);
	g->AddComponent<ge::Sprite>(imgName, 1);

	this->buttons.push_back(std::move(g));
}
