#ifndef CreateState_H_
#define CreateState_H_

#include <SFML/Graphics.hpp>

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
};

#endif /*CreateState_H_*/
