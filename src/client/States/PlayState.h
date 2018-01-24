#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include <SFML/Graphics.hpp>

#include "GameEngine.h"
#include "AGameState.h"
#include "PlayWorld.h"
#include "IArtificialIntelligence.hpp"

using ge::Velocity;
using ge::Position;
using ge::Sprite;
using ge::Collider;
using ge::Ia;

class PlayState : public ge::AGameState {
public:
	PlayState() = default;
	PlayState(PlayState const & other) = delete;
	PlayState(PlayState && other) = delete;
	~PlayState() override = default;

	PlayState & operator=(PlayState const & other) = delete;
	PlayState & operator=(PlayState && other) = delete;

	bool Init(ge::GameEngine & engine) override;
	void Clear() override;

	void Pause() override;
	void Resume() override;

	void HandleEvent(ge::GameEngine & engine, sf::Event const & event) override;
	void Update(ge::GameEngine & engine) override;
	void Display(ge::GameEngine & engine, float interpolation) override;

private:
	void HandlePlayerMovement_(ge::GameEngine const & engine, sf::Event::KeyEvent const & event);
	void HandlePlayerAnimation_(ge::GameEngine const & engine, sf::Event::KeyEvent const & event);
	void HandleQuit_(ge::GameEngine & engine, sf::Event::KeyEvent const & event);

	PlayWorld world_;
	std::chrono::time_point<std::chrono::high_resolution_clock> time_;

};

#endif /*PLAYSTATE_H_*/
