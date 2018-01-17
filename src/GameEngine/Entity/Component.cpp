#include "Component.h"


const std::size_t Component::Type = std::hash<std::string>()(TO_STRING(Component));

CLASS_DEFINITION(Component, Position)
CLASS_DEFINITION(Component, Velocity)
CLASS_DEFINITION(Component, Sprite)
CLASS_DEFINITION(Component, Text)
CLASS_DEFINITION(Component, Input)

/* 
	Position Member functions
*/

Position::Position() : Component(std::move("Position"))
{
	this->m_pos = Vector2D(0, 0);
}

Position::Position(const Vector2D& rhs) : Component(std::move("Position"))
{
	this->m_pos = rhs;
}

Position::~Position()
{

}

void Position::UpdatePos(Vector2D const & v)
{
	this->m_pos.x += v.x;
	this->m_pos.y += v.y;
}

Vector2D Position::getPos() const
{
	return (this->m_pos);
}

/*
	Velocity Member functions
*/

Velocity::Velocity() : Component(std::move("Velocity"))
{
	this->m_pos = Vector2D(0, 0);
}

Velocity::Velocity(const Vector2D& rhs) : Component(std::move("Velocity"))
{
	this->m_pos = rhs;
}

Velocity::~Velocity()
{

}

void Velocity::UpdateVel(double const & v)
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

Sprite::Sprite(std::string t_textureName, uint32_t t_priority) : Component(std::move("Sprite"))
{
	this->textureName = t_textureName;
	this->priority = t_priority;
}

Sprite::~Sprite()
{

}

/*
	Text Member Functions
*/

Text::Text(std::string t_text, std::string t_fontName) : Component(std::move("Text"))
{
	this->text = t_text;
	this->fontName = t_fontName;
}

Text::~Text()
{

}

/*
	Input Member Functions
*/

Input::Input(int t_inputId) : Component(std::move("Input"))
{
	this->id = t_inputId;
}

Input::~Input()
{

}

/* 
	GameObject non-templeted member functions
*/

void GameObject::setTag(std::string const & t_tag)
{
	this->m_tag = t_tag;
}

std::string GameObject::getTag() const
{
	return (this->m_tag);
}