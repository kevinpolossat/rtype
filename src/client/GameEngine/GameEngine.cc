#include "GameEngine.h"
#include "Vector2D.h"

ge::GameEngine::GameEngine()
		: nm_(std::make_unique<ge::network::NetworkManager>()),
		  rm_(std::make_unique<ge::ResourcesManager>()),
		  st_(std::make_unique<ge::StatesManager>()),
		  toDraw_([](PrioritizedDrawable const & d1, PrioritizedDrawable const & d2) { return d1.first < d2.first; }) {
}

/*
**** CORE
*/
void ge::GameEngine::HandleEvents_() {
	sf::Event event;
	while (window_.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				Quit();
				break;
			default:
				st_->GetCurrentState()->HandleEvent(*this, event);
				break;
		}
	}
}

void ge::GameEngine::Display_(const float interpolation) {
	window_.clear();
	st_->GetCurrentState()->Display(*this, interpolation);
	while (!toDraw_.empty()) {
		window_.draw(*toDraw_.top().second);
		toDraw_.pop();
	}
	window_.display();
}

bool ge::GameEngine::Init(std::string const & title, uint32_t const width, uint32_t const height, bool const fullscreen) {
	windowTitle_ = title;
	fullscreen_ = fullscreen;
	window_.create(sf::VideoMode(width, height), title, fullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
	window_.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(width), static_cast<float>(height))));
	return true;
}

bool ge::GameEngine::Init(std::string const & title, ge::Vector2u const & size, bool const fullscreen) {
	return Init(title, size.x, size.y, fullscreen);
}

void ge::GameEngine::Run(std::string const & initState) {
	PushState(initState);
	LoopTimer timer;

	while (window_.isOpen()) {
		timer.Start();
		while (timer.Update()) {
			nm_->handleRecvEvent();
			HandleEvents_();
			st_->GetCurrentState()->Update(*this);
			nm_->handleSendEvent();
		}
		Display_(timer.GetInterpolation());
	}

/*	auto nextGameTick = std::chrono::high_resolution_clock::now();
	int loops;
	float interpolation;

	while (window_.isOpen()) {
		timer.Start();
		while (std::chrono::high_resolution_clock::now() > nextGameTick && loops < maxFrameSkip) {
			nm_->handleRecvEvent();
			HandleEvents_();
			st_->GetCurrentState()->Update(*this);
			nextGameTick += std::chrono::milliseconds(msToSkip);
			nm_->handleSendEvent();
			++loops;
		}

		interpolation = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() + std::chrono::duration<float, std::milli>(msToSkip) - nextGameTick)
		                / std::chrono::duration<float, std::milli>(msToSkip);
		Display_(interpolation);
	}*/
}

void ge::GameEngine::Draw(std::shared_ptr<sf::Drawable> const & drawable, int32_t const display_level) {
	toDraw_.push(PrioritizedDrawable(display_level, drawable));
}

sf::Vector2f ge::GameEngine::GetCoord(ge::Vector2u v) const {
	return window_.mapPixelToCoords(sf::Vector2i(v.x, v.y));
}

sf::Vector2f ge::GameEngine::GetCoord(uint32_t x, uint32_t y) const {
	return window_.mapPixelToCoords(sf::Vector2i(x, y));
}

ge::Vector2f ge::GameEngine::GetSize() const {
	return Vector2f(window_.getView().getSize().x, window_.getView().getSize().y);
}

ge::Vector2u ge::GameEngine::GetWindowSize() const {
	return Vector2u(window_.getSize().x, window_.getSize().y);
}

void ge::GameEngine::SetSize(uint32_t width, uint32_t height) {
	window_.setSize({ width, height });
	window_.clear();
	window_.display();
//	window_.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(width), static_cast<float>(height))));
	window_.setPosition({ 0, 0 });
}

void ge::GameEngine::SetSize(ge::Vector2u const & size) {
	SetSize(size.x, size.y);
}

void ge::GameEngine::SetFullscreen(bool fullscreen) {
	window_.create(sf::VideoMode(window_.getSize().x, window_.getSize().y), windowTitle_, fullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
	fullscreen_ = fullscreen;
}

bool ge::GameEngine::IsFullscreen() const {
	return fullscreen_;
}

std::vector<ge::Vector2u> ge::GameEngine::GetResolutionsModes() const {
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	std::vector<ge::Vector2u> resolutions;
	for (auto & mode : modes) {
		resolutions.emplace_back(mode.width, mode.height);
	}
	return resolutions;
}

void ge::GameEngine::Quit() {
	window_.close();
}

/*
**** NETWORK
*/
void ge::GameEngine::AddCommunication(std::shared_ptr<ge::network::NetworkCommunication> const & c) {
	nm_->addCommunication(c);
}
void ge::GameEngine::RemoveCommunication(std::shared_ptr<ge::network::NetworkCommunication> const & c) {
	nm_->removeCommunication(c);
}

/*
**** COMPONENTS
*/
/*
bool ge::GameEngine::AddComponent(std::string const & name) {
	return cm_->AddComponent(name);
}

bool ge::GameEngine::AddComponents(std::vector<std::string> const & names) {
	return cm_->AddComponents(names);
}

bool ge::GameEngine::AddComposedComponents(std::string const & name, std::vector<std::string> const & composition) {
	return cm_->AddComposedComponents(name, composition);
}

bool ge::GameEngine::Match(const ge::Entity & entity, const ge::Component & component) const {
	return cm_->Match(entity, component);
}

bool ge::GameEngine::Match(const ge::Entity & entity, std::string const & name) const {
	return cm_->Match(entity, name);
}

bool ge::GameEngine::Match(std::string const & name1, std::string const & name2) const {
	return cm_->Match(name1, name2);
}

const ge::Component &ge::GameEngine::operator[](std::string const & name) const {
	return (*cm_)[name];
}
*/
/*
**** STATES
*/
void ge::GameEngine::AddState(std::string const & name, std::shared_ptr<AGameState> const & state) {
	st_->AddState(name, state);
}

void ge::GameEngine::ChangeState(std::string const & stateName) {
	st_->ChangeState(*this, stateName);
}

void ge::GameEngine::PushState(std::string const & stateName) {
	st_->PushState(*this, stateName);
}

void ge::GameEngine::PopState() {
	st_->PopState();
}

/*
**** RESOURCES
*/
void ge::GameEngine::Load(Animator const & animator) {
	for (auto & animation : animator.GetAnimationsList()) {
		for (auto & sprite : animation.second.sprites) {
			rm_->Load<ge::Resources::Texture>(sprite, sprite);
		}
	}
}

sf::Texture & ge::GameEngine::Texture(std::string const & name) {
	return rm_->Texture(name);
}

sf::Font & ge::GameEngine::Font(std::string const & name) {
	return rm_->Font(name);
}

sf::SoundBuffer & ge::GameEngine::Sound(std::string const & name) {
	return rm_->Sound(name);
}

sf::Music & ge::GameEngine::Music(std::string const & name) {
	return rm_->Music(name);
}