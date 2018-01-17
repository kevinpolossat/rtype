#include "Component.h"


const std::size_t Component::Type = std::hash<std::string>()(TO_STRING(Component));

CLASS_DEFINITION(Component, Position)
CLASS_DEFINITION(Component, Velocity)
CLASS_DEFINITION(Component, Sprite)
CLASS_DEFINITION(Component, Text)
CLASS_DEFINITION(Component, Input)
CLASS_DEFINITION(Component, Animator)


/* 
	Position Member functions
*/

Position::Position() : Component("Position")
{
	this->m_pos = Vector2D(0, 0);
}

Position::Position(const Vector2D& rhs) : Component("Position")
{
	this->m_pos = rhs;
}

Position::~Position()
{

}

void Position::UpdatePos(Vector2D const & v, uint32_t widht, uint32_t height, uint32_t offset)
{
	this->m_pos.x += v.x;
	this->m_pos.y += v.y;
	if (this->m_pos.x < 0)
		m_pos.x = 0;
	if (this->m_pos.y < 0)
		m_pos.y = 0;
	if (this->m_pos.x > widht - offset)
		m_pos.x = widht - offset;
	if (this->m_pos.y > height - offset)
		m_pos.y = height - offset;
}

Vector2D Position::getPos() const
{
	return (this->m_pos);
}

/*
	Velocity Member functions
*/

Velocity::Velocity() : Component("Velocity")
{
	this->m_pos = Vector2D(0, 0);
}

Velocity::Velocity(const Vector2D& rhs) : Component("Velocity")
{
	this->m_pos = rhs;
}

Velocity::~Velocity()
{

}

void Velocity::UpdateVel(double const v)
{
	this->m_pos.x /= v;
	this->m_pos.y /= v;
}

Vector2D Velocity::getVel() const
{
	return (this->m_pos);
}

/*
	Sprite Member Functions
*/

Sprite::Sprite(std::string const & t_textureName, uint32_t const t_priority) : Component("Sprite"), textureName(t_textureName), priority(t_priority)
{
}

Sprite::~Sprite()
{

}

/*
	Text Member Functions
*/

Text::Text(std::string const & t_text, std::string const & t_fontName) : Component("Text"), text(t_text), fontName(t_fontName)
{
}

Text::~Text()
{

}

/*
	Input Member Functions
*/

Input::Input(int t_inputId) : Component("Input"), id(t_inputId)
{
}

Input::~Input()
{

}


/*
	Animator memver functions
*/

Animator::Animator() : Component("Animator")
{

}

Animator::~Animator()
{

}

void Animator::AddAnimation(std::string const & name, Animation const & animation) {
	animations_.insert(std::pair<std::string, Animation>(name, animation));
}

void Animator::SetAnimation(std::string const & name) {
	if (currents_.empty() || name != currents_.top()) {
		if (!animations_.count(name)) {
			ErrorUnknownAnimation_(name);
		}
		currents_ = std::stack<std::string>();
		currents_.push(name);
		time_ = std::chrono::high_resolution_clock::now();
	}
}

void Animator::DoOnce(std::string const & name) {
	if (currents_.empty() || name != currents_.top()) {
		if (!animations_.count(name)) {
			ErrorUnknownAnimation_(name);
		}
		currents_.push(name);
		time_ = std::chrono::high_resolution_clock::now();
	}
}

std::string Animator::GetSprite() {
	if (currents_.empty()) {
		ErrorNoAnimation_();
		return "";
	}
	if (animations_.count(currents_.top())) {
		Animation & animation = animations_[currents_.top()];
		while (std::chrono::high_resolution_clock::now() > time_) {
			time_ += std::chrono::milliseconds(animation.speed);
			if (animation.current + 1 >= animation.sprites.size()) {
				animation.current = 0;
				if (currents_.size() > 1) {
					currents_.pop();
				}
			}
			else {
				++animation.current;
			}
		}
		return animation.sprites[animation.current];
	}
	else {
		ErrorUnknownAnimation_("currents_");
		return "";
	}
}

int32_t Animator::GetPriority() const {
	if (currents_.empty()) {
		ErrorNoAnimation_();
		return 0;
	}
	if (animations_.count(currents_.top())) {
		return animations_.at(currents_.top()).priority;
	}
	else {
		ErrorUnknownAnimation_(currents_.top());
		return 0;
	}
}

void Animator::ErrorUnknownAnimation_(std::string const & name) const {
	std::cerr << "Animator : Animation " << name << " doesn't exist" << std::endl;
}

void Animator::ErrorNoAnimation_() const {
	std::cerr << "Animator : No animation set" << std::endl;
}

Animator::AnimationsList const & Animator::GetAnimationsList() const {
	return animations_;
}

/* 
	GameObject non-templeted member functions
*/

void GameObject::setTag(std::string const & t_tag)
{
	this->m_tag_ = t_tag;
}

std::string GameObject::getTag() const
{
	return (this->m_tag_);
}