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
	virtual Action actualize(std::vector<AIPosition>& ) {};

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

	virtual AIPosition getNearPlayer(std::vector<AIPosition>& players)
	{
		double min = static_cast<double>(_height) * static_cast<double>(_width);
		int minIndex = 0;
		for (int i = 0; i < players.size(); i++)
		{
			double stock = sqrt((this->getPosition().X - players.at(i).X) * (this->getPosition().X - players.at(i).X)
													+ (this->getPosition().Y - players.at(i).Y) * (this->getPosition().Y - players.at(i).Y));
			if (stock < min)
			{
				min = stock;
				minIndex = i;
			}
		}
		return players.at(minIndex);
	}

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
