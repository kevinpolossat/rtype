#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include <SFML\Graphics.hpp>

#include "IGameState.h"

class PlayState : public IGameState {
public:
	PlayState();
	PlayState(PlayState const & other) = delete;
	PlayState(PlayState const && other) = delete;
	~PlayState();

	PlayState & operator=(PlayState const & other) = delete;
	PlayState & operator=(PlayState const && other) = delete;

	bool Init() override;
	void Clear() override;

	void Pause() override;
	void Resume() override;

	void HandleEvents(GameEngine & game) override;
	void Update(GameEngine const & game) override;
	void Display(GameEngine & game) override;

	static PlayState & Instance();

private:
	static PlayState instance_;

	sf::CircleShape circle_;
};

#endif /*PLAYSTATE_H_*/