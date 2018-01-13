#ifndef STATES_MANAGER_H
#define STATES_MANAGER_H

#include <memory>
#include <unordered_map>
#include <queue>
#include <stack>
#include <iostream>

#include "AGameState.h"
#include "GameEngine.h"

namespace ge {
	class StateManager {
	public:
		StateManager() = default;
		StateManager(StateManager const & other) = delete;
		StateManager(StateManager && other) = delete;
		~StateManager();

		StateManager & operator=(StateManager const & other) = delete;
		StateManager & operator=(StateManager && other) = delete;

		void AddState(std::string const & name, std::shared_ptr<AGameState> const & state);
		void ChangeState(ge::GameEngine & engine, std::string const & stateName);
		void PushState(ge::GameEngine & engine, std::string const & stateName);
		void PopState();

		std::shared_ptr<ge::AGameState> & GetCurrentState();

	private:

		std::unordered_map<std::string, std::shared_ptr<AGameState>> states_;
		std::stack<std::shared_ptr<AGameState>> stack_;
	};
}

#endif /*STATES_MANAGER_H*/
