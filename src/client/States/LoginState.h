#ifndef LoginState_H_
#define LoginState_H_

#include <SFML/Graphics.hpp>
#include "MenuState.h"
#include "MenuValue.h"

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
	void HandleClickOnText_(ge::GameEngine & engine, ge::GameObject & obj) override;
	void HandleKey_(ge::GameEngine & engine, sf::Event::TextEvent const & event) override;
	ge::MenuValue *val;
	std::string login = "";
	std::vector<char> v = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
	'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
};

#endif /*LoginState_H_*/
