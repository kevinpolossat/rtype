#include <vector>
#include <iostream>
#include "GameEngine.h"
#include "States/IntroState.h"
#include "States/PlayState.h"
#include "Entity/Component.h"
#include	"States/CreateState.h"
#include	"States/LoginState.h"
#include "States/JoinState.h"


int main() {
	ge::GameEngine gameEngine;
	if (gameEngine.Init("R-Type", 800, 600, false)) {
		gameEngine.AddState("Intro", std::make_shared<IntroState>());
		gameEngine.AddState("Play", std::make_shared<PlayState>());
		gameEngine.AddState("Create", std::make_shared<CreateState>());
		gameEngine.AddState("Login", std::make_shared<LoginState>());
		gameEngine.AddState("Join", std::make_shared<JoinState>());

		gameEngine.Run("Intro");
	}
	return 0;
}
