#ifndef INTROSTATE_H_
#define INTROSTATE_H_

#include <SFML/Graphics.hpp>

#include "MenuState.h"

class IntroState : public MenuState {
public:
	IntroState() = default;
	IntroState(IntroState const & other) = delete;
	IntroState(IntroState && other) = delete;
	~IntroState() override = default;

	IntroState & operator=(IntroState const & other) = delete;
	IntroState & operator=(IntroState && other) = delete;

	bool Init(ge::GameEngine & engine) override;

private:
	void HandleClickOnText_(ge::GameEngine & engine, ge::GameObject & obj) override;
	void HandleQuit_(ge::GameEngine &engine) override;
};

#endif /*INTROSTATE_H_*/
