#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <vector>
#include <memory>
#include <stack>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <functional>
#include <queue>

#include "ResourcesManager.h"
#include "AGameState.h"

using PrioritizedDrawable = std::pair<int32_t , std::shared_ptr<sf::Drawable>>;

class GameEngine {
public:
	static constexpr int32_t UI = 0;
	static constexpr int32_t Background = -1;

	GameEngine();
	GameEngine(GameEngine const & other) = delete;
	GameEngine(GameEngine && other) = delete;
	~GameEngine();

	GameEngine & operator=(GameEngine const & other) = delete;
	GameEngine & operator=(GameEngine && other) = delete;

	bool Init(std::string const & title, uint32_t width, uint32_t height);

	void AddState(std::string const & name, std::shared_ptr<AGameState> const & state);
	void ChangeState(std::string const & stateName);
	void PushState(std::string const & stateName);
	void PopState();

	void Run(std::string const & initState);

	void Draw(std::shared_ptr<sf::Drawable> const & drawable, int32_t display_level);

	void Quit();

	ResourcesManager & Rm();

private:
	sf::RenderWindow & Window();
	void HandleEvents_();
	void Update_();
	void Display_(float interpolation);

	std::unordered_map<std::string, std::shared_ptr<AGameState>> states_;
	std::stack<std::shared_ptr<AGameState>> stack_;

	sf::RenderWindow window_;

	ResourcesManager rm_;

	std::priority_queue<PrioritizedDrawable,
			std::vector<PrioritizedDrawable>,
			std::function<bool(PrioritizedDrawable, PrioritizedDrawable)>> toDraw_;
};

#endif /*GAMEENGINE_H_*/
