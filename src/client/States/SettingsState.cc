#include "SettingsState.h"

bool SettingsState::Init(ge::GameEngine &engine) {
	engine.Load<ge::Resources::Font>("retro", "resources/PressStart2P.ttf");

	ge::Vector2u size = engine.GetSize();
	world_.CreateText(ge::Vector2f(size.x / 2, size.y / 5.f), "Resolution :", "retro", true);
	world_.CreateText(ge::Vector2f(size.x / 2, size.y / 5.f * 2), "Fullscreen :", "retro", true);
	world_.CreateText(ge::Vector2f(size.x / 2, size.y / 5.f * 3), "Sound :", "retro", true);
	world_.CreateText(ge::Vector2f(size.x / 2, size.y / 5.f * 4), "Cancel :", "retro", CANCEL, true);
	return true;
}

void SettingsState::HandleClickOnText_(ge::GameEngine & engine, ge::GameObject & obj) {
}