#ifndef LoginState_H_
#define LoginState_H_

#include <SFML/Graphics.hpp>

#include "AGameState.h"
#include "IntroWorld.h"
#include "GameEngine.h"


class LoginState : public ge::AGameState {
	enum ButtonId
  {
    CREATE,
    JOIN,
    CANCEL,
    NONE
	};

public:
	LoginState() = default;
	LoginState(LoginState const & other) = delete;
	LoginState(LoginState && other) = delete;
	~LoginState() override = default;

	LoginState & operator=(LoginState const & other) = delete;
	LoginState & operator=(LoginState && other) = delete;

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

#endif /*LoginState_H_*/
