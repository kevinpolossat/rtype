#ifndef __BASIC_HPP__
#define __BASIC_HPP__

#include <math.h>
#include "IArtificialIntelligence.hpp"

class Basic : public IArtificialIntelligence
{
public:
	Basic(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height);
	~Basic() {}

	virtual std::shared_ptr<IArtificialIntelligence> NewIA(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height);

	virtual Action actualize(std::vector<AIPosition>& shoots, std::vector<AIPosition>& enemies, AIPosition myPos) override;

	virtual bool setDamages(uint32_t dmg) override;

	virtual const AIPosition& getPosition() const override;
	virtual void setPosition(const AIPosition& p) override;

	virtual const std::string &getName() const override;
	virtual const void setName(const std::string &n) override;

	virtual const uint32_t getLife() const override;
	virtual void setLife(const uint32_t l) override;

	virtual const uint32_t getWidth() const override;
	virtual void setWidth(const uint32_t l) override;

	virtual const uint32_t getHeight() const override;
	virtual void setHeight(const uint32_t l) override;

	virtual const bool getShoot() const override;
	virtual void setShoot(const bool x) override;

	virtual const uint32_t getTurn() const override;
	virtual void setTurn(const uint32_t t) override;

	virtual void setShootVector(const vec2D& x) override;
	virtual const vec2D& getShootVector() const override;

	virtual AIPosition& getNearPlayer(std::vector<AIPosition>& players) const override;

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

#endif //__BASIC_HPP__
