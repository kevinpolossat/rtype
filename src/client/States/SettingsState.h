#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "MenuState.h"

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
};

#endif /*SETTINGS_STATE_H*/
