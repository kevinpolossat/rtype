#include <iostream>
#include <chrono>

#include "GameEngine.h"
#include "IntroState.h"
#include "PlayState.h"

GameEngine::~GameEngine() {
	while (!stack_.empty()) {
		stack_.top()->Clear();
		stack_.pop();
	}
}

bool GameEngine::Init(std::string const & title, uint32_t width, uint32_t height) {
	window_.create(sf::VideoMode(width, height), title);
	window_.setView(sf::View(sf::FloatRect(0.f, 0.f, width, height)));
	return true;
}

void GameEngine::AddState(std::string const & name, std::shared_ptr<AGameState> const & state) {
	states_.insert(std::make_pair(name, state));
}

void GameEngine::ChangeState(std::string const & stateName) {
	// clear current state
	while (!stack_.empty()) {
		stack_.top()->Clear();
		stack_.pop();
	}

	// store and init the new state
	if (!states_.count(stateName)) {
		std::cerr << "Can't find " << stateName << " state" << std::endl;
		std::exit(EXIT_SUCCESS);
	}
	stack_.push(states_.at(stateName));
	if (!stack_.top()->Init(*this)) {
		std::cerr << "Can't init " << stateName << " state" << std::endl;
		std::exit(EXIT_SUCCESS);
	}
}

void GameEngine::PushState(std::string const & stateName) {
	// pause current state
	if (!stack_.empty()) {
		stack_.top()->Pause();
	}

	// store and init the new state
	if (!states_.count(stateName)) {
		std::cerr << "Can't find " << stateName << " state" << std::endl;
		std::exit(EXIT_SUCCESS);
	}
	stack_.push(states_.at(stateName));
	if (!stack_.top()->Init(*this)) {
		std::cerr << "Can't init " << stateName << " state" << std::endl;
		std::exit(EXIT_SUCCESS);
	}
}

void GameEngine::PopState() {
	// cleanup the current state
	if (!stack_.empty()) {
		stack_.top()->Clear();
		stack_.pop();
	}

	// resume previous state
	if (!stack_.empty()) {
		stack_.top()->Resume();
	}
}

void GameEngine::Run(std::string const & initState) {
	PushState(initState);
	const int updatePerSecond = 25;
	const int msToSkip = 1000 / updatePerSecond;
	const int maxFrameSkip = 5;

	auto nextGameTick = std::chrono::high_resolution_clock::now();
	int loops;
	float interpolation;

	while (window_.isOpen()) {
		loops = 0;
		while (std::chrono::high_resolution_clock::now() > nextGameTick && loops < maxFrameSkip) {
			HandleEvents_();
			Update_();
			nextGameTick += std::chrono::milliseconds(msToSkip);
			++loops;
		}

		interpolation = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() + std::chrono::duration<float, std::milli>(msToSkip) - nextGameTick)
			/ std::chrono::duration<float, std::milli>(msToSkip);
		Display_(interpolation);
	}
}

void GameEngine::HandleEvents_() {
	stack_.top()->HandleEvents(*this);
}

void GameEngine::Update_() {
	// let the state update the game
	stack_.top()->Update(*this);
}

void GameEngine::Display_(const float interpolation) {
	// let the state draw the screen
	window_.clear();
	stack_.top()->Display(*this, interpolation);
	window_.display();
}

sf::RenderWindow & GameEngine::Window() {
	return window_;
}

ResourcesManager & GameEngine::Rm() {
	return rm_;
}
