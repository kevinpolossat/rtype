#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "MenuState.h"
#include "Settings.h"

class SettingsState : public MenuState {
public:
	SettingsState() = default;
	SettingsState(SettingsState const & other) = delete;
	SettingsState(SettingsState && other) = delete;
	~SettingsState() override = default;

	SettingsState & operator=(SettingsState const & other) = delete;
	SettingsState & operator=(SettingsState && other) = delete;

	bool Init(ge::GameEngine & engine) override;

private:
	void HandleClickOnText_(ge::GameEngine & engine, ge::GameObject & obj) override;

	void UpdateResolutionText_(ge::GameEngine & engine);
	std::string GetCurrentResolutionText_(ge::GameEngine & engine) const;
	std::string GetCurrentFullscreenText_(ge::GameEngine & engine) const;
	std::string GetCurrentSoundText_(ge::GameEngine & engine) const;

	void ReduceResolution_(ge::GameEngine & engine) const;
	void AugmentResolution_(ge::GameEngine & engine) const;
};

#endif /*SETTINGS_STATE_H*/
