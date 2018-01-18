#ifndef CreateState_H_
#define CreateState_H_

#include <SFML/Graphics.hpp>

#include "AGameState.h"
#include "IntroWorld.h"
#include "GameEngine.h"


class CreateState : public ge::AGameState {
	enum ButtonId
  {
		PLUS,
    MOINS,
    VALID,
    NONE,
    CANCEL
	};

public:
	CreateState() = default;
	CreateState(CreateState const & other) = delete;
	CreateState(CreateState && other) = delete;
	~CreateState() override = default;

	CreateState & operator=(CreateState const & other) = delete;
	CreateState & operator=(CreateState && other) = delete;

	bool Init(ge::GameEngine & engine) override;
	void Clear() override;
	void Pause() override;
	void Resume() override;

	void HandleEvent(ge::GameEngine & engine, sf::Event const & event) override;
	void Update(ge::GameEngine const & engine) override;
	void Display(ge::GameEngine & engine, float interpolation) override;

private:
	void HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event);

  int nbPlayers = 1;
	IntroWorld world_;
};

#endif /*CreateState_H_*/
