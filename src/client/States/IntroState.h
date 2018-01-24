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
	void HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) override;
	void HandleKey_(ge::GameEngine & engine, sf::Event::TextEvent const & event) override;
};

#endif /*INTROSTATE_H_*/
