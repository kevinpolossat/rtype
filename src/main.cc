#include <vector>
#include <iostream> 
/*
#include "GameEngine.h"
#include "IntroState.h"
#include "PlayState.h"
*/
#include "Entity/Entity.h"

int main() {
	//ge::GameEngine gameEngine;

	GameObject test;

	test.AddComponent<Position>(Vector2D(10,5));
	auto & pos = test.GetComponent<Position>();
	std::cout << pos.getPos().x << std::endl;
	std::cin.get();
	
	/*if (gameEngine.Init("R-Type", 800, 600)) {
		gameEngine.AddComponents( {"Position", "Velocity", "Sprite", "Text", "Input", "PlayerTag"} );
		gameEngine.AddComposedComponents("Button", {"Position", "Text", "Input"} );
		gameEngine.AddComposedComponents("Drawable", {"Position", "Sprite"} );
		gameEngine.AddComposedComponents("AnimatedDrawable", {"Position", "ge::Animator"} );
		gameEngine.AddComposedComponents("Player", {"Position", "Velocity", "ge::Animator", "PlayerTag"} );
		gameEngine.AddState("Intro", std::make_shared<IntroState>());
		gameEngine.AddState("Play", std::make_shared<PlayState>());
		gameEngine.Run("Intro");
	}
	*/
	return 0;
}
