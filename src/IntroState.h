#ifndef INTROSTATE_H_
#define INTROSTATE_H_

#include <SFML/Graphics.hpp>

#include "AGameState.h"
#include "IntroWorld.h"

class IntroState : public AGameState {
	enum ButtonId {
		START,
		QUIT
	};

public:
	IntroState() = default;
	IntroState(IntroState const & other) = delete;
	IntroState(IntroState const && other) = delete;
	~IntroState() override = default;

	IntroState & operator=(IntroState const & other) = delete;
	IntroState & operator=(IntroState const && other) = delete;

	bool Init(GameEngine & engine) override;
	void Clear() override;

	void Pause() override;
	void Resume() override;

	void HandleEvent(GameEngine & engine, sf::Event const & event) override;
	void Update(GameEngine const & engine) override;
	void Display(GameEngine & engine, float interpolation) override;

private:
	void HandleClick_(GameEngine & engine, sf::Event::MouseButtonEvent const & event);
	
	IntroWorld world_;
};

#endif /*INTROSTATE_H_*/