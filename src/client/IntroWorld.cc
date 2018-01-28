#include "IntroWorld.h"

void IntroWorld::CreateText(ge::Vector2f const & pos, std::string const & text, std::string const & font, int input, bool centered)
{
	std::unique_ptr<ge::GameObject> g = std::make_unique<ge::GameObject>();

	g->AddComponent<ge::Position>(pos);
	g->AddComponent<ge::Input>(input);
	g->AddComponent<ge::Text>(text, font, centered);

	this->texts.push_back(std::move(g));
}

void IntroWorld::CreateText(ge::Vector2f const & pos, std::string const & text, std::string const & font, bool centered)
{
	std::unique_ptr<ge::GameObject> g = std::make_unique<ge::GameObject>();

	g->AddComponent<ge::Position>(pos);
	g->AddComponent<ge::Text>(text, font, centered);

	this->texts.push_back(std::move(g));
}


void IntroWorld::CreateButton(ge::Vector2f const & pos, std::string const & font, int input, std::string const & imgName)
{
	std::unique_ptr<ge::GameObject> g = std::make_unique<ge::GameObject>();

	g->AddComponent<ge::Position>(pos);
	g->AddComponent<ge::Input>(input);
	g->AddComponent<ge::Sprite>(imgName, 1);

	this->buttons.push_back(std::move(g));
}

void IntroWorld::CreateBackground()
{
	this->background = std::make_unique<ge::GameObject>();

	background->AddComponent<ge::Position>(ge::Vector2f(0,0));
	background->AddComponent<ge::Animator>();
	ge::Animation scroll;
	scroll.priority = 1;
	scroll.speed = 50;
	bool done = false;
	for (uint32_t i = 0; i < 2; ++i)
	{
		for (uint32_t j = 0; j < 10; ++j)
		{
			for (uint32_t k = 0; k < 10; ++k)
			{
				scroll.sprites.push_back("resources/BackGround/frame_" + std::to_string(i) + std::to_string(j) + std::to_string(k) + "_delay-0.02s.gif");
				if (i == 1 && j == 2 && k == 7)
				{
					done = true;
					break;
				}
			}
			if (done)
				break;
		}
		if (done)
			break;
	}
	background->GetComponent<ge::Animator>()->AddAnimation("Scrolling", scroll);
	background->GetComponent<ge::Animator>()->SetAnimation("Scrolling");
}
