#include "IntroWorld.h"

void IntroWorld::CreateButton(Vector2D const & pos, std::string text, std::string font, int input)
{
	GameObject * g = new GameObject();

	g->AddComponent<Position>(pos);
	g->AddComponent<Text>(text, font);
	g->AddComponent<Input>(input);

	this->buttons.push_back(g);
}