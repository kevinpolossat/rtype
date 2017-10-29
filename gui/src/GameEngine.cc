#include <iostream>
#include <chrono>

#include "GameEngine.h"
#include "IntroState.h"
#include "PlayState.h"

GameEngine::GameEngine() {
}

GameEngine::~GameEngine() {
	while (!states_.empty()) {
		states_.back()->Clear();
		states_.pop_back();
	}
}

bool GameEngine::Init(std::string const & title, uint32_t width, uint32_t height) {
	window_.create(sf::VideoMode(width, height), title);
	PushState(&IntroState::Instance());
	return true;
}

void GameEngine::ChangeState(IGameState * state) {
	// clear current state
	if (!states_.empty()) {
		states_.back()->Clear();
		states_.pop_back();
	}

	// store and init the new state
	states_.push_back(state);
	if (!states_.back()->Init()) {
		std::exit(EXIT_SUCCESS);
	}
}

void GameEngine::PushState(IGameState * state) {
	// pause current state
	if (!states_.empty()) {
		states_.back()->Pause();
	}

	// store and init the new state
	states_.push_back(state);
	if (!states_.back()->Init()) {
		std::exit(EXIT_SUCCESS);
	}
}

void GameEngine::PopState() {
	// cleanup the current state
	if (!states_.empty()) {
		states_.back()->Clear();
		states_.pop_back();
	}

	// resume previous state
	if (!states_.empty()) {
		states_.back()->Resume();
	}
}

void GameEngine::Run() {
	const int updatePerSecond = 25;
	const int msToSkip = 1000 / updatePerSecond;
	const int maxFrameSkip = 5;

	auto nextGameTick = std::chrono::high_resolution_clock::now();
	int loops;
	float interpolation;

	while (window_.isOpen()) {
		loops = 0;
		while (std::chrono::high_resolution_clock::now() > nextGameTick && loops < maxFrameSkip) {
			HandleEvents();
			Update();
			nextGameTick += std::chrono::milliseconds(msToSkip);
			++loops;
		}

		interpolation = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() + std::chrono::duration<float, std::milli>(msToSkip) - nextGameTick)
			/ std::chrono::duration<float, std::milli>(msToSkip);
		std::cout << interpolation << std::endl;
		Display(interpolation);
	}
}

void GameEngine::HandleEvents() {
	states_.back()->HandleEvents(*this);
}

void GameEngine::Update() {
	// let the state update the game
	states_.back()->Update(*this);
}

void GameEngine::Display(float const interpolation) {
	// let the state draw the screen
	window_.clear();
	states_.back()->Display(*this);
	window_.display();
}

sf::RenderWindow & GameEngine::Window() {
	return window_;
}
