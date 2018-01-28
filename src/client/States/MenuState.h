#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "client/IntroWorld.h"
#include "AGameState.h"
#include "GameEngine.h"
#include "MenuValue.h"

class MenuState : public ge::AGameState {
public:
	MenuState() = default;
	MenuState(MenuState const & other) = delete;
	MenuState(MenuState && other) = delete;
	~MenuState() override = default;

	MenuState & operator=(MenuState const & other) = delete;
	MenuState & operator=(MenuState && other) = delete;

	bool Init(ge::GameEngine & engine) override = 0;
	void Clear() override;

	void Pause() override;
	void Resume() override;

	void HandleEvent(ge::GameEngine & engine, sf::Event const & event) override;
	void Update(ge::GameEngine & engine) override;
	void Display(ge::GameEngine & engine, float interpolation) override;

protected:
	enum ButtonId
	{
		START = 0,
		CREATE,
		JOIN,
		SETTINGS,
		LESS,
		PLUS,
		L_RESOLUTION,
		RESOLUTION,
		P_RESOLUTION,
		L_FULLSCREEN,
		FULLSCREEN,
		P_FULLSCREEN,
		L_VOLUME,
		VOLUME,
		P_VOLUME,
		VALID,
		CANCEL,
		QUIT,
		NONE
	};

	virtual void HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event);
	virtual void HandleClickOnText_(ge::GameEngine & engine, ge::GameObject & obj);
	virtual	void HandleKey_(ge::GameEngine & engine, sf::Event::TextEvent const & event);
	virtual void HandleQuit_(ge::GameEngine &engine);

	sf::Text ToSFMLText_(ge::GameEngine & engine, ge::GameObject & obj) const;

	IntroWorld world_;
};

#endif /*MENU_STATE_H*/
