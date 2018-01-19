#ifndef JoinState_H_
#define JoinState_H_

#include <SFML/Graphics.hpp>
#include  <vector>
#include "AGameState.h"
#include "IntroWorld.h"
#include "GameEngine.h"


class JoinState : public ge::AGameState {
	enum ButtonId
  {
    VALID,
    NONE,
    CANCEL
	};

public:
	JoinState() = default;
	JoinState(JoinState const & other) = delete;
	JoinState(JoinState && other) = delete;
	~JoinState() override = default;

	JoinState & operator=(JoinState const & other) = delete;
	JoinState & operator=(JoinState && other) = delete;

	bool Init(ge::GameEngine & engine) override;
	void Clear() override;
	void Pause() override;
	void Resume() override;

	void HandleEvent(ge::GameEngine & engine, sf::Event const & event) override;
	void Update(ge::GameEngine const & engine) override;
	void Display(ge::GameEngine & engine, float interpolation) override;

private:
	void HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event);
  std::vector<std::string> _games;
	IntroWorld world_;
};

#endif /*JoinState_H_*/
