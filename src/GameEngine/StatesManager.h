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
	class StatesManager {
	public:
		StatesManager() = default;
		StatesManager(StatesManager const & other) = delete;
		StatesManager(StatesManager && other) = delete;
		~StatesManager();

		StatesManager & operator=(StatesManager const & other) = delete;
		StatesManager & operator=(StatesManager && other) = delete;

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
