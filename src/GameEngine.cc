#include "GameEngine.h"

GameEngine::GameEngine()
		: toDraw_([](PrioritizedDrawable const & d1, PrioritizedDrawable const & d2) { return d1.first < d2.first; }) {
}

GameEngine::~GameEngine() {
	while (!stack_.empty()) {
		stack_.top()->Clear();
		stack_.pop();
	}
}

bool GameEngine::Init(std::string const & title, uint32_t width, uint32_t height) {
	window_.create(sf::VideoMode(width, height), title);
	window_.setView(sf::View(sf::FloatRect(0.f, 0.f, width, height)));
	return true;
}

void GameEngine::AddState(std::string const & name, std::shared_ptr<AGameState> const & state) {
	states_.insert(std::make_pair(name, state));
}

void GameEngine::ChangeState(std::string const & stateName) {
	while (!stack_.empty()) {
		stack_.top()->Clear();
		stack_.pop();
	}
	if (!states_.count(stateName)) {
		std::cerr << "Can't find " << stateName << " state" << std::endl;
		std::exit(EXIT_SUCCESS);
	}
	stack_.push(states_.at(stateName));
	if (!stack_.top()->Init(*this)) {
		std::cerr << "Can't init " << stateName << " state" << std::endl;
		std::exit(EXIT_SUCCESS);
	}
}

void GameEngine::PushState(std::string const & stateName) {
	if (!stack_.empty()) {
		stack_.top()->Pause();
	}
	if (!states_.count(stateName)) {
		std::cerr << "Can't find " << stateName << " state" << std::endl;
		std::exit(EXIT_SUCCESS);
	}
	stack_.push(states_.at(stateName));
	if (!stack_.top()->Init(*this)) {
		std::cerr << "Can't init " << stateName << " state" << std::endl;
		std::exit(EXIT_SUCCESS);
	}
}

void GameEngine::PopState() {
	if (!stack_.empty()) {
		stack_.top()->Clear();
		stack_.pop();
	}
	if (!stack_.empty()) {
		stack_.top()->Resume();
	}
}

void GameEngine::Run(std::string const & initState) {
	PushState(initState);
	const int updatePerSecond = 25;
	const int msToSkip = 1000 / updatePerSecond;
	const int maxFrameSkip = 5;

	auto nextGameTick = std::chrono::high_resolution_clock::now();
	int loops;
	float interpolation;

	while (window_.isOpen()) {
		loops = 0;
		while (std::chrono::high_resolution_clock::now() > nextGameTick && loops < maxFrameSkip) {
			HandleEvents_();
			Update_();
			nextGameTick += std::chrono::milliseconds(msToSkip);
			++loops;
		}

		interpolation = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() + std::chrono::duration<float, std::milli>(msToSkip) - nextGameTick)
		                / std::chrono::duration<float, std::milli>(msToSkip);
		Display_(interpolation);
	}
}

void GameEngine::HandleEvents_() {
	sf::Event event;
	while (window_.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				Quit();
				break;
			default:
				stack_.top()->HandleEvent(*this, event);
				break;
		}
	}
}

void GameEngine::Update_() {
	stack_.top()->Update(*this);
}

void GameEngine::Display_(const float interpolation) {
	window_.clear();
	stack_.top()->Display(*this, interpolation);
	while (!toDraw_.empty()) {
		window_.draw(*toDraw_.top().second);
		toDraw_.pop();
	}
	window_.display();
}

sf::RenderWindow & GameEngine::Window() {
	return window_;
}

ResourcesManager & GameEngine::Rm() {
	return rm_;
}

void GameEngine::Draw(std::shared_ptr<sf::Drawable> const & drawable, int32_t const display_level) {
	toDraw_.push(PrioritizedDrawable(display_level, drawable));
}

void GameEngine::Quit() {
	window_.close();
}
