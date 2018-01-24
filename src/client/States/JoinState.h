#ifndef JoinState_H_
#define JoinState_H_

#include <SFML/Graphics.hpp>
#include <vector>

#include "MenuState.h"

class JoinState : public MenuState {
public:
	JoinState() = default;
	JoinState(JoinState const & other) = delete;
	JoinState(JoinState && other) = delete;
	~JoinState() override = default;

	JoinState & operator=(JoinState const & other) = delete;
	JoinState & operator=(JoinState && other) = delete;

	bool Init(ge::GameEngine & engine) override;

private:
	void HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) override;
	void HandleKey_(ge::GameEngine & engine, sf::Event::TextEvent const & event) override;

	std::vector<std::string> _games;
};

#endif /*JoinState_H_*/
