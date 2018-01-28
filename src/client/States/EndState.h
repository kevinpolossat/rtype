#ifndef ENDSTATE_H_
#define ENDSTATE_H_

#include <SFML/Graphics.hpp>

#include "MenuState.h"

class EndState : public MenuState {
public:
	EndState() = default;
	EndState(EndState const & other) = delete;
	EndState(EndState && other) = delete;
	~EndState() override = default;

	EndState & operator=(EndState const & other) = delete;
	EndState & operator=(EndState && other) = delete;

	bool Init(ge::GameEngine & engine) override;

private:
  void HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) override;
	void HandleKey_(ge::GameEngine & engine, sf::Event::TextEvent const & event) override;
};

#endif /*INTROSTATE_H_*/
