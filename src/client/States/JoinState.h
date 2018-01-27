#ifndef JoinState_H_
#define JoinState_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "MenuValue.h"
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
	void UpdateList(ge::Vector2u const & size);

	std::vector<std::string> _games;
	std::string _gamechose = "";
};

#endif /*JoinState_H_*/
