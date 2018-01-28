#include "StatesManager.h"

ge::StatesManager::~StatesManager() {
	while (!stack_.empty()) {
		stack_.top()->Clear();
		stack_.pop();
	}
}

void ge::StatesManager::SetDefaultState(std::string const & name) {
	defaultState_ = name;
}

void ge::StatesManager::AddState(std::string const & name, const std::shared_ptr<ge::AGameState> & state) {
	states_.insert(std::make_pair(name, state));
}

void ge::StatesManager::ChangeState(ge::GameEngine & engine, std::string const & stateName) {
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

void ge::StatesManager::PushState(ge::GameEngine & engine, std::string const & stateName) {
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

void ge::StatesManager::PopState() {
	if (!stack_.empty()) {
		stack_.top()->Clear();
		stack_.pop();
	}
	if (!stack_.empty()) {
		stack_.top()->Resume();
	}
}

std::shared_ptr<ge::AGameState> & ge::StatesManager::GetCurrentState(ge::GameEngine & engine) {
	if (stack_.empty()) {
		ChangeState(engine, defaultState_);
	}
	return stack_.top();
}
