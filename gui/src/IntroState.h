#ifndef INTROSTATE_H_
#define INTROSTATE_H_

#include <SFML\Graphics.hpp>

#include "IGameState.h"

class IntroState : public IGameState {
public:
	IntroState();
	IntroState(IntroState const & other) = delete;
	IntroState(IntroState const && other) = delete;
	~IntroState();

	IntroState & operator=(IntroState const & other) = delete;
	IntroState & operator=(IntroState const && other) = delete;

	bool Init() override;
	void Clear() override;

	void Pause() override;
	void Resume() override;

	void HandleEvents(GameEngine & game) override;
	void Update(GameEngine const & game) override;
	void Display(GameEngine & game) override;

	static IntroState & Instance();

private:
	static IntroState instance_;

	sf::Text text_;
	sf::Font font_;
};

#endif /*INTROSTATE_H_*/