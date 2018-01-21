#ifndef __BOSS_HPP__
#define __BOSS_HPP__

#include <iostream>
#include <vector>
#include "IArtificialIntelligence.hpp"

class AIShoot
{
public:
  explicit AIShoot(AIPosition p, vec2D v, int hitbox);
  ~AIShoot();

  const AIPosition getTheoryPosition() const { return _theoryPos; }
  const AIPosition getStartPosition() const { return _startPos; }

  void resetTheoryPosition() {_theoryPos = _startPos;}

  const bool increaseShoot();

  const bool collision(AIPosition check, int Xbox, int Ybox);
  const bool collisionNoAutoIncrease(AIPosition check, int Xbox, int Ybox);

private:
  int         _hitbox;
  AIPosition  _startPos;
  AIPosition  _theoryPos;
  vec2D       _direction;
};

class Boss : public IArtificialIntelligence
{
public:
  	Boss(const int myX, const int myY, const int width, const int height);
    Boss(Boss *);
  	~Boss() {}

    Boss & operator=(Boss *);

    virtual IArtificialIntelligence *NewIA(const uint32_t myX, const uint32_t myY, const uint32_t width, const uint32_t height) override;

  	virtual Action actualize(std::vector<AIPosition>& shoots, std::vector<AIPosition>& enemies, AIPosition myPos) override;

  	virtual bool setDamages(uint32_t dmg) override;

  	virtual const AIPosition getPosition() const override;
  	virtual void setPosition(const AIPosition p) override;

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

  	virtual void setShootVector(const vec2D x) override;
  	virtual const vec2D getShootVector() const override;

  	virtual AIPosition getNearPlayer(std::vector<AIPosition>& players) const override;

private:

  void        _selectMove(std::vector<AIPosition>&);
  void        _selectShoot(std::vector<AIPosition>&);
  uint32_t			_turn;
	uint32_t			_width;
	uint32_t			_height;
	AIPosition		_pos;
	std::string		_name;
	uint32_t			_life;
	bool					_shoot;
	vec2D					_shootVector;
  int    _XBox;
  int    _YBox;
};

#endif
