#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <vector>
#include <SFML\Graphics.hpp>

#include "IGameState.h"

class GameEngine {
public:
	GameEngine();
	GameEngine(GameEngine const & other) = delete;
	GameEngine(GameEngine const && other) = delete;
	~GameEngine();

	GameEngine & operator=(GameEngine const & other) = delete;
	GameEngine & operator=(GameEngine const && other) = delete;

	bool Init(std::string const & title, uint32_t width, uint32_t height);

	void ChangeState(IGameState * state);
	void PushState(IGameState * state);
	void PopState();

	void Run();

	void HandleEvents();
	void Update();
	void Display(float const interpolation);

	sf::RenderWindow & Window();

private:
	std::vector<IGameState *> states_;
	sf::RenderWindow window_;
};

#endif /*GAMEENGINE_H_*/