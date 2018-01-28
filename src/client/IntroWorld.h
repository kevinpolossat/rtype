#ifndef WORLD_H_
#define WORLD_H_

#include "AWorld.h"

class IntroWorld : public ge::AWorld {
public:
	IntroWorld() = default;
	IntroWorld(IntroWorld const & other) = delete;
	IntroWorld(IntroWorld && other) = delete;
	~IntroWorld() override = default;

	IntroWorld & operator=(IntroWorld const & other) = delete;
	IntroWorld & operator=(IntroWorld && other) = delete;

	void CreateText(ge::Vector2f const & pos, std::string const & text, std::string const & font, int input, bool centered = false);
	void CreateText(ge::Vector2f const & pos, std::string const & text, std::string const & font, bool centered = false);
	void CreateButton(ge::Vector2f const & pos, std::string const & font, int input, std::string const & imgName);
	void CreateBackground();


	std::vector<std::unique_ptr<ge::GameObject>> buttons;
	std::vector<std::unique_ptr<ge::GameObject>> texts;
	std::vector<std::unique_ptr<ge::GameObject>> games;
	std::unique_ptr<ge::GameObject> background;
};

#endif /* WORLD_H_ */
