#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <vector>
#include <memory>
#include <stack>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "ResourcesManager.h"
#include "AGameState.h"

class GameEngine {
public:
	GameEngine() = default;
	GameEngine(GameEngine const & other) = delete;
	GameEngine(GameEngine const && other) = delete;
	~GameEngine();

	GameEngine & operator=(GameEngine const & other) = delete;
	GameEngine & operator=(GameEngine const && other) = delete;

	bool Init(std::string const & title, uint32_t width, uint32_t height);

	void AddState(std::string const & name, std::shared_ptr<AGameState> const & state);
	void ChangeState(std::string const & stateName);
	void PushState(std::string const & stateName);
	void PopState();

	void Run(std::string const & initState);

	sf::RenderWindow & Window();
	ResourcesManager & Rm();

private:
	void HandleEvents_();
	void Update_();
	void Display_(float interpolation);

	std::unordered_map<std::string, std::shared_ptr<AGameState>> states_;
	std::stack<std::shared_ptr<AGameState>> stack_;
	sf::RenderWindow window_;
	ResourcesManager rm_;
};

#endif /*GAMEENGINE_H_*/