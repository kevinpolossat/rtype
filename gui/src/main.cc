#include "GameEngine.h"

int main() {
	GameEngine gameEngine;
	if (gameEngine.Init("R-Type", 800, 600)) {
		gameEngine.Run();
	}
	return 0;
}