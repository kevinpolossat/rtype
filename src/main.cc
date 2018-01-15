#include <vector>

#include "GameEngine.h"
#include "IntroState.h"
#include "PlayState.h"

int main() {
	ge::GameEngine gameEngine;
	if (gameEngine.Init("R-Type", 800, 600)) {
		gameEngine.AddComponents( {"Position", "Velocity", "Sprite", "Text", "Input", "PlayerTag"} );
		gameEngine.AddComposedComponents("Button", {"Position", "Text", "Input"} );
		gameEngine.AddComposedComponents("Drawable", {"Position", "Sprite"} );
		gameEngine.AddComposedComponents("AnimatedDrawable", {"Position", "ge::Animator"} );
		gameEngine.AddComposedComponents("Player", {"Position", "Velocity", "ge::Animator", "PlayerTag"} );
		gameEngine.AddState("Intro", std::make_shared<IntroState>());
		gameEngine.AddState("Play", std::make_shared<PlayState>());
		gameEngine.Run("Intro");
	}
	return 0;
}
