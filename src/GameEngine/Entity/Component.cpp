#include "Component.h"


const std::size_t Component::Type = std::hash<std::string>()(TO_STRING(Component));

CLASS_DEFINITION(Component, Position)


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
