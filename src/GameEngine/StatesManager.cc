#include "StatesManager.h"

ge::StateManager::~StateManager() {
	while (!stack_.empty()) {
		stack_.top()->Clear();
		stack_.pop();
	}
}

void ge::StateManager::AddState(std::string const & name, const std::shared_ptr<ge::AGameState> & state) {
	states_.insert(std::make_pair(name, state));
}

void ge::StateManager::ChangeState(ge::GameEngine & engine, std::string const & stateName) {
	while (!stack_.empty()) {
		stack_.top()->Clear();
		stack_.pop();
	}
	if (!states_.count(stateName)) {
		std::cerr << "Can't find " << stateName << " state" << std::endl;
		engine.Quit();
	}
	stack_.push(states_.at(stateName));
	if (!stack_.top()->Init(engine)) {
		std::cerr << "Can't init " << stateName << " state" << std::endl;
		engine.Quit();
	}
}

void ge::StateManager::PushState(ge::GameEngine & engine, std::string const & stateName) {
	if (!stack_.empty()) {
		stack_.top()->Pause();
	}
	if (!states_.count(stateName)) {
		std::cerr << "Can't find " << stateName << " state" << std::endl;
		engine.Quit();
	}
	stack_.push(states_.at(stateName));
	if (!stack_.top()->Init(engine)) {
		std::cerr << "Can't init " << stateName << " state" << std::endl;
		engine.Quit();
	}
}

void ge::StateManager::PopState() {
	if (!stack_.empty()) {
		stack_.top()->Clear();
		stack_.pop();
	}
	if (!stack_.empty()) {
		stack_.top()->Resume();
	}
}

std::shared_ptr<ge::AGameState> & ge::StateManager::GetCurrentState() {
	return stack_.top();
}
