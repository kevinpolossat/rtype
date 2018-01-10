#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include <SFML/Graphics.hpp>

#include "AGameState.h"
#include "PlayWorld.h"

class PlayState : public AGameState {
public:
	PlayState() = default;
	PlayState(PlayState const & other) = delete;
	PlayState(PlayState && other) = delete;
	~PlayState() override = default;

	PlayState & operator=(PlayState const & other) = delete;
	PlayState & operator=(PlayState && other) = delete;

	bool Init(GameEngine & engine) override;
	void Clear() override;

	void Pause() override;
	void Resume() override;

	void HandleEvent(GameEngine & engine, sf::Event const & event) override;
	void Update(GameEngine const & engine) override;
	void Display(GameEngine & engine, float interpolation) override;

private:
	void HandlePlayerMovement_(sf::Event::KeyEvent const & event);
	void HandleQuit_(GameEngine & engine, sf::Event::KeyEvent const & event);

	PlayWorld world_;
};

#endif /*PLAYSTATE_H_*/
