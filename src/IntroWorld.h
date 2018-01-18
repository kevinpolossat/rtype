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

	void CreateButton(ge::Vector2f const & pos, std::string const & text, std::string const & font, int input);

	std::vector<std::unique_ptr<ge::GameObject>> buttons;
};

#endif /* WORLD_H_ */
