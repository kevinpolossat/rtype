#include "SettingsState.h"

SettingsState::SettingsState(bool inGameSettings)
		: inGameSettings_(inGameSettings) {
}

bool SettingsState::Init(ge::GameEngine & engine) {
	engine.Load<ge::Resources::Font>("retro", "resources/PressStart2P.ttf");

	ge::Vector2f size = engine.GetSize();

	world_.CreateText(ge::Vector2f(size.x / 4.f, size.y / 6.f * 2), "Resolution :", "retro", NONE, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3 - 170, size.y / 6.f * 2), "<", "retro", L_RESOLUTION, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3, size.y / 6.f * 2), GetCurrentResolutionText_(engine), "retro", RESOLUTION, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3 + 170, size.y / 6.f * 2), ">", "retro", P_RESOLUTION, true);

	world_.CreateText(ge::Vector2f(size.x / 4.f, size.y / 6.f * 3), "Fullscreen :", "retro", NONE, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3 - 170, size.y / 6.f * 3), "<", "retro", L_FULLSCREEN, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3, size.y / 6.f * 3), GetCurrentFullscreenText_(engine), "retro", FULLSCREEN, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3 + 170, size.y / 6.f * 3), ">", "retro", P_FULLSCREEN, true);

	world_.CreateText(ge::Vector2f(size.x / 4.f, size.y / 6.f * 4), "Volume :", "retro", NONE, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3 - 170, size.y / 6.f * 4), "<", "retro", L_VOLUME, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3, size.y / 6.f * 4), GetCurrentVolumeText_(engine), "retro", VOLUME, true);
	world_.CreateText(ge::Vector2f(size.x / 4.f * 3 + 170, size.y / 6.f * 4), ">", "retro", P_VOLUME, true);

	if (inGameSettings_) {
		world_.CreateText(ge::Vector2f(size.x / 2.f, size.y / 6.f), "Resume", "retro", RESUME, true);
		world_.CreateText(ge::Vector2f(size.x / 2.f, size.y / 6.f * 5), "Quit", "retro", QUIT, true);
	} else {
		world_.CreateText(ge::Vector2f(size.x / 2.f, size.y / 6.f * 5), "Cancel", "retro", CANCEL, true);
	}
	world_.CreateBackground();
	engine.Load(*world_.background->GetComponent<ge::Animator>());
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

void SettingsState::ReduceVolume_(ge::GameEngine & engine) const {
	if (engine.GetVolume() > 0)
		engine.SetVolume(engine.GetVolume() - 5);
}

void SettingsState::AugmentVolume_(ge::GameEngine & engine) const {
	if (engine.GetVolume() < 100)
		engine.SetVolume(engine.GetVolume() + 5);
}

void SettingsState::UpdateResolutionText_(ge::GameEngine & engine) {
	for (auto & text : world_.texts) {
		if (text->GetComponent<ge::Input>() && text->GetComponent<ge::Input>()->id == RESOLUTION) {
			text->GetComponent<ge::Text>()->text = GetCurrentResolutionText_(engine);
		}
	}
}

void SettingsState::UpdateFullscreenText_(ge::GameEngine & engine) {
	for (auto & text : world_.texts) {
		if (text->GetComponent<ge::Input>() && text->GetComponent<ge::Input>()->id == FULLSCREEN) {
			text->GetComponent<ge::Text>()->text = GetCurrentFullscreenText_(engine);
		}
	}
}

void SettingsState::UpdateVolumeText_(ge::GameEngine & engine) {
	for (auto & text : world_.texts) {
		if (text->GetComponent<ge::Input>() && text->GetComponent<ge::Input>()->id == VOLUME) {
			text->GetComponent<ge::Text>()->text = GetCurrentVolumeText_(engine);
		}
	}
}

void SettingsState::HandleClickOnText_(ge::GameEngine & engine, ge::GameObject & obj) {
	MenuState::HandleClickOnText_(engine, obj);
	switch (obj.GetComponent<ge::Input>()->id) {
		case L_RESOLUTION:
			ReduceResolution_(engine);
			UpdateResolutionText_(engine);
			break;
		case P_RESOLUTION:
			AugmentResolution_(engine);
			UpdateResolutionText_(engine);
			break;
		case L_FULLSCREEN:
			engine.SetFullscreen(false);
			UpdateFullscreenText_(engine);
			break;
		case P_FULLSCREEN:
			engine.SetFullscreen(true);
			UpdateFullscreenText_(engine);
			break;
		case L_VOLUME:
			ReduceVolume_(engine);
			UpdateVolumeText_(engine);
			break;
		case P_VOLUME:
			AugmentVolume_(engine);
			UpdateVolumeText_(engine);
			break;
		case CANCEL:
		case RESUME:
			HandleQuit_(engine);
			break;
		case QUIT:
			engine.ChangeState("Intro");
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

std::string SettingsState::GetCurrentVolumeText_(ge::GameEngine & engine) const {
	return std::to_string(engine.GetVolume());
}
