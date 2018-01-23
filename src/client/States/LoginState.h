#ifndef LoginState_H_
#define LoginState_H_

#include <SFML/Graphics.hpp>

#include "MenuState.h"

class LoginState : public MenuState {
public:
	LoginState() = default;
	LoginState(LoginState const & other) = delete;
	LoginState(LoginState && other) = delete;
	~LoginState() override = default;

	LoginState & operator=(LoginState const & other) = delete;
	LoginState & operator=(LoginState && other) = delete;

	bool Init(ge::GameEngine & engine) override;

private:
	void HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) override;
	void HandleKey_(ge::GameEngine & engine, sf::Event::TextEvent const & event) override;

	std::string login = "";
};

#endif /*LoginState_H_*/
