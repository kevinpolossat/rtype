#ifndef __IARTIFICIAL_INTELLIGENCE_HPP__
#define __IARTIFICIAL_INTELLIGENCE_HPP__
#include <iostream>
#include <string>
#include <math.h>

struct AIPosition
{
	int X;
	int Y;
};

enum Action
{
	DEFAULT,
	SHOOT,
	DEAD
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

	// CORE
	virtual Action actualize(const uint32_t enX, const uint32_t enY) {return Action::DEFAULT;};

	virtual bool setDamages(uint32_t dmg)
	{
			uint32_t l = this->getLife();

			this->setLife(l - dmg);
			return (this->getLife() > 0);
	}

	// SETTER | GETTER
	virtual const AIPosition getPosition() { return _pos; }
	virtual void setPosition(const AIPosition p) { _pos = p; }

	virtual const std::string &getName() { return _name; }
	virtual const void setName(const std::string &n) { _name = n; }

	virtual const uint32_t getLife() { return _life; }
	virtual void setLife(const uint32_t l) { _life = l; }

	virtual const uint32_t getWidth() { return _width; }
	virtual void setWidth(const uint32_t l) { _width = l; }

	virtual const uint32_t getHeight() { return _height; }
	virtual void setHeight(const uint32_t l) { _height = l; }

	virtual const bool getShoot() { return _shoot; }
	virtual void setShoot(const bool x) { _shoot = x; }

	virtual const uint32_t getTurn() { return _turn; }
	virtual void setTurn(const uint32_t t) { _turn = t; }

	virtual void setShootVector(const vec2D x) {_shootVector = x;}
	virtual const vec2D getShootVector() {return _shootVector;}


private:
	uint32_t			_turn;
	uint32_t			_width;
	uint32_t			_height;
	AIPosition		_pos;
	std::string		_name;
	uint32_t			_life;
	bool					_shoot;
	vec2D					_shootVector;
};

#endif
