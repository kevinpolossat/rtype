#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include <SFML/Graphics.hpp>

#include "AGameState.h"
#include "PlayWorld.h"

class PlayState : public AGameState {
public:
	PlayState();
	PlayState(PlayState const & other) = delete;
	PlayState(PlayState const && other) = delete;
	~PlayState() = default;

	PlayState & operator=(PlayState const & other) = delete;
	PlayState & operator=(PlayState const && other) = delete;

	bool Init(GameEngine & engine) override;
	void Clear() override;

	void Pause() override;
	void Resume() override;

	void HandleEvents(GameEngine & engine) override;
	void Update(GameEngine const & engine) override;
	void Display(GameEngine & engine, const float interpolation) override;

private:
	void HandlePlayerMovement_(sf::Event::KeyEvent const & event);
	void HandleQuit_(GameEngine & engine, sf::Event::KeyEvent const & event);

	PlayWorld world_;
};

#endif /*PLAYSTATE_H_*/