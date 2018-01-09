#ifndef AGAMESTATE_H_
#define AGAMESTATE_H_

#include "AWorld.h"

class GameEngine;

class AGameState {
public:
	AGameState() = default;
	AGameState(AGameState const & other) = delete;
	AGameState(AGameState const && other) = delete;
	virtual ~AGameState() = default;

	AGameState & operator=(AGameState & other) = delete;
	AGameState & operator=(AGameState && other) = delete;

	virtual bool Init(GameEngine & engine) = 0;
	virtual void Clear() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvent(GameEngine & engine, sf::Event const & event) = 0;
	virtual void Update(GameEngine const & engine) = 0;
	virtual void Display(GameEngine & engine, float interpolation) = 0;
};

#endif /*AGAMESTATE_H_*/