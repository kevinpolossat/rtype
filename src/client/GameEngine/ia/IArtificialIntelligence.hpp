#ifndef __IARTIFICIAL_INTELLIGENCE_HPP__
#define __IARTIFICIAL_INTELLIGENCE_HPP__
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

struct AIPosition
{
	int X;
	int Y;
};

enum Action
{
	DEFAULT = 0,
	SHOOT = 1,
	DEAD = 2
};

struct vec2D
{
		float X;
		float Y;
};

class IArtificialIntelligence
{
public:
	explicit IArtificialIntelligence() = default;
	virtual ~IArtificialIntelligence() = default;

	virtual IArtificialIntelligence *NewIA(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height) = 0;
	// CORE
	virtual Action actualize(std::vector<AIPosition>& shoots, std::vector<AIPosition>& enemies, AIPosition myPos) = 0;

	virtual bool setDamages(uint32_t dmg) = 0;

	virtual const AIPosition getPosition() const = 0;
	virtual void setPosition(const AIPosition p) = 0;

	virtual const std::string &getName() const = 0;
	virtual const void setName(const std::string &n) = 0;

	virtual const uint32_t getLife() const = 0;
	virtual void setLife(const uint32_t l) = 0;

	virtual const uint32_t getWidth() const = 0;
	virtual void setWidth(const uint32_t l) = 0;

	virtual const uint32_t getHeight() const = 0;
	virtual void setHeight(const uint32_t l) = 0;

	virtual const bool getShoot() const = 0;
	virtual void setShoot(const bool x) = 0;

	virtual const uint32_t getTurn() const = 0;
	virtual void setTurn(const uint32_t t) = 0;

	virtual void setShootVector(const vec2D x) = 0;
	virtual const vec2D getShootVector() const = 0;

	virtual AIPosition getNearPlayer(std::vector<AIPosition>& players) const = 0;

};

#endif
