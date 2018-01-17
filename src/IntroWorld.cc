#include "IntroWorld.h"

void IntroWorld::CreateButton(Vector2D const & pos, std::string const & text, std::string const & font, int input)
{
	std::unique_ptr<GameObject> g;

	g->AddComponent<Position>(pos);
	g->AddComponent<Text>(text, font);
	g->AddComponent<Input>(input);

	this->buttons.push_back(std::move(g));
}