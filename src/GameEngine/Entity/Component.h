#pragma once

#ifndef COMPONENTS
#define COMPONENTS
#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <stack>
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


class Component 
{
public:
	static const std::size_t Type;
	virtual bool IsClassType(const std::size_t classType) const { return classType == Type; }
	virtual	~Component() = default;
	Component(std::string && initialValue) : value(initialValue) { }
	std::string	value = "uninitialized";
};


class Position : public Component 
{
	CLASS_DECLARATION(Position)

	public:
		Position();
		Position(const Vector2D& rhs);
		~Position();
		void UpdatePos(Vector2D const & v);
		Vector2D getPos() const;
		Vector2D	m_pos;
};

class Velocity : public Component
{
	CLASS_DECLARATION(Velocity)

public:
	Velocity();
	Velocity(const Vector2D& rhs);
	~Velocity();
	void UpdateVel(double const v);
	Vector2D getVel() const;
	Vector2D	m_pos;
};

class Sprite : public Component
{
	CLASS_DECLARATION(Sprite)

public:
	Sprite(std::string const & t_textureName, uint32_t const t_priority);
	~Sprite();
	std::string textureName;
	uint32_t	priority;
};

class Text : public Component
{
	CLASS_DECLARATION(Text)

public:
	Text(std::string const & t_text, std::string const & t_fontName);
	~Text();
	std::string text;
	std::string fontName;
};

class Input : public Component
{
	CLASS_DECLARATION(Input)

public:
	Input(int t_inputId);
	~Input();
	int		id;
};

struct Animation {
	std::vector<std::string> sprites;
	uint32_t current = 0;
	uint32_t speed = 50;
	int32_t priority;
};

class Animator  : public Component
{
	CLASS_DECLARATION(Animator)
	using AnimationsList = std::unordered_map<std::string, Animation>;

public:
	Animator();
	~Animator();

	void AddAnimation(std::string const & name, Animation const & animation);
	void SetAnimation(std::string const & name);
	void DoOnce(std::string const & name);

	std::string GetSprite();
	int32_t GetPriority() const;

	AnimationsList const & GetAnimationsList() const;

private:
	void ErrorUnknownAnimation_(std::string const & name) const;
	void ErrorNoAnimation_() const;

	std::chrono::time_point<std::chrono::high_resolution_clock> time_;
	std::stack<std::string> currents_;
	AnimationsList animations_;
};

class GameObject 
{
public:
	GameObject() {}
	~GameObject() {}
	template<class ComponentType, typename... Args>
	void	AddComponent(Args&&... params);

	template<class ComponentType>
	ComponentType &	GetComponent();

	template<class ComponentType>
	bool	RemoveComponent();

	void setTag(std::string const & t_tag);
	std::string getTag() const;

private:
	std::vector<std::unique_ptr<Component>> components_;
	std::string	m_tag_;

};

/*
	GameObject Templeted functions
*/

template<class ComponentType, typename... Args>
void GameObject::AddComponent(Args&&... params)
{
	components_.emplace_back(std::make_unique<ComponentType>(std::forward<Args>(params)...));
}

template<class ComponentType>
ComponentType & GameObject::GetComponent()
{
	for (auto & component : components_)
	{
		if (component->IsClassType(ComponentType::Type))
			return *static_cast<ComponentType *>(component.get());
	}
	return *std::unique_ptr<ComponentType>(nullptr);
}

template<class ComponentType>
bool GameObject::RemoveComponent()
{
	if (components_.empty())
		return false;

	auto & index = std::find_if(components_.begin(),
		components_.end(),
		[classType = ComponentType::Type](auto & component) {
		return component->IsClassType(classType);
	});

	bool success = index != components_.end();

	if (success)
		components_.erase(index);

	return success;
}

#endif // !COMPONENTS
