#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "client/IntroWorld.h"
#include "AGameState.h"
#include "GameEngine.h"

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
		PLUS,
		MOINS,
		VALID,
		CANCEL,
		QUIT,
		NONE
	};

	virtual void HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) = 0;
	virtual	void HandleKey_(ge::GameEngine & engine, sf::Event::TextEvent const & event) = 0;

	IntroWorld world_;
};

#endif /*MENU_STATE_H*/
