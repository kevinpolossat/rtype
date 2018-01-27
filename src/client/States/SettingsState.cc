#include "SettingsState.h"

bool SettingsState::Init(ge::GameEngine & engine) {
	engine.Load<ge::Resources::Font>("retro", "resources/PressStart2P.ttf");

	ge::Vector2f size = engine.GetSize();

	world_.CreateText(ge::Vector2f(size.x / 4.f, size.y / 5.f), "Resolution :", "retro", true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3 - 170, size.y / 5.f), "<", "retro", L_RESOLUTION, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3, size.y / 5.f), GetCurrentResolutionText_(engine), "retro", RESOLUTION, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3 + 170, size.y / 5.f), ">", "retro", P_RESOLUTION, true);

	world_.CreateText(ge::Vector2f(size.x / 4.f, size.y / 5.f * 2), "Fullscreen :", "retro", true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3 - 170, size.y / 5.f * 2), "<", "retro", L_FULLSCREEN, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3, size.y / 5.f * 2), GetCurrentFullscreenText_(engine), "retro", FULLSCREEN, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3 + 170, size.y / 5.f * 2), ">", "retro", P_FULLSCREEN, true);

	world_.CreateText(ge::Vector2f(size.x / 4.f, size.y / 5.f * 3), "Sound :", "retro", true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3 - 170, size.y / 5.f * 3), "<", "retro", L_SOUND, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3, size.y / 5.f * 3), GetCurrentSoundText_(engine), "retro", SOUND, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3 + 170, size.y / 5.f * 3), ">", "retro", P_SOUND, true);

	world_.CreateText(ge::Vector2f(size.x / 2.f, size.y / 5.f * 4), "Cancel", "retro", CANCEL, true);
	return true;
}

void SettingsState::ReduceResolution_(ge::GameEngine & engine) const {
	std::vector<ge::Vector2u> v = engine.GetResolutionsModes();
	for (uint32_t i = 0; i < v.size() - 1; ++i) {
		if (v[i] == engine.GetWindowSize()) {
			engine.SetSize(v[i + 1]);
			i = v.size();
		}
	}
}

void SettingsState::AugmentResolution_(ge::GameEngine & engine) const {
	std::vector<ge::Vector2u> v = engine.GetResolutionsModes();
	for (uint32_t i = 1; i < v.size(); ++i) {
		if (v[i] == engine.GetWindowSize()) {
			engine.SetSize(v[i - 1]);
			i = v.size();
		}
	}
}

void SettingsState::UpdateResolutionText_(ge::GameEngine & engine) {
	for (auto & text : world_.texts) {
		if (text->GetComponent<ge::Input>() && text->GetComponent<ge::Input>()->id == RESOLUTION) {
			text->GetComponent<ge::Text>()->text = GetCurrentResolutionText_(engine);
		}
	}
}

void SettingsState::HandleClickOnText_(ge::GameEngine & engine, ge::GameObject & obj) {
	switch (obj.GetComponent<ge::Input>()->id) {
		case L_RESOLUTION:
			ReduceResolution_(engine);
			UpdateResolutionText_(engine);
			break;
		case P_RESOLUTION:
			AugmentResolution_(engine);
			UpdateResolutionText_(engine);
			break;
		case CANCEL:
			HandleQuit_(engine);
			break;
		default:
			break;
	}
}

std::string SettingsState::GetCurrentResolutionText_(ge::GameEngine & engine) const {
	return std::to_string(engine.GetWindowSize().x) + "x" + std::to_string(engine.GetWindowSize().y);
}

std::string SettingsState::GetCurrentFullscreenText_(ge::GameEngine & engine) const {
	return engine.IsFullscreen() ? "Yes" : "No";
}

std::string SettingsState::GetCurrentSoundText_(ge::GameEngine & engine) const {
	return std::to_string(50);
}