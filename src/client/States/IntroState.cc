#include "IntroState.h"

bool IntroState::Init(ge::GameEngine & engine) {
	engine.Load<ge::Resources::Font>("arial", "resources/arial.ttf");
	engine.Load<ge::Resources::Font>("retro", "resources/PressStart2P.ttf");

	ge::Vector2u size = engine.GetSize();
	world_.CreateText(ge::Vector2f(size.x / 2, size.y / 5.f), "Play", "retro", START, true);
	world_.CreateText(ge::Vector2f(size.x / 2, size.y / 5.f * 2), "Settings", "retro", SETTINGS, true);
	world_.CreateText(ge::Vector2f(size.x / 2, size.y / 5.f * 3), "Quit", "retro", QUIT, true);

	world_.CreateBackground();
	engine.Load(*world_.background->GetComponent<ge::Animator>());
	return true;
}

void IntroState::HandleClickOnText_(ge::GameEngine &engine, ge::GameObject &obj) {
	switch (obj.GetComponent<ge::Input>()->id) {
		case START:
			engine.PushState("Login");
			break;
		case SETTINGS:
			engine.PushState("Settings");
			break;
		case QUIT:
			engine.Quit();
			break;
		default:
			break;
	}
}

void IntroState::HandleQuit_(ge::GameEngine & engine) {
	engine.Quit();
}
