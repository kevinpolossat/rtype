#include "Component.h"


const std::size_t Component::Type = std::hash<std::string>()(TO_STRING(Component));

CLASS_DEFINITION(Component, Position)
CLASS_DEFINITION(Component, Velocity)
CLASS_DEFINITION(Component, Sprite)
CLASS_DEFINITION(Component, Text)


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