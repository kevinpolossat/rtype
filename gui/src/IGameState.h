#ifndef IGAMESTATE_H_
#define IGAMESTATE_H_

class GameEngine;

class IGameState {
public:
	virtual ~IGameState() {};

	IGameState & operator=(IGameState & other) = delete;
	IGameState & operator=(IGameState && other) = delete;

	virtual bool Init() = 0;
	virtual void Clear() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(GameEngine & game) = 0;
	virtual void Update(GameEngine const & game) = 0;
	virtual void Display(GameEngine & game) = 0;
};

#endif /*IGAMESTATE_H_*/