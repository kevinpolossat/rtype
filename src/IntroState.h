#ifndef INTROSTATE_H_
#define INTROSTATE_H_

#include <SFML/Graphics.hpp>

#include "AGameState.h"
#include "IntroWorld.h"
#include "GameEngine.h"


class IntroState : public ge::AGameState {
	enum ButtonId {
		START,
		QUIT
	};

public:
	IntroState() = default;
	IntroState(IntroState const & other) = delete;
	IntroState(IntroState && other) = delete;
	~IntroState() override = default;

	IntroState & operator=(IntroState const & other) = delete;
	IntroState & operator=(IntroState && other) = delete;

	bool Init(ge::GameEngine & engine) override;
	void Clear() override;

	void Pause() override;
	void Resume() override;

	void HandleEvent(ge::GameEngine & engine, sf::Event const & event) override;
	void Update(ge::GameEngine const & engine) override;
	void Display(ge::GameEngine & engine, float interpolation) override;

private:
	void HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event);

	IntroWorld world_;
};

#endif /*INTROSTATE_H_*/
