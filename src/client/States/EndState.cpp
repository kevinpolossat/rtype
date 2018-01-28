#include "EndState.h"

bool EndState::Init(ge::GameEngine & engine) {
	engine.Load<ge::Resources::Font>("arial", "resources/arial.ttf");
	engine.Load<ge::Resources::Font>("retro", "resources/PressStart2P.ttf");

	ge::Vector2f size = engine.GetSize();
	world_.CreateText(ge::Vector2f(size.x / 2 - 250, size.y / 5.f), "Fin de la partie", "retro", NONE);

	world_.CreateBackground();
	engine.Load(*world_.background->GetComponent<ge::Animator>());
	return true;
}
void EndState::HandleKey_(ge::GameEngine & engine, sf::Event::TextEvent const & event){}
void EndState::HandleClick_(ge::GameEngine & engine, sf::Event::MouseButtonEvent const & event) {}
