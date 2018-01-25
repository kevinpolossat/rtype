#ifndef CreateState_H_
#define CreateState_H_

#include <SFML/Graphics.hpp>
#include "MenuValue.h"
#include "MenuState.h"

class CreateState : public MenuState {
public:
	CreateState() = default;
	CreateState(CreateState const & other) = delete;
	CreateState(CreateState && other) = delete;
	~CreateState() override = default;

	CreateState & operator=(CreateState const & other) = delete;
	CreateState & operator=(CreateState && other) = delete;

	bool Init(ge::GameEngine & engine) override;

private:
	void HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) override;
	void HandleKey_(ge::GameEngine & engine, sf::Event::TextEvent const & event) override;
	int nbPlayers = 1;
	std::string nameGame = "";
	std::vector<char> v = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
	'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
};

#endif /*CreateState_H_*/
