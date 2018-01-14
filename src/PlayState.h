#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include <SFML/Graphics.hpp>

#include "GameEngine.h"
#include "AGameState.h"
#include "PlayWorld.h"

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
	void Update(ge::GameEngine const & engine) override;
	void Display(ge::GameEngine & engine, float interpolation) override;

private:
	void HandlePlayerMovement_(ge::GameEngine const & engine, sf::Event::KeyEvent const & event);
	void HandleQuit_(ge::GameEngine & engine, sf::Event::KeyEvent const & event);

	PlayWorld world_;
};

#endif /*PLAYSTATE_H_*/
