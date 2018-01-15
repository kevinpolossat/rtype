#pragma once

#ifndef COMPONENTS
#define COMPONENTS
#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>
#include "Vector2D.h"

#define TO_STRING( x ) #x

#define CLASS_DECLARATION( classname )                                                      \
public:                                                                                     \
    static const std::size_t Type;                                                          \
    virtual bool IsClassType( const std::size_t classType ) const override;                 \

#define CLASS_DEFINITION( parentclass, childclass )                                         \
const std::size_t childclass::Type = std::hash< std::string >()( TO_STRING( childclass ) ); \
bool childclass::IsClassType( const std::size_t classType ) const {                         \
        if ( classType == childclass::Type )                                                \
            return true;                                                                    \
        return parentclass::IsClassType( classType );                                       \
}      


class Component {
public:
	static const std::size_t Type;
	virtual bool IsClassType(const std::size_t classType) const { return classType == Type; }
	virtual	~Component() = default;
	Component(std::string && initialValue) : value(initialValue) { }
	std::string	value = "uninitialized";
};


class Position : public Component {

	CLASS_DECLARATION(Position)

	public:
		Position();
		Position(const Vector2D& rhs);
		~Position();
		Vector2D getPos() const;
	private:
		Vector2D	m_pos;
};

class GameObject {
public:
	template<class ComponentType, typename... Args>
	void	AddComponent(Args&&... params);

	template<class ComponentType>
	ComponentType &	GetComponent();

	template<class ComponentType>
	bool	RemoveComponent();
private:
	std::vector<std::unique_ptr<Component>> components;

};

/*
	GameObject Templeted functions
*/

template<class ComponentType, typename... Args>
void GameObject::AddComponent(Args&&... params)
{
	components.emplace_back(std::make_unique<ComponentType>(std::forward<Args>(params)...));
}

template<class ComponentType>
ComponentType & GameObject::GetComponent()
{
	for (auto && component : components)
	{
		if (component->IsClassType(ComponentType::Type))
			return *static_cast<ComponentType *>(component.get());
	}
	return *std::unique_ptr<ComponentType>(nullptr);
}

template<class ComponentType>
bool GameObject::RemoveComponent()
{
	if (components.empty())
		return false;

	auto & index = std::find_if(components.begin(),
		components.end(),
		[classType = ComponentType::Type](auto & component) {
		return component->IsClassType(classType);
	});

	bool success = index != components.end();

	if (success)
		components.erase(index);

	return success;
}

#endif // !COMPONENTS
