#include <vector>
#include <iostream> 
#include "GameEngine.h"
#include "IntroState.h"
#include "PlayState.h"
#include "Entity/Component.h"

int main() {
	ge::GameEngine gameEngine;
	
	if (gameEngine.Init("R-Type", 800, 600)) {
		gameEngine.AddState("Intro", std::make_shared<IntroState>());
		gameEngine.AddState("Play", std::make_shared<PlayState>());
		gameEngine.Run("Intro");
	}
	return 0;
}
